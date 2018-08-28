cmake_minimum_required(VERSION 2.8)
project(xcom_${CMAKE_PLATFORM})

#设置C++11 
set(CMAKE_CXX_STANDARD 11)

#设置make
include(xcom.cmake)

#设置头文件
include_directories(${XCOM_INC})

# 添加依赖库
#set(LIBS lib_xcast)

#设置导出头文件以及包地址
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../libs/include)
set(LIBS_DIR ${CMAKE_SOURCE_DIR}/../libs/${CMAKE_PLATFORM})

if(WIN32)#编译Windows
	add_definitions("/utf-8")
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

	add_library(xcom SHARED ${XCOM_SRC})

	set(LIBS ${LIBS}
			Ws2_32.lib
			)

	target_link_libraries(xcom ${LIBS})

	add_custom_command(TARGET xcom POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E remove_directory ${LIBS_DIR}
			COMMAND "${CMAKE_COMMAND}" -E copy_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} ${LIBS_DIR}
			#COMMAND "${CMAKE_COMMAND}" -E copy ${XCAST_DIR}/xcast.dll ${XCAST_DIR}/SDL2.dll ${LIBS_DIR}
			COMMENT "Copying library to output directory")
elseif(APPLE)
	add_definitions(-Wfatal-errors)
	add_library(xcom STATIC ${XCOM_SRC})

	if(CMAKE_TOOLCHAIN_FILE)#编译iOS
		set_xcode_property (xcom IPHONEOS_DEPLOYMENT_TARGET ${IOS_DEPLOYMENT_TARGET} "all")
	else()#编译macOS
		set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
	endif()

	add_custom_command(TARGET xcom POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E remove_directory ${LIBS_DIR}
			COMMAND "${CMAKE_COMMAND}" -E copy_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} ${LIBS_DIR}
			#COMMAND "${CMAKE_COMMAND}" -E copy_directory ${XCAST_DIR}/xcast.framework ${LIBS_DIR}/xcast.framework
			COMMENT "Copying library to output directory")
else()
	add_definitions(-Wfatal-errors)
	#add_definitions(-std=c++11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

	add_library(xcom SHARED ${XCOM_SRC})

	if(CMAKE_TOOLCHAIN_FILE)#编译Android
		set(LIBS ${LIBS}
				z
				android
				)
	else()#编译Linux
		add_custom_command(TARGET com POST_BUILD
				COMMAND "${CMAKE_COMMAND}" -E remove_directory ${LIBS_DIR}
				COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:xcom> ${LIBS_DIR}/libxcom.so
				#COMMAND "${CMAKE_COMMAND}" -E copy ${XCAST_DIR}/libxcast.so ${LIBS_DIR}
				COMMENT "Copying library to output directory")
	endif()

	target_link_libraries(xcom ${LIBS})
endif()

add_custom_command(TARGET xcom POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory ${INCLUDE_DIR}
		COMMAND "${CMAKE_COMMAND}" -E copy ${XCOM_INCLUDE} ${INCLUDE_DIR}
		COMMENT "Copying header to output directory")
