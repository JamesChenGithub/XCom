#!/usr/bin/env bash

#############################################
#设置变量
#设置当前目录
WORK_DIR=`pwd`
echo "当前目录:${WORK_DIR}"

#设置工程名
PROJ_NAME=xcom
PROJECT_UPPER_NAME=`echo ${PROJ_NAME} | tr "[a-z]" "[A-Z]"`
echo "当前项目名称:${PROJ_NAME} ${PROJECT_UPPER_NAME}"
#设置源代码目录
TARGET_DIR=$WORK_DIR/${PROJ_NAME}
echo "当前源代码目录:${TARGET_DIR}"

#设置构建类型
BUILD_TYPE=Release

GEN_ONLY=

TARGETS=

#############################################
#函数区

function build_target
{
    BuildFolder="build"
    BuildDir=${WORK_DIR}/${BuildFolder}
    mkdir -p ${BuildFolder}
    cd build

    OUT_DIR=$WORK_DIR/libs/include
    rm -rf $OUT_DIR

    OUT_DIR=$WORK_DIR/libs/$1
    rm -rf $OUT_DIR

    echo `date +"%Y-%m-%d %H:%M:%S"` "正在构建目标($1)"

    if [ "$1"x = "iOS"x ]; then

        build_lib "iOS" "SIMULATOR"
        mv ${BuildDir}/$1/Release-iphonesimulator/lib${PROJ_NAME}.a $OUT_DIR/../lib${PROJ_NAME}_sim.a

        build_lib "iOS" "SIMULATOR64"
        mv ${BuildDir}/$1/Release-iphonesimulator/lib${PROJ_NAME}.a $OUT_DIR/../lib${PROJ_NAME}_sim64.a

        build_lib "iOS" "OS"
        mv ${BuildDir}/$1/Release-iphoneos/lib${PROJ_NAME}.a   $OUT_DIR/../lib${PROJ_NAME}_os.a

        echo `date +"%Y-%m-%d %H:%M:%S"`" 正在合并fat包..."
        lipo -create $OUT_DIR/../lib${PROJ_NAME}_os.a $OUT_DIR/../lib${PROJ_NAME}_sim.a $OUT_DIR/../lib${PROJ_NAME}_sim64.a -output $OUT_DIR/lib${PROJ_NAME}.a
        rm -f $OUT_DIR/../lib${PROJ_NAME}_os.a $OUT_DIR/../lib${PROJ_NAME}_sim.a $OUT_DIR/../lib${PROJ_NAME}_sim64.a

        echo "构建${PROJ_NAME}.framework"
        mkdir $OUT_DIR/${PROJ_NAME}.framework
        cp $OUT_DIR/lib${PROJ_NAME}.a  $OUT_DIR/${PROJ_NAME}.framework/
        mv $OUT_DIR/${PROJ_NAME}.framework/lib${PROJ_NAME}.a $OUT_DIR/${PROJ_NAME}.framework/${PROJ_NAME}

        mkdir $OUT_DIR/${PROJ_NAME}.framework/Headers
        cp -r $WORK_DIR/libs/include/  $OUT_DIR/${PROJ_NAME}.framework/Headers/

    elif [ "$1"x = "macOS"x ]; then
        build_lib "macOS"
        #修改Deployment Target为10.8
        sed -i "" 's/LIBRARY_STYLE = STATIC;/LIBRARY_STYLE = STATIC;MACOSX_DEPLOYMENT_TARGET = 10.8;/' $WORK_DIR/build/macOS/${PROJ_NAME}_macOS.xcodeproj/project.pbxproj

        echo "构建${PROJ_NAME}.framework"
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


function build_lib
{
    rm -rf $1
    mkdir -p $1
    cd $1

    CMAKE=cmake

    echo `date +"%Y-%m-%d %H:%M:%S"` "正在生成项目($1)"
    echo "$TARGET_DIR"
    if [ "$1"x = "iOS"x ]; then
        echo "$CMAKE -G \"Xcode\" $TARGET_DIR \
            -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
            -DCMAKE_PLATFORM=\"$1\" \
            -DCMAKE_TOOLCHAIN_FILE=$WORK_DIR/toolchains/ios.toolchain.cmake \
            -DIOS_PLATFORM=\"$2\" \
            -DENABLE_BITCODE=false \
            -DIOS_DEPLOYMENT_TARGET=\"8.0\" \
            -DPROJECT_PREFIX_NAME=${PROJ_NAME} \
            -DPROJECT_UPPER_NAME=${PROJECT_UPPER_NAME}"

        $CMAKE -G "Xcode" $TARGET_DIR \
            -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
            -DCMAKE_PLATFORM="$1" \
            -DCMAKE_TOOLCHAIN_FILE=$WORK_DIR/toolchains/ios.toolchain.cmake \
            -DIOS_PLATFORM="$2" \
            -DENABLE_BITCODE=false \
            -DIOS_DEPLOYMENT_TARGET="8.0" \
            -DPROJECT_PREFIX_NAME=${PROJ_NAME} \
            -DPROJECT_UPPER_NAME=${PROJECT_UPPER_NAME}
    elif [ "$1"x = "macOS"x ]; then
        echo "$CMAKE -G \"Xcode\" $TARGET_DIR \
            -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
            -DCMAKE_PLATFORM=\"$1\" \
            -DCMAKE_OSX_DEPLOYMENT_TARGET=\"10.8\" \
            -DPROJECT_PREFIX_NAME=${PROJ_NAME}\
            -DPROJECT_UPPER_NAME=${PROJECT_UPPER_NAME}"

        $CMAKE -G "Xcode" $TARGET_DIR \
            -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
            -DCMAKE_PLATFORM="$1" \
            -DCMAKE_OSX_DEPLOYMENT_TARGET="10.8" \
            -DPROJECT_PREFIX_NAME=${PROJ_NAME} \
            -DPROJECT_UPPER_NAME=${PROJECT_UPPER_NAME}
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

function check_result
{
    if [[ $? -ne 0 ]]; then
        echo `date +"%Y-%m-%d %H:%M:%S"` $*
        exit 1
    fi
}


#############################################

#获取当前系统
SYSTEM=`uname -s`
#打印参数列表
echo "$*"
if [ -z "$*" ]; then
    if [ "$SYSTEM"x = "Darwin"x ]; then
        #默认构建macOS
        TARGETS="macOS"
    elif [ "$SYSTEM"x = "Linux"x ]; then
        #默认构建Linux
        TARGETS="Linux"
    fi
fi
#############################################
#检查
#检查传递给脚本的参数个数
while [ $# -gt 0 ];do
    case $1 in
        -g)
            #没有运行到?
            echo "GEN_ONLY=true"
            GEN_ONLY=true
            ;;
        -d)
            #没有运行到?
            echo "BUILD_TYPE=Debug"
            BUILD_TYPE=Debug
            ;;
        -s)
            #没有运行到?
            echo "编译speed_test"
            TARGET_DIR=$WORK_DIR/test/speed_test
            PROJ_NAME=speed_test
            ;;

        #macOS上可以编译macos/ios/linux/android
        iOS)
            #编iOS
            if [ "$SYSTEM"x = "Darwin"x ]; then
                TARGETS="$TARGETS iOS"
                echo "构建iOS"
            else
                echo `date +"%Y-%m-%d %H:%M:%S"` "当前平台下无法构建iOS目标"
            fi
            ;;
        macOS)
            if [ "$SYSTEM"x = "Darwin"x ]; then
                TARGETS="$TARGETS macOS"
                echo "构建macOS"
            else
                echo `date +"%Y-%m-%d %H:%M:%S"` "当前平台下无法构建macOS目标"
            fi
            ;;
        Android)
            TARGETS="$TARGETS Android"
            echo "构建Android"
            ;;
        Linux)
            if [ "$SYSTEM"x = "Linux"x ]; then
                TARGETS="$TARGETS Linux"
                echo "构建Android"
            else
                echo `date +"%Y-%m-%d %H:%M:%S"` "当前平台下无法构建Linux目标"
            fi
            ;;
        xlive_sdk)
            TARGET_DIR=$WORK_DIR/xlive_xcast
            echo "未构建${TARGET_DIR}"
            ;;
        *)
            echo "无效参数: $1"
            ;;
    esac
    shift
done

echo "本次要构建的目标是:${TARGETS}"
for TARGET in $TARGETS
do
    echo "开始构建: $TARGETS"
    build_target $TARGET
done
