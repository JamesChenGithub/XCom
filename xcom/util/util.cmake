get_filename_component(XLIVE_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)


include(${XLIVE_CMAKE_DIR}/xc_api/xc_api.cmake)
include(${XLIVE_CMAKE_DIR}/comm/comm.cmake)


set(XLIVE_INC
		${XLIVE_CMAKE_DIR}
		${XC_API_INC}
		${COMM_INC}
		)

set(XLIVE_INCLUDE
		${XLIVE_CMAKE_DIR}/xlive_callback.h
		${XLIVE_CMAKE_DIR}/xlive_comm.h
		${XLIVE_CMAKE_DIR}/xlive_xcast.h
		${XLIVE_CMAKE_DIR}/xlive_string.h
		${XLIVE_CMAKE_DIR}/xlive_log.h
		${XLIVE_CMAKE_DIR}/xlive_version.h
		${XLIVE_CMAKE_DIR}/xlive.h
		)

file(GLOB XLIVE_HEADER ${XLIVE_CMAKE_DIR}/*.h)
file(GLOB PLATFORMS_HEADER ${PLATFORMS_CMAKE_DIR}/xlive_mainthread.h)
file(GLOB XLIVE_SOURCE ${XLIVE_CMAKE_DIR}/*.cpp)

set(XLIVE_SRC
		${COMM_SRC}
		${XC_API_SRC}
		${XLIVE_HEADER}
		${PLATFORMS_HEADER}
		${XLIVE_SOURCE}
		)

