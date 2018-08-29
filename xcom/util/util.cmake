get_filename_component(UTIL_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
message("util 设置：${UTIL_CMAKE_DIR}")

include(${UTIL_CMAKE_DIR}/string/string.cmake)
include(${UTIL_CMAKE_DIR}/time/time.cmake)

set(UTIL_INC
	${UTIL_CMAKE_DIR}
	${STRING_INC}
	${TIME_INC}
	)

message("UTIL_INC : ${UTIL_INC}")

set(UTIL_INCLUDE
	${UTIL_CMAKE_DIR}/string/*.h
	${UTIL_CMAKE_DIR}/time/*.h
	)

file(GLOB UTIL_HEADER ${UTIL_CMAKE_DIR}/*.h)
file(GLOB UTIL_SOURCE ${UTIL_CMAKE_DIR}/*.cpp)

set(UTIL_SRC
		${STRING_SRC}
		${TIME_SRC}
		#${UTIL_HEADER}
		#${UTIL_SOURCE}
		)
