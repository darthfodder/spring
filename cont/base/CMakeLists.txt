# This will build the following, needed to run spring:
# * ${BUILD_DIR}/spring/bitmaps.sdz
# * ${BUILD_DIR}/springcontent.sdz
# * ${BUILD_DIR}/maphelper.sdz
# * ${BUILD_DIR}/cursors.sdz

FIND_PACKAGE(SevenZip REQUIRED)

add_custom_target(basecontent ALL)

MACRO(CreateBaseContentArchive outputdir filename files)
	### FIXME: find a nicer way to silence 7z
	if(UNIX)
		set(QUIET ">/dev/null")
	elseif(WIN32)
		set(QUIET ">nul")
	endif()
	set(outputfile "${Spring_BINARY_DIR}/${outputdir}/${filename}")
	### remove old file to force recreation from scratch
	file(REMOVE "${outputfile}")
	add_custom_command(
		OUTPUT "${outputfile}"
		COMMAND ${SEVENZIP_BIN} a -tzip ${outputfile} ${files} ${QUIET}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
		COMMENT "Creating ${output}"
		DEPENDS ${files}
	)

	### add target & dependencies to basecontent
	add_custom_target(${filename} DEPENDS ${outputfile})
	add_dependencies(basecontent ${filename})

	### Install content
	install(FILES "${outputfile}"
		DESTINATION ${DATADIR}/${outputdir})
ENDMACRO()

file(MAKE_DIRECTORY "${Spring_BINARY_DIR}/base")
file(MAKE_DIRECTORY "${Spring_BINARY_DIR}/base/spring")

add_subdirectory(bitmaps)
add_subdirectory(springcontent)
add_subdirectory(maphelper)
add_subdirectory(cursors)



