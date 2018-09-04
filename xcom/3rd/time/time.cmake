get_filename_component(TIME_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(TIME_INC
		${TIME_CMAKE_DIR}
		)

set(TIME_SRC
		${TIME_CMAKE_DIR}/ttime.cpp
		)
