# libromdata test suite
CMAKE_POLICY(SET CMP0048 NEW)
IF(POLICY CMP0063)
	# CMake 3.3: Enable symbol visibility presets for all
	# target types, including static libraries and executables.
	CMAKE_POLICY(SET CMP0063 NEW)
ENDIF(POLICY CMP0063)
PROJECT(libromdata-tests LANGUAGES C CXX)

# Top-level src directory
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../..)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/../..)

IF(ENABLE_DECRYPTION)
	# CtrKeyScrambler test.
	ADD_EXECUTABLE(CtrKeyScramblerTest CtrKeyScramblerTest.cpp)
	TARGET_LINK_LIBRARIES(CtrKeyScramblerTest PRIVATE rptest romdata)
	TARGET_LINK_LIBRARIES(CtrKeyScramblerTest PRIVATE gtest)
	DO_SPLIT_DEBUG(CtrKeyScramblerTest)
	SET_WINDOWS_SUBSYSTEM(CtrKeyScramblerTest CONSOLE)
	SET_WINDOWS_ENTRYPOINT(CtrKeyScramblerTest wmain OFF)
	ADD_TEST(NAME CtrKeyScramblerTest COMMAND CtrKeyScramblerTest "--gtest_brief=1")
ENDIF(ENABLE_DECRYPTION)

# GcnFstPrint (Not a test, but a useful program.)
ADD_EXECUTABLE(GcnFstPrint
	disc/FstPrint.cpp
	disc/FstPrint.hpp
	disc/GcnFstPrint.cpp
	)
TARGET_LINK_LIBRARIES(GcnFstPrint PRIVATE rpsecure romdata)
IF(ENABLE_NLS)
	TARGET_LINK_LIBRARIES(GcnFstPrint PRIVATE i18n)
ENDIF(ENABLE_NLS)
IF(WIN32)
	TARGET_LINK_LIBRARIES(GcnFstPrint PRIVATE wmain)
ENDIF(WIN32)
DO_SPLIT_DEBUG(GcnFstPrint)
SET_WINDOWS_SUBSYSTEM(GcnFstPrint CONSOLE)
SET_WINDOWS_ENTRYPOINT(GcnFstPrint wmain OFF)

# GcnFstTest
# NOTE: We can't disable NLS here due to its usage
# in FstPrint.cpp. gtest_init.cpp will set LC_ALL=C.
ADD_EXECUTABLE(GcnFstTest
	disc/FstPrint.cpp
	disc/FstPrint.hpp
	disc/GcnFstTest.cpp
	)
TARGET_LINK_LIBRARIES(GcnFstTest PRIVATE rptest romdata)
IF(ENABLE_NLS)
	TARGET_LINK_LIBRARIES(GcnFstTest PRIVATE i18n)
ENDIF(ENABLE_NLS)
TARGET_LINK_LIBRARIES(GcnFstTest PRIVATE gtest)
TARGET_LINK_LIBRARIES(GcnFstTest PRIVATE minizip ${ZLIB_LIBRARIES})
DO_SPLIT_DEBUG(GcnFstTest)
SET_WINDOWS_SUBSYSTEM(GcnFstTest CONSOLE)
SET_WINDOWS_ENTRYPOINT(GcnFstTest wmain OFF)
ADD_TEST(NAME GcnFstTest COMMAND GcnFstTest --gtest_brief)
IF(NOT WIN32 AND NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY STREQUAL "")
	# Create a symlink to the fst_data directory.
	ADD_CUSTOM_COMMAND(TARGET GcnFstTest POST_BUILD
		COMMAND ln -sf "${CMAKE_CURRENT_SOURCE_DIR}/disc/fst_data" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fst_data"
		VERBATIM
		)
ENDIF(NOT WIN32 AND NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY STREQUAL "")

