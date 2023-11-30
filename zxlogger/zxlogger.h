//
// Created by zhouxian on 21-4-16.
//

#ifndef __ZXLOGGER_H
#define __ZXLOGGER_H

#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/List.h>
#include <log/logprint.h>

using namespace android;

/*define log device base class*/
// _LogDeviceBase 是继承线程的一个子类
typedef class _LogDeviceBase : public Thread
{

private:
   // 线程名字
    String8 name;
    // 线程id
    pthread_t threadId;
    // 创建存放日志的目录
    int createDirectory( const String8& path, const String8& dir = String8("") );
    // 准备启动，虚方法
    virtual status_t readyToRun();

protected:
 // 日志的路径，所在目录，权限，名字以及大小
    String8 logPath;
    String8 logDir;
    String8 logMaskPath;
    String8 logFileName;
    unsigned int logMaxSize;
// 日志所属与的类型
    String8 mode;
    // 最大日志个数
    int maxFiles;
    // 自动生成的时间辍
    int generateTimestamp( String8& timeStamp );
    // 这是干啥的？
    int split_string(char *split_str[],int split_max_num, char *str, char c);
    // 核心的处理文件
    int readFile( const String8& file );

public:

    _LogDeviceBase( const String8& devName );
    virtual ~_LogDeviceBase();
    // 线程名字？
    String8 getName( void );
    int setMode( const String8& _mode );
    int setMaxFiles( int max );
    int setLogPath( const String8& path );
    int setLogMaskPath( const String8& maskPath );
    int setLogMaxSize( unsigned int size ); 
    int setLogDirectory( const String8& dir );
    int setLogFileName( const String8& fileName );


}LogDeviceBase;

/*-------------------------------------------------------------------------------*/

/*define kmsg log device class*/
typedef class _KmsgLogDevice : public LogDeviceBase
{

public:

  // 赋值给线程的名字
    _KmsgLogDevice( const String8& devName = String8("dmesg") ):LogDeviceBase( devName ){};
    // 需要子类实现，虚方法
    virtual bool threadLoop();

}KmsgLogDevice;

/*define Qsee log device class*/
typedef class _QseeLogDevice : public LogDeviceBase
{

public:
    _QseeLogDevice( const String8& devName = String8("qsee") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();
}QseeLogDevice;

/*define Tz Log device class*/
typedef class _TzLogDevice : public LogDeviceBase
{

public:
    _TzLogDevice( const String8& devName = String8("tz") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();
}TzLogDevice;

/*define modem log device class*/
typedef class _ModemLogDevice : public LogDeviceBase
{

public:

    _ModemLogDevice( const String8& devName = String8("modem") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();

}ModemLogDevice;

/*define bugreport log device class*/
typedef class _BugReportDevice : public LogDeviceBase
{

public:

    _BugReportDevice( const String8& devName = String8("bugreport") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();

}BugReportDevice;


/*define net log device class*/
typedef class _NetDevice : public LogDeviceBase
{

public:

    _NetDevice( const String8& devName = String8("net") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();

}NetDevice;

/*define dynamic class*/
typedef class _DynamicDevice: public LogDeviceBase
{

private:

    typedef struct _keyProp
    {
        const String8 key;
        const String8 keyPath;
        const String8 keyValuePrefix;
        const String8 keyValueSubfix;

    }keyProp;

    static const int maxKeyNum;
    static struct _keyProp keys[];

    int parseMaskFile( const String8& maskFile );
    int writeFile( const String8& path, const String8& value );
    int getKeyPath( const String8& key, String8& out );
    int getKeyValue( const String8& key, const String8& value, String8& out );

public:

        _DynamicDevice( const String8& devName = String8("dynamic") ):LogDeviceBase( devName ){};
        virtual bool threadLoop();

}DynamicDevice;

/*define main log device class*/
typedef class _MainLogDevice : public LogDeviceBase
{

public:

    _MainLogDevice( const String8& devName = String8("main") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();

}MainLogDevice;


/*define radio log device class*/
typedef class _RadioLogDevice : public LogDeviceBase
{

public:

    _RadioLogDevice( const String8& devName = String8("radio") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();

}RadioLogDevice;


/*define event log device class*/
typedef class _EventLogDevice : public LogDeviceBase
{

public:

    _EventLogDevice( const String8& devName = String8("event") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();

}EventLogDevice;

/*define system log device class*/
typedef class _SystemLogDevice : public LogDeviceBase
{

public:

    _SystemLogDevice( const String8& devName = String8("system") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();

}SystemLogDevice;

/*define crash log device class*/
typedef class _CrashLogDevice : public LogDeviceBase
{

public:

    _CrashLogDevice( const String8& devName = String8("crash") ):LogDeviceBase( devName ){};
    virtual bool threadLoop();

}CrashLogDevice;

#endif
