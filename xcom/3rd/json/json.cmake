get_filename_component(JSON_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(JSON_INC
		#${JSON_CMAKE_DIR} #Linux compile error fix
		)

set(JSON_SRC
		${JSON_CMAKE_DIR}/json_reader.cpp
		${JSON_CMAKE_DIR}/json_value.cpp
		${JSON_CMAKE_DIR}/json_writer.cpp
		)
