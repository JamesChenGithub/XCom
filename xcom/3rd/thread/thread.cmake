get_filename_component(THREAD_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(THREAD_INC
		${THREAD_CMAKE_DIR}
		)

set(THREAD_SRC
		${THREAD_CMAKE_DIR}/tdispatch.cpp
		${THREAD_CMAKE_DIR}/tthread.cpp
		)
