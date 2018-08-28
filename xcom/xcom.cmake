get_filename_component(XCOM_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)


include(${XCOM_CMAKE_DIR}/base/base.cmake)

#include(${XCOM_CMAKE_DIR}/log/log.cmake)
#include(${XCOM_CMAKE_DIR}/util/util.cmake)
#include(${XCOM_CMAKE_DIR}/platform/util.cmake)


set(XCOM_INC
		${XCOM_CMAKE_DIR}
		${XCOM_BASE_INC}

		#${XCOM_LOG_INC}
		#${COMM_UTIL_INC}
		#${COMM_PLATFORM_INC}
		)

#set(XCOM_INCLUDE
		#${XCOM_CMAKE_DIR}/xlive_callback.h
		#${XCOM_CMAKE_DIR}/xlive_comm.h
		#${XCOM_CMAKE_DIR}/xlive_xcast.h
		#${XCOM_CMAKE_DIR}/xlive_string.h
		#${XCOM_CMAKE_DIR}/xlive_log.h
		#${XCOM_CMAKE_DIR}/xlive_version.h
		#${XCOM_CMAKE_DIR}/xlive.h
		)

#file(GLOB XCOM_HEADER ${XCOM_CMAKE_DIR}/base/inc/*.h)
#file(GLOB PLATFORMS_HEADER ${PLATFORMS_CMAKE_DIR}/xlive_mainthread.h)
#file(GLOB XCOM_SOURCE ${XCOM_CMAKE_DIR}/*.cpp)

set(XCOM_SRC
		${XCOM_BASE_INC}
		#${XC_API_SRC}
		#${XCOM_HEADER}
		#${PLATFORMS_HEADER}
		#${XCOM_SOURCE}
		)

