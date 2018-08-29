get_filename_component(TIME_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
message("string设置 : ${TIME_CMAKE_DIR}")

set(TIME_INC
		${TIME_CMAKE_DIR}
		)

message("TIME_CMAKE_DIR : ${TIME_CMAKE_DIR}")

file(GLOB TIME_HEADER ${TIME_CMAKE_DIR}/*.h)
file(GLOB TIME_SOURCE ${TIME_CMAKE_DIR}/*.cpp)

set(TIME_SRC
		${TIME_HEADER}
		${TIME_SOURCE}
		)
