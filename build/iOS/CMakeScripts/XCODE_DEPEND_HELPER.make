# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.xcom.Debug:
/Users/alexichen/UnixSpace/XCom/build/iOS/Debug${EFFECTIVE_PLATFORM_NAME}/libxcom.a:
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/Debug${EFFECTIVE_PLATFORM_NAME}/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/Debug/xcom.build/Objects-normal/armv7/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/Debug/xcom.build/Objects-normal/armv7s/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/Debug/xcom.build/Objects-normal/arm64/libxcom.a


PostBuild.xcom.Release:
/Users/alexichen/UnixSpace/XCom/build/iOS/Release${EFFECTIVE_PLATFORM_NAME}/libxcom.a:
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/Release${EFFECTIVE_PLATFORM_NAME}/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/Release/xcom.build/Objects-normal/armv7/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/Release/xcom.build/Objects-normal/armv7s/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/Release/xcom.build/Objects-normal/arm64/libxcom.a


PostBuild.xcom.MinSizeRel:
/Users/alexichen/UnixSpace/XCom/build/iOS/MinSizeRel${EFFECTIVE_PLATFORM_NAME}/libxcom.a:
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/MinSizeRel${EFFECTIVE_PLATFORM_NAME}/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/MinSizeRel/xcom.build/Objects-normal/armv7/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/MinSizeRel/xcom.build/Objects-normal/armv7s/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/MinSizeRel/xcom.build/Objects-normal/arm64/libxcom.a


PostBuild.xcom.RelWithDebInfo:
/Users/alexichen/UnixSpace/XCom/build/iOS/RelWithDebInfo${EFFECTIVE_PLATFORM_NAME}/libxcom.a:
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/RelWithDebInfo${EFFECTIVE_PLATFORM_NAME}/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/RelWithDebInfo/xcom.build/Objects-normal/armv7/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/RelWithDebInfo/xcom.build/Objects-normal/armv7s/libxcom.a
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/iOS/xcom_iOS.build/RelWithDebInfo/xcom.build/Objects-normal/arm64/libxcom.a




# For each target create a dummy ruleso the target does not have to exist
