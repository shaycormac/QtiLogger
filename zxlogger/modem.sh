#!/system/bin/sh

# 这个玩意 ，A310路径没有呀，只有 vendor/bin下面有
/system/bin/diag_mdlog -c -k
# 这两个有
/system/bin/stop zxlogger
/system/bin/stop zxbootlogger

exit 0
