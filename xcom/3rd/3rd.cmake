get_filename_component(3RD_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
message("util 设置：${3RD_CMAKE_DIR}")

include(${3RD_CMAKE_DIR}/message_loop/message_loop.cmake)
include(${3RD_CMAKE_DIR}/thread/thread.cmake)
include(${3RD_CMAKE_DIR}/time/time.cmake)
include(${3RD_CMAKE_DIR}/curl/curl.cmake)
include(${3RD_CMAKE_DIR}/json/json.cmake)


set(3RD_INC
	${3RD_CMAKE_DIR}
	${TIME_INC}
	${THREAD_INC}
	${MSG_LOOP_INC}
	${CURL_INC}
	${JSON_INC}
	)

message("3RD_INC : ${3RD_INC}")

set(3RD_INCLUDE
	${3RD_CMAKE_DIR}/time/*.h
	${3RD_CMAKE_DIR}/thread/*.h
	${3RD_CMAKE_DIR}/message_loop/*.h
	${3RD_CMAKE_DIR}/curl/*.h
	${3RD_CMAKE_DIR}/json/*.h
	)

file(GLOB 3RD_HEADER ${3RD_CMAKE_DIR}/*.h)
file(GLOB 3RD_SOURCE ${3RD_CMAKE_DIR}/*.cpp)

set(3RD_SRC
		${TIME_SRC}
		${THREAD_SRC}
		${MSG_LOOP_SRC}
		${CURL_SRC}
		${JSON_SRC}
		#${UTIL_HEADER}
		#${UTIL_SOURCE}
		)
