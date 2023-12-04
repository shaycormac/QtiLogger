#!/system/bin/sh

# 这个玩意 ，A310路径没有呀，只有 vendor/bin下面有，但是看rc源碼，好像都沒有機會執行過，所以暫時不管了
# 手机里也没有，是不是作者写错了？？？？
/system/bin/diag_mdlog -c -k
# stop 倒是有，但是怀疑是不是也写错了，应该是 vendor/bin/stop  ??
/system/bin/stop zxlogger
/system/bin/stop zxbootlogger

exit 0
