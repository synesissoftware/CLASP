
if(APPLE)

	message("adding '/usr/local/include' to include-directories for 'examples'")

	include_directories("/usr/local/include")
endif(APPLE)

if(WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		message (STATUS "Compiling for 64-bit Windows")

		add_definitions(-DWIN64)
	else()

		message (STATUS "Compiling for 32-bit Windows")

		add_definitions(-DWIN32)
	endif()

	# suppress implicit-link file
	add_definitions(-DCSTRING_INCL_CSTRING_H_IMPLICIT_LINK)
endif()

if(UNIX)

	add_definitions(-DUNIX)
	add_definitions(-Dunix)
endif()


add_subdirectory(cvu)


# ############################## end of file ############################# #

