INCLUDE( InstallRequiredSystemLibraries)

SET( CPACK_PACKAGE_NAME "bcl")
SET( CPACK_PACKAGE_DESCRIPTION_SUMMARY "bcl is the biochemical library")
SET( CPACK_PACKAGE_VENDOR "bclcommons")
SET( CPACK_PACKAGE_CONTACT "bcl-academic-support@meilerlab.org")
SET( CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${BCL_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
SET( CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/installer/License.txt")
SET( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/installer/License.txt")
SET( CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/installer/ReadMe_${CMAKE_SYSTEM_NAME}.txt")
SET( CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/installer/Welcome.txt")
SET( CPACK_PACKAGE_VERSION_MAJOR ${BCL_VERSION_MAJOR})
SET( CPACK_PACKAGE_VERSION_MINOR ${BCL_VERSION_MINOR})
SET( CPACK_PACKAGE_VERSION_PATCH ${BCL_VERSION_PATCH})
SET( CPACK_PACKAGE_INSTALL_DIRECTORY "bcl_${BCL_VERSION_MAJOR}.${BCL_VERSION_MINOR}")
SET( CPACK_SOURCE_IGNORE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/build/"      # build folders are auto-generated by the build
    "/build_selected_files/"
    "/.git/"
    "/.svn/"
    "/pthreads/"   # affects win32 build only; because libpthreads for win32 is LGPL, which would require BCL to be LGPL
    "/ati/"        # ATI's sources (used for win32 opencl build) are copyrighted
    "/freeocl/"    # LGPL
    "apps/internal/util/bcl_app_generate_license_file" # No GenerateLicenseFile
)

SET( BCL_EXEC_PREFIX ".")

# turn all source packaging off; choose default compression type below
SET( CPACK_SOURCE_GENERATOR "")

# STGZ generator for Linux by default
IF( UNIX)
	SET( CPACK_GENERATOR "STGZ")
	SET( CPACK_SOURCE_GENERATOR  "TGZ")
ENDIF( UNIX)

# NSIS generator for Windows by default
IF( WIN32)
	SET( BCL_EXEC_PREFIX "./bin")
	SET( CPACK_GENERATOR "NSIS")
	SET( CPACK_SOURCE_GENERATOR "ZIP")

	# generator specific variables
	SET( CPACK_NSIS_MUI_ICON                 "${CMAKE_CURRENT_SOURCE_DIR}/installer\\\\bcl_windows.ico") # installer icon
	SET( CPACK_NSIS_MUI_UNIICON              "${CMAKE_CURRENT_SOURCE_DIR}/installer\\\\bcl_windows.ico") # uninstaller icon
	SET( CPACK_PACKAGE_ICON                  "${CMAKE_CURRENT_SOURCE_DIR}/installer\\\\bcl.bmp") # branding icon displayed in the installer - can be a bmp
#  SET( CPACK_NSIS_EXTRA_INSTALL_COMMANDS   "")
#  SET( CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "")
#  SET( CPACK_NSIS_COMPRESSOR               "")
	SET( CPACK_NSIS_MODIFY_PATH              ON) # adds the install path to the PATH variable
	SET( CPACK_NSIS_DISPLAY_NAME             "BioChemicalLibrary")
	SET( CPACK_NSIS_INSTALLED_ICON_NAME      "${CMAKE_CURRENT_SOURCE_DIR}/installer\\\\bcl_windows.ico") # Set the icon used for the Windows "Add or Remove Programs" tool
	SET( CPACK_NSIS_HELP_LINK                "http:\\\\www.meilerlab.org")
	SET( CPACK_NSIS_URL_INFO_ABOUT           "http:\\\\www.meilerlab.org\\\\bclcommons")
	SET( CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
	SET( CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}")
#  SET( CPACK_NSIS_CONTACT                  "")
#  SET( CPACK_NSIS_CREATE_ICONS_EXTRA       "")
#  SET( CPACK_NSIS_DELETE_ICONS_EXTRA       "")
#  SET( CPACK_NSIS_MENU_LINKS               "") # overrides start menu links
#  SET( CPACK_NSIS_MUI_FINISHPAGE_RUN       "")
ENDIF( WIN32)

# STGZ generator for Mac by default
IF( APPLE)
	SET( CPACK_GENERATOR  "STGZ")
	SET( CPACK_SOURCE_GENERATOR "ZIP")
ENDIF( APPLE)

#SET( CPACK_COMPONENTS_ALL_GROUPS_IN_ONE_PACKAGE 0)
#SET( CPACK_COMPONENTS_ALL_GROUPS_IN_ONE_PACKAGE 1)
#SET( CPACK_COMPONENTS_IGNORE_GROUPS 1)

#include only cpackcomponent
# including cpack entirely configures the entire installer, and leads to cpack not working correctly and/or requiring
# a strongly version-dependent set of flags to work-around
INCLUDE( CPackComponent)

################
# install groups
################

# group for release objects; all such objects will always be packed
CPACK_ADD_COMPONENT(
	BclReleaseAll
	DISPLAY_NAME "bcl opencl kernels"
	DESCRIPTION "opencl kernels for opencl components"
)

IF( NOT BCL_LICENSE)

	# Component groups currently suffer from several bugs in CPack, and of questionable use for the simple needs of our
	# installation process.  These commands are kept, only as reference, for how component groups may be used

	# group externals
	CPACK_ADD_COMPONENT_GROUP(
		BclExtern
		DISPLAY_NAME "bcl external libraries"
		DESCRIPTION "dynamically linked external libraries which might be required, if they are not installed on the system"
	)

	# group for resources
	CPACK_ADD_COMPONENT_GROUP(
		BclResources
		DISPLAY_NAME "bcl resources"
		DESCRIPTION "resources required to use certain features and applications within the bcl"
	)

	# group for static applications
	CPACK_ADD_COMPONENT_GROUP(
		BclStaticApplications
		DISPLAY_NAME "applications linked statically"
		DESCRIPTION "applications that are standalone - they require more space"
	)

	# group for dynamic applications
	CPACK_ADD_COMPONENT_GROUP(
		BclDynamicApplications
		DISPLAY_NAME "applications linked dynamically"
		DESCRIPTION "applications that require the bcl libraries, useful if multiple applications are installed, saving hdd space and memory"
	)
ENDIF()