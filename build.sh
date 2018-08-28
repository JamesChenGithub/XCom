#!/usr/bin/env bash

#检查命令行执行结果，失败后打印信息并退出


function check_result
{
    if [[ $? -ne 0 ]]; then
        echo `date +"%Y-%m-%d %H:%M:%S"` $*
        exit 1
    fi
}

function build_lib
{
	rm -rf $1
	mkdir -p $1
	cd $1

	CMAKE=cmake

	echo `date +"%Y-%m-%d %H:%M:%S"` "正在生成项目($1)"
	if [ "$1"x = "iOS"x ]; then
		$CMAKE -G "Xcode" $TARGET_DIR \
			-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
			-DCMAKE_PLATFORM="$1" \
			-DCMAKE_TOOLCHAIN_FILE=$WORK_DIR/toolchains/ios.toolchain.cmake \
			-DIOS_PLATFORM="$2" \
			-DENABLE_BITCODE=false \
			-DIOS_DEPLOYMENT_TARGET="8.0"
	elif [ "$1"x = "macOS"x ]; then
		$CMAKE -G "Xcode" $TARGET_DIR \
			-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
			-DCMAKE_PLATFORM="$1" \
			-DCMAKE_OSX_DEPLOYMENT_TARGET="10.8"
	elif [ "$1"x = "Android"x ]; then
		if [ -z $ANDROID_SDK_HOME ]; then
			echo `date +"%Y-%m-%d %H:%M:%S"` "找不到环境变量：ANDROID_SDK_HOME"
			exit 1
		fi
		if [ -z $ANDROID_NDK_HOME ]; then
			echo `date +"%Y-%m-%d %H:%M:%S"` "找不到环境变量：ANDROID_NDK_HOME"
			exit 1
		fi
		rm -rf $TARGET_DIR/jar/local.properties
		echo -e "ndk.dir=$ANDROID_NDK_HOME\nsdk.dir=$ANDROID_SDK_HOME" > $TARGET_DIR/jar/local.properties
	elif [ "$1"x = "Linux"x ]; then
		$CMAKE $TARGET_DIR \
			-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
			-DCMAKE_PLATFORM="$1" \
			-DCMAKE_CXX_COMPILER=gcc
	fi
	check_result "生成失败"

	if [ -z "$GEN_ONLY" ]; then

		echo `date +"%Y-%m-%d %H:%M:%S"` "正在编译安装"
		if [ "$1"x = "Android"x ]; then
			$TARGET_DIR/jar/gradlew -p $TARGET_DIR/jar build
		else
			$CMAKE --build . --config $BUILD_TYPE
		fi
		check_result "编译安装失败"

	fi

	cd ..
	echo `date +"%Y-%m-%d %H:%M:%S"` "库构建完成($1)"
}

function build_target
{
	mkdir -p build
	cd build

    OUT_DIR=$WORK_DIR/libs/include
    echo ${OUT_DIR}
    rm -rf $OUT_DIR

	OUT_DIR=$WORK_DIR/libs/$1
    echo ${OUT_DIR}
	rm -rf $OUT_DIR

	echo `date +"%Y-%m-%d %H:%M:%S"` "正在构建目标($1)"
	if [ "$1"x = "iOS"x ]; then
        #修改Deployment Target为8.0
        sed -i "" 's/SDKROOT = \/Applications\/Xcode.app/IPHONEOS_DEPLOYMENT_TARGET = 8.0;SDKROOT = \/Applications\/Xcode.app/' $WORK_DIR/build/iOS/${PROJ_NAME}_iOS.xcodeproj/project.pbxproj

        build_lib "iOS" "SIMULATOR"
        mv $OUT_DIR/../../build/$1/Release-iphonesimulator/lib${PROJ_NAME}.a $OUT_DIR/../lib${PROJ_NAME}_sim.a
        build_lib "iOS" "SIMULATOR64"
        mv $OUT_DIR/../../build/$1/Release-iphonesimulator/lib${PROJ_NAME}.a $OUT_DIR/../lib${PROJ_NAME}_sim64.a
        build_lib "iOS" "OS"
        mv $OUT_DIR/../../build/$1/Release-iphoneos/lib${PROJ_NAME}.a   $OUT_DIR/../lib${PROJ_NAME}_os.a
        echo `date +"%Y-%m-%d %H:%M:%S"`" 正在合并fat包..."
        lipo -create $OUT_DIR/../lib${PROJ_NAME}_os.a $OUT_DIR/../lib${PROJ_NAME}_sim.a $OUT_DIR/../lib${PROJ_NAME}_sim64.a -output $OUT_DIR/lib${PROJ_NAME}.a
        rm -f $OUT_DIR/../lib${PROJ_NAME}_os.a $OUT_DIR/../lib${PROJ_NAME}_sim.a $OUT_DIR/../lib${PROJ_NAME}_sim64.a


        mkdir $OUT_DIR/${PROJ_NAME}.framework
        cp $OUT_DIR/lib${PROJ_NAME}.a  $OUT_DIR/${PROJ_NAME}.framework/
        mv $OUT_DIR/${PROJ_NAME}.framework/lib${PROJ_NAME}.a $OUT_DIR/${PROJ_NAME}.framework/${PROJ_NAME}

        mkdir $OUT_DIR/${PROJ_NAME}.framework/Headers
        cp -r $WORK_DIR/libs/include/  $OUT_DIR/${PROJ_NAME}.framework/Headers/

	elif [ "$1"x = "macOS"x ]; then
		build_lib "macOS"
		#修改Deployment Target为10.8
		sed -i "" 's/LIBRARY_STYLE = STATIC;/LIBRARY_STYLE = STATIC;MACOSX_DEPLOYMENT_TARGET = 10.8;/' $WORK_DIR/build/macOS/${PROJ_NAME}_macOS.xcodeproj/project.pbxproj

        mkdir $OUT_DIR/${PROJ_NAME}.framework
        cp $OUT_DIR/lib${PROJ_NAME}.a  $OUT_DIR/${PROJ_NAME}.framework/
        mv $OUT_DIR/${PROJ_NAME}.framework/lib${PROJ_NAME}.a $OUT_DIR/${PROJ_NAME}.framework/${PROJ_NAME}

        mkdir $OUT_DIR/${PROJ_NAME}.framework/Headers
        cp -r $WORK_DIR/libs/include/  $OUT_DIR/${PROJ_NAME}.framework/Headers/
	else
		build_lib "$1"
	fi

	cd ..
	echo `date +"%Y-%m-%d %H:%M:%S"` "目标构建完成($1)"
}

WORK_DIR=$(cd $(dirname $BASH_SOURCE); pwd)
TARGET_DIR=$WORK_DIR/xcom
PROJ_NAME=xcom
BUILD_TYPE=Release
GEN_ONLY=

SYSTEM=`uname -s`
if [ -z "$*" ]; then
	if [ "$SYSTEM"x = "Darwin"x ]; then
		TARGETS="macOS"
	elif [ "$SYSTEM"x = "Linux"x ]; then
		TARGETS="Linux"
	fi
fi


while [ $# -gt 0 ];do
	case $1 in
		-g)
			GEN_ONLY=true
			;;
		-d)
			BUILD_TYPE=Debug
			;;
		-s)
			TARGET_DIR=$WORK_DIR/test/speed_test
			PROJ_NAME=speed_test
			;;
		iOS)
			if [ "$SYSTEM"x = "Darwin"x ]; then
				TARGETS="$TARGETS iOS"
			else
				echo `date +"%Y-%m-%d %H:%M:%S"` "当前平台下无法构建iOS目标"
			fi
			;;
		macOS)
			if [ "$SYSTEM"x = "Darwin"x ]; then
				TARGETS="$TARGETS macOS"
			else
				echo `date +"%Y-%m-%d %H:%M:%S"` "当前平台下无法构建macOS目标"
			fi
			;;
		Android)
			TARGETS="$TARGETS Android"
			;;
		Linux)
			if [ "$SYSTEM"x = "Linux"x ]; then
				TARGETS="$TARGETS Linux"
			else
				echo `date +"%Y-%m-%d %H:%M:%S"` "当前平台下无法构建Linux目标"
			fi
			;;
		xcom_sdk)
			TARGET_DIR=$WORK_DIR/xcom
			;;
		*)
			echo "无效参数: $1"
			;;
	esac
	shift
done

for TARGET in $TARGETS
do
    echo "build $TARGETS"
	build_target $TARGET
done

