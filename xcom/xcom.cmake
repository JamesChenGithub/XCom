# 1. 获取当前目录
get_filename_component(XCOM_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
message("xcom设置 : ${XCOM_CMAKE_DIR}")

# 2. 如果有子目录，添加相应子目录的cmake 
include(${XCOM_CMAKE_DIR}/base/base.cmake)
#include(${XCOM_CMAKE_DIR}/log/log.cmake)
include(${XCOM_CMAKE_DIR}/util/util.cmake)
#include(${XCOM_CMAKE_DIR}/platform/platform.cmake)

# 3. 添加子目录的文件到INC
set(XCOM_INC
		${XCOM_CMAKE_DIR}
		${BASE_INC}
		${UTIL_INC}
		)

message("设置XCOM_INC : ${XCOM_INC}")

# 4. 添加子目录INCLUDE
set(XCOM_INCLUDE
		${UTIL_INCLUDE}
		${BASE_HEADER}
		)

#${XCOM_CMAKE_DIR}/base/*.h

# 5. 设置当前目录的源代码
file(GLOB XCOM_HEADER ${XCOM_CMAKE_DIR}/*.h)
file(GLOB XCOM_SOURCE ${XCOM_CMAKE_DIR}/*.cpp)

# 6. 添加源代码
set(XCOM_SRC
		${BASE_SRC}
		${UTIL_SRC}
		#${XCOM_HEADER}
		#${XCOM_SOURCE}
		)

