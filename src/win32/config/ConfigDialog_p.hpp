/***************************************************************************
 * ROM Properties Page shell extension. (Win32)                            *
 * ConfigDialog_p.hpp: Configuration dialog. (Private class)               *
 *                                                                         *
 * Copyright (c) 2016-2017 by David Korth.                                 *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; either version 2 of the License, or (at your  *
 * option) any later version.                                              *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License along *
 * with this program; if not, write to the Free Software Foundation, Inc., *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           *
 ***************************************************************************/

#ifndef __ROMPROPERTIES_WIN32_CONFIG_CONFIGDIALOGPRIVATE_HPP__
#define __ROMPROPERTIES_WIN32_CONFIG_CONFIGDIALOGPRIVATE_HPP__

#include "libromdata/config.libromdata.h"
#include "libromdata/common.h"

namespace LibRomData {
	class Config;
}

// Property sheet tabs.
class ITab;

class ConfigDialogPrivate
{
	public:
		ConfigDialogPrivate();
		~ConfigDialogPrivate();

	private:
		RP_DISABLE_COPY(ConfigDialogPrivate)

	public:
		// Property for "D pointer".
		// This points to the ConfigDialogPrivate object.
		static const wchar_t D_PTR_PROP[];

	public:
		// Config instance.
		LibRomData::Config *config;

		/**
		 * Convert a bool value to BST_CHCEKED or BST_UNCHECKED.
		 * @param value Bool value.
		 * @return BST_CHECKED or BST_UNCHECKED.
		 */
		static inline int boolToBstChecked(bool value) {
			return (value ? BST_CHECKED : BST_UNCHECKED);
		}

		/**
		 * Convert BST_CHECKED or BST_UNCHECKED to a bool string.
		 * @param value BST_CHECKED or BST_UNCHECKED.
		 * @return Bool string.
		 */
		static inline const wchar_t *bstCheckedToBoolString(unsigned int value) {
			return (value == BST_CHECKED ? L"true" : L"false");
		}

		// Property sheet variables.
		ITab *tabs[3];	// TODO: Add Downloads.
		HPROPSHEETPAGE hpsp[3];
		PROPSHEETHEADER psh;

		// Property sheet change variables.
		// Used for optimization.
		bool changed_Downloads;

		// Downloads tab functions.
		void reset_Downloads(HWND hDlg);
		void save_Downloads(HWND hDlg);
		static INT_PTR CALLBACK DlgProc_Downloads(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static UINT CALLBACK CallbackProc_Downloads(HWND hWnd, UINT uMsg, LPPROPSHEETPAGE ppsp);

		// Property Sheet callback.
		static int CALLBACK CallbackProc(HWND hDlg, UINT uMsg, LPARAM lParam);

		// Create Property Sheet.
		static INT_PTR CreatePropertySheet(void);
};

#endif /* __ROMPROPERTIES_WIN32_CONFIG_CONFIGDIALOGPRIVATE_HPP__ */
