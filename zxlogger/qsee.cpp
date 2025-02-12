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
 *   todo 考虑要不要拿掉，没有相关路径
 * @return
 */
bool QseeLogDevice::threadLoop()
{
    printf( "%s threadLoop run!\n", getName().string() );

    // 这个玩意，好像没有啊！！，对的，这个是拿QSSE日志的，但是板子下面根本就没有这个路径
    // A227这个路径是由的
    readFile( String8("/d/tzdbg/qsee_log") );

    for ( ;; )
    {
        sleep( 60 );
    }

    printf( "%s threadLoop exit!\n", getName().string() );

    return 0;
}


