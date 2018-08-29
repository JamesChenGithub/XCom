# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.xcom.Debug:
/Users/alexichen/UnixSpace/XCom/build/macOS/Debug/libxcom.a:
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/macOS/Debug/libxcom.a


PostBuild.xcom.Release:
/Users/alexichen/UnixSpace/XCom/build/macOS/Release/libxcom.a:
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/macOS/Release/libxcom.a


PostBuild.xcom.MinSizeRel:
/Users/alexichen/UnixSpace/XCom/build/macOS/MinSizeRel/libxcom.a:
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/macOS/MinSizeRel/libxcom.a


PostBuild.xcom.RelWithDebInfo:
/Users/alexichen/UnixSpace/XCom/build/macOS/RelWithDebInfo/libxcom.a:
	/bin/rm -f /Users/alexichen/UnixSpace/XCom/build/macOS/RelWithDebInfo/libxcom.a




# For each target create a dummy ruleso the target does not have to exist
