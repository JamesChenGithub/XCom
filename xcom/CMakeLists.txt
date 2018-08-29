#设置最小cmake版本
MESSAGE("\n\n============================")
MESSAGE("设置最小cmake版本 : cmake_minimum_required(VERSION 2.8)")
cmake_minimum_required(VERSION 2.8)

#设置自定义变量, 由build.sh PROJECT_PREFIX_NAME 传入
MESSAGE("工程前缀名:${PROJECT_PREFIX_NAME} 工程名大写为: ${PROJECT_UPPER_NAME}")

#设置平台工程名
MESSAGE ("设置平台工程名 : ${PROJECT_PREFIX_NAME}_${CMAKE_PLATFORM}")
project(${PROJECT_PREFIX_NAME}_${CMAKE_PLATFORM})

#设置C++11
set(CMAKE_CXX_STANDARD 11)

#设置cmake项
include(${PROJECT_PREFIX_NAME}.cmake)


#设置工程目录下：${PROJECT_PREFIX_NAME}.cmake项中配置的目录
MESSAGE("include 目录有:${${PROJECT_UPPER_NAME}_INC}")
include_directories(${${PROJECT_UPPER_NAME}_INC})


#设置依赖库
#set(LIBS lib_xcast)

#设置生成的头文件目录
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../libs/include)

#设置生成的文件目录
set(LIBS_DIR ${CMAKE_SOURCE_DIR}/../libs/${CMAKE_PLATFORM})

if(WIN32)#编译Windows
	add_definitions("/utf-8")
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

	add_library(${PROJECT_PREFIX_NAME} SHARED ${${PROJECT_UPPER_NAME}_SRC})

	set(LIBS ${LIBS}
			Ws2_32.lib
			)

	target_link_libraries(${PROJECT_PREFIX_NAME} ${LIBS})

	add_custom_command(TARGET ${PROJECT_PREFIX_NAME} POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E remove_directory ${LIBS_DIR}
			COMMAND "${CMAKE_COMMAND}" -E copy_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} ${LIBS_DIR}
			COMMENT "Copying library to output directory")

#COMMAND "${CMAKE_COMMAND}" -E copy ${XCAST_DIR}/xcast.dll ${XCAST_DIR}/SDL2.dll ${LIBS_DIR}

elseif(APPLE)
	add_definitions(-Wfatal-errors)
	
	#添加生成库
	message("添加生成库 : ${PROJECT_UPPER_NAME} === ${PROJECT_UPPER_NAME}_SRC === ${${PROJECT_UPPER_NAME}_SRC}  === ")
	message("添加生成库 : add_library(${PROJECT_PREFIX_NAME} STATIC ${${PROJECT_UPPER_NAME}_SRC})")

	add_library(${PROJECT_PREFIX_NAME} STATIC ${${PROJECT_UPPER_NAME}_SRC})

	if(CMAKE_TOOLCHAIN_FILE)#编译iOS
		set_xcode_property (${PROJECT_PREFIX_NAME} IPHONEOS_DEPLOYMENT_TARGET ${IOS_DEPLOYMENT_TARGET} "all")
	else()#编译macOS
		set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
	endif()

	add_custom_command(TARGET ${PROJECT_PREFIX_NAME} POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E remove_directory ${LIBS_DIR}
			COMMAND "${CMAKE_COMMAND}" -E copy_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} ${LIBS_DIR}
			COMMENT "Copying library to output directory")

#COMMAND "${CMAKE_COMMAND}" -E copy_directory ${XCAST_DIR}/xcast.framework ${LIBS_DIR}/xcast.framework
else()
	add_definitions(-Wfatal-errors)
	#add_definitions(-std=c++11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

	add_library(${PROJECT_PREFIX_NAME} SHARED ${${PROJECT_UPPER_NAME}_SRC})

	if(CMAKE_TOOLCHAIN_FILE)#编译Android
		set(LIBS ${LIBS}
				z
				android
				)
	else()#编译Linux
		add_custom_command(TARGET ${PROJECT_PREFIX_NAME} POST_BUILD
				COMMAND "${CMAKE_COMMAND}" -E remove_directory ${LIBS_DIR}
				COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:${PROJECT_PREFIX_NAME}> ${LIBS_DIR}/lib${PROJECT_PREFIX_NAME}.so
				COMMAND "${CMAKE_COMMAND}" -E copy ${XCAST_DIR}/libxcast.so ${LIBS_DIR}
				COMMENT "Copying library to output directory")
	endif()

	target_link_libraries(${PROJECT_PREFIX_NAME} ${LIBS})
endif()

add_custom_command(TARGET ${PROJECT_PREFIX_NAME} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E make_directory ${INCLUDE_DIR}
		COMMAND "${CMAKE_COMMAND}" -E copy ${${PROJECT_UPPER_NAME}_INCLUDE} ${INCLUDE_DIR}
		COMMENT "Copying header to output directory")
