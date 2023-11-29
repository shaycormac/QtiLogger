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

bool BugReportDevice::threadLoop()
{
    ALOGD( "%s threadLoop run!\n", getName().string() );

    // 看看真正机器下面有这个路径的可执行文件么 ,有的
    const String8 bugreport("/system/bin/bugreport > ");
    String8 timeStamp("");
    generateTimestamp( timeStamp );
    String8 cmd("");

    cmd = bugreport + logPath + "/" + logDir + "/bugreport_"
          + timeStamp;
    ALOGD("bugreport cmd is  %s \n", cmd.string() );

    system( cmd.string() );

    for ( ;; )
    {
        sleep( 60 );
    }

    ALOGD( "%s threadLoop exit!\n", getName().string() );

    return 0;

}
