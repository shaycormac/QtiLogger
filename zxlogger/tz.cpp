//
// Created by zhouxian on 21-4-16.
//

#define LOG_TAG "zxlogger"

#include <cutils/properties.h>

//#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include <utils/Log.h>
#include <utils/threads.h>

#if defined(HAVE_PTHREADS)
# include <pthread.h>
# include <sys/resource.h>
#endif

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "zxlogger.h"


using namespace android;
/**
 *  todo 所以这个日志看看是否要拿掉！！
 * @return
 */
bool TzLogDevice::threadLoop()
{
    printf( "%s threadLoop run!\n", getName().string() );
   // 这个是TrustZone 日志，可是目前A310上 d下面是空的目录，啥也没有，不像普通手机那样
    // sc126:/ # cd d
    // system/bin/sh: cd: /d: No such file or directory
    // 2|sc126:/ # cd /sys/kernel/debug
    // system/bin/sh: cd: /sys/kernel/debug: No such file or directory
    readFile( String8("/d/tzdbg/log") );

    for ( ;; )
    {
        sleep( 60 );
    }

    printf( "%s threadLoop exit!\n", getName().string() );

    return 0;
}