# ImageDecoder test
ADD_EXECUTABLE(ImageDecoderTest img/ImageDecoderTest.cpp)
TARGET_LINK_LIBRARIES(ImageDecoderTest PRIVATE rptest romdata)
TARGET_LINK_LIBRARIES(ImageDecoderTest PRIVATE gtest ${ZLIB_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(ImageDecoderTest PRIVATE ${ZLIB_INCLUDE_DIRS})
TARGET_COMPILE_DEFINITIONS(ImageDecoderTest PRIVATE ${ZLIB_DEFINITIONS})
IF(PNG_LIBRARY)
	TARGET_LINK_LIBRARIES(ImageDecoderTest PRIVATE ${PNG_LIBRARY})
	TARGET_INCLUDE_DIRECTORIES(ImageDecoderTest PRIVATE ${PNG_INCLUDE_DIRS})
	TARGET_COMPILE_DEFINITIONS(ImageDecoderTest PRIVATE ${PNG_DEFINITIONS})
ENDIF(PNG_LIBRARY)
DO_SPLIT_DEBUG(ImageDecoderTest)
SET_WINDOWS_SUBSYSTEM(ImageDecoderTest CONSOLE)
SET_WINDOWS_ENTRYPOINT(ImageDecoderTest wmain OFF)
ADD_TEST(NAME ImageDecoderTest COMMAND ImageDecoderTest --gtest_brief --gtest_filter=-*Benchmark*)
IF(NOT WIN32 AND NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY STREQUAL "")
	# Create a symlink to the ImageDecoder_data directory.
	ADD_CUSTOM_COMMAND(TARGET ImageDecoderTest POST_BUILD
		COMMAND ln -sf "${CMAKE_CURRENT_SOURCE_DIR}/img/ImageDecoder_data" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImageDecoder_data"
		VERBATIM
		)
ENDIF(NOT WIN32 AND NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY STREQUAL "")

# Nintendo System ID test
ADD_EXECUTABLE(NintendoSystemIDTest NintendoSystemIDTest.cpp)
TARGET_LINK_LIBRARIES(NintendoSystemIDTest PRIVATE rptest romdata)
TARGET_LINK_LIBRARIES(NintendoSystemIDTest PRIVATE gtest)
DO_SPLIT_DEBUG(NintendoSystemIDTest)
SET_WINDOWS_SUBSYSTEM(NintendoSystemIDTest CONSOLE)
SET_WINDOWS_ENTRYPOINT(NintendoSystemIDTest wmain OFF)
ADD_TEST(NAME NintendoSystemIDTest COMMAND NintendoSystemIDTest --gtest_brief)

# SuperMagicDrive test
ADD_EXECUTABLE(SuperMagicDriveTest
	utils/SuperMagicDriveTest.cpp
	utils/SuperMagicDriveTest_data.hpp
	)
TARGET_LINK_LIBRARIES(SuperMagicDriveTest PRIVATE rptest romdata)
TARGET_LINK_LIBRARIES(SuperMagicDriveTest PRIVATE gtest)
TARGET_LINK_LIBRARIES(SuperMagicDriveTest PRIVATE ${ZLIB_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(SuperMagicDriveTest PRIVATE ${ZLIB_INCLUDE_DIRS})
TARGET_COMPILE_DEFINITIONS(SuperMagicDriveTest PRIVATE ${ZLIB_DEFINITIONS})
DO_SPLIT_DEBUG(SuperMagicDriveTest)
SET_WINDOWS_SUBSYSTEM(SuperMagicDriveTest CONSOLE)
SET_WINDOWS_ENTRYPOINT(SuperMagicDriveTest wmain OFF)
ADD_TEST(NAME SuperMagicDriveTest COMMAND SuperMagicDriveTest --gtest_brief --gtest_filter=-*benchmark*)

### zstd is required past this point ###

IF(ENABLE_ZSTD)
	# MicroTAR zstd wrapper
	ADD_LIBRARY(microtar_zstd STATIC microtar_zstd.c microtar_zstd.h)
	TARGET_LINK_LIBRARIES(microtar_zstd PUBLIC microtar ${ZSTD_LIBRARY})
	DO_SPLIT_DEBUG(microtar_zstd)

	# RomHeader test
	ADD_EXECUTABLE(RomHeaderTest RomHeaderTest.cpp)
	TARGET_LINK_LIBRARIES(RomHeaderTest PRIVATE rptest romdata)
	TARGET_LINK_LIBRARIES(RomHeaderTest PRIVATE microtar_zstd)
	TARGET_LINK_LIBRARIES(RomHeaderTest PRIVATE gtest)
	DO_SPLIT_DEBUG(RomHeaderTest)
	SET_WINDOWS_SUBSYSTEM(RomHeaderTest CONSOLE)
	SET_WINDOWS_ENTRYPOINT(RomHeaderTest wmain OFF)
	ADD_TEST(NAME RomHeaderTest COMMAND RomHeaderTest --gtest_brief)
	IF(NOT WIN32 AND NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY STREQUAL "")
		# Create a symlink to the RomHeaders directory.
		ADD_CUSTOM_COMMAND(TARGET RomHeaderTest POST_BUILD
			COMMAND ln -sf "${CMAKE_CURRENT_SOURCE_DIR}/RomHeaders" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RomHeaders"
			VERBATIM
			)
	ENDIF(NOT WIN32 AND NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY STREQUAL "")
ENDIF(ENABLE_ZSTD)
