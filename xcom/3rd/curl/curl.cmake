get_filename_component(CURL_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(CURL_INC
		${CURL_CMAKE_DIR}
		${CURL_CMAKE_DIR}/include
		)

set(CURL_SRC
		${CURL_CMAKE_DIR}/tconnection.cpp
		${CURL_CMAKE_DIR}/tconnection_operation.cpp
		${CURL_CMAKE_DIR}/tconnection_operation_queue.cpp
		${CURL_CMAKE_DIR}/trequest.cpp
		${CURL_CMAKE_DIR}/tresponse.cpp
		)

if(WIN32)
	add_library(lib_curl STATIC IMPORTED)
	set(CURL_DIR ${CURL_CMAKE_DIR}/Windows)
	set(CURL_LIB ${CURL_DIR}/libcurl.lib)
elseif(APPLE)
	add_library(lib_curl STATIC IMPORTED)
	if(CMAKE_TOOLCHAIN_FILE)#编译iOS
		set(CURL_DIR ${CURL_CMAKE_DIR}/iOS)
	else()
		set(CURL_DIR ${CURL_CMAKE_DIR}/macOS)
	endif()
	set(CURL_LIB ${CURL_DIR}/libcurl.a)
else()
	add_library(lib_curl STATIC IMPORTED)
	if(CMAKE_TOOLCHAIN_FILE)#编译Android
		set(CURL_DIR ${CURL_CMAKE_DIR}/Android)
	else()
		set(CURL_DIR ${CURL_CMAKE_DIR}/Linux)
	endif()
	set(CURL_LIB ${CURL_DIR}/libcurl.a)
endif()

set_target_properties(lib_curl PROPERTIES IMPORTED_LOCATION ${CURL_LIB})