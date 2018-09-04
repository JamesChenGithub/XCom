get_filename_component(MSG_LOOP_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(MSG_LOOP_INC
		${MSG_LOOP_CMAKE_DIR}
		)

set(MSG_LOOP_SRC
		${MSG_LOOP_CMAKE_DIR}/tlazy_instance.cpp
		${MSG_LOOP_CMAKE_DIR}/tmessage_loop.cpp
		${MSG_LOOP_CMAKE_DIR}/tmessage_loop_libevent.cpp
		${MSG_LOOP_CMAKE_DIR}/tmessage_pump_default.cpp
		${MSG_LOOP_CMAKE_DIR}/trun_loop.cpp
		)
