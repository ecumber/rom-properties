/***************************************************************************
 * ROM Properties Page shell extension. (KDE4/KF5)                         *
 * DragImageTreeView.cpp: Drag & Drop QTreeView subclass.                  *
 *                                                                         *
 * Copyright (c) 2019-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

// References:
// - https://doc.qt.io/qt-5/dnd.html
// - https://wiki.qt.io/QList_Drag_and_Drop_Example
#include "stdafx.h"
#include "DragImageTreeView.hpp"
#include "RpQByteArrayFile.hpp"

// librpbase, librptexture
using LibRpBase::RpPngWriter;
using LibRpTexture::rp_image;

void DragImageTreeView::startDrag(Qt::DropActions supportedActions)
{
	// TODO: Handle supportedActions?
	// TODO: Multiple PNG images if multiple items are selected?
	// - May need to write images to a temp directory and use a URI list...
	Q_UNUSED(supportedActions)

	// Get the selected indexes.
	const QModelIndexList indexes = selectedIndexes();
	if (indexes.isEmpty()) {
		// No items selected.
		return;
	}

	// NOTE: Each column is technically considered an item.
	// Find the first item with a valid RpImageRole.
	QModelIndexList items;
	for (const QModelIndex &p : indexes) {
		void *img = p.data(RpImageRole).value<void*>();
		if (img != nullptr) {
			// Index has a valid image.
			items.append(p);
		}
	}

	// TODO: Handle more than one selected item.
	items = items.mid(0, 1);

	// Find rp_image* objects in the items.
	QMimeData *const mimeData = new QMimeData;
	mimeData->setObjectName(QLatin1String("mimeData"));
	QIcon dragIcon;
	bool hasOne = false;
	for (const QModelIndex &index : items) {
		const rp_image *const img = static_cast<const rp_image*>(index.data(RpImageRole).value<void*>());
		if (!img)
			continue;

		// Convert the rp_image to PNG.
		RpQByteArrayFile *const pngData = new RpQByteArrayFile();
		RpPngWriter *const pngWriter = new RpPngWriter(pngData, img);
		if (!pngWriter->isOpen()) {
			// Unable to open the PNG writer.
			delete pngWriter;
			pngData->unref();
			continue;
		}

		// TODO: Add text fields indicating the source game.

		int pwRet = pngWriter->write_IHDR();
		if (pwRet != 0) {
			// Error writing the PNG image...
			delete pngWriter;
			pngData->unref();
			continue;
		}
		pwRet = pngWriter->write_IDAT();
		if (pwRet != 0) {
			// Error writing the PNG image...
			delete pngWriter;
			pngData->unref();
			continue;
		}

		// RpPngWriter will finalize the PNG on delete.
		delete pngWriter;

		// Set the PNG data.
		mimeData->setData(QLatin1String("image/png"), pngData->qByteArray());
		pngData->unref();

		// Save the icon.
		if (dragIcon.isNull()) {
			QStandardItemModel *const model = qobject_cast<QStandardItemModel*>(this->model());
			if (model) {
				QStandardItem *const item = model->itemFromIndex(index);
				if (item) {
					dragIcon = item->icon();
				}
			}
		}

		hasOne = true;
	}

	if (!hasOne) {
		// No rp_image* objects...
		delete mimeData;
		return;
	}

	QDrag *const drag = new QDrag(this);
	drag->setObjectName(QLatin1String("drag"));
	drag->setMimeData(mimeData);

	QPixmap qpxm;
	if (!dragIcon.isNull()) {
		qpxm = dragIcon.pixmap(this->iconSize());
	}
	if (!qpxm.isNull()) {
		drag->setPixmap(qpxm);
	}

	drag->exec(Qt::CopyAction);
}
