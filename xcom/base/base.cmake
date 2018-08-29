get_filename_component(BASE_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
message("base设置 : ${BASE_CMAKE_DIR}")



set(BASE_INC
		${XC_API_CMAKE_DIR}
		)

message("BASE_INC : ${BASE_INC}")

file(GLOB BASE_HEADER ${BASE_CMAKE_DIR}/*.h)
file(GLOB BASE_SOURCE ${BASE_CMAKE_DIR}/*.cpp)

set(BASE_SRC
		${BASE_HEADER}
		${BASE_SOURCE}
		)



