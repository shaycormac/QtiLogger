//
// Created by zhouxian on 21-4-16.
//

#ifndef __CONFIGDATA_H
#define __CONFIGDATA_H

#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/List.h>
#include <log/logprint.h>

using namespace android;

typedef class _DATA
{

private:

    typedef struct _CommonData
    {
      // 日志名称
        String8 logName;
        // 日志最大长度
        unsigned int logMaxSize;
        // 日志是否可用
        bool logEnable;

        // 构造方法
        _CommonData( const String8& _logName, unsigned int size )
        {
            logName = _logName.string();
            logEnable = false;
            logMaxSize = size;
        }

    }CommonData;

    // 默认的日志大小，只要初始化一次即可，默认是12M,在实现的cpp中初始化
    const static unsigned int defaultLogMaxSize;

    // 配置的名称
    String8 name;
 // 日志路径
    String8 logPath;
    // modem 权限掩码
    String8 modemLogMaskPath;
    // kenrel 衡量方法的权限掩码路径
    String8 dynamicLogMaskPath;
    // 本日志系统的支持几个模式，包括boot,，ota省级，关机充电,recover日志，正常模式共5种
    String8 mode;/*zxlogger running mode,support boot,ota,poweroffcharge,recovery and normal mode*/
    // 最大可以支持的文件个数
    int maxFiles;/*the max log files that can be save,normally be use in special mode*/

    // 集合嘛
    List<struct _CommonData> CommonDataList;
    // 属性集合
    List<String8> PropConfigDataList;

    // 虚方法，添加一个配置，默认大小12M
    int addCommonData( const String8& _logName, unsigned int size = defaultLogMaxSize );
    // 日志权限路径是否正确
    int isVailLogMaskPath(const String8& str);

protected:
   // 分割？
    int split(const String8& str, const String8& pattern);
    // 使用特殊的日志掩码权限
    int userSpecifyLogMask( void );

public:
    // 默认构造方法
    _DATA( const String8& _name = String8("") )
    {
        printf( "%s Constructors!\n" , _name.string() );
        ALOGD( "%s Constructors!\n" , _name.string() );
        name = _name.string();
        maxFiles = 0;
    }
    // 解构方法
    ~_DATA()
    {
        printf( "%s Destructors!\n", name.string() );
        ALOGD( "%s Destructors!\n" , name.string() );
    }

    // 初始化
    int init( void );
    // 配置日志系统模式
    int configMode( const String8& _mode );
    // 配置最大支持文件个数
    int configMaxFiles( int max );
    // 配置日志路径
    int configLogPath( const String8& path );
    int configModemLogMaskPath( const String8& path );
    int configDynamicLogMaskPath( const String8& path );
    int configLogEnable( const String8& name, bool enable );
    // 上面的重载方法
    int configLogMaxSize( const String8& name, unsigned int size );

    int getLogPath( String8& path );
    int getModemLogMaskPath( String8& path );
    int getDynamicLogMaskPath( String8& path );
    unsigned int getLogMaxSize( const String8& name );
    bool isLogEnable( const String8& name );
    int getMode( String8& _mode );
    int getMaxFiles( void );

}DATA;

/**
 *  继承DATA的一个 argvData 参数，用于init.rc取值
 *  模式或者路径
 */
typedef class _ArgvData : public DATA
{
    /*support argv: <mode=boot> <path=/data/local/tmp>*/
private:

    typedef enum
    {
        e_ArgvMode,
        e_ArgvPath,
        e_ArgvMax,

    }e_Argv;

    typedef struct _supportArgv
    {
        String8 Argv;
        e_Argv eArgv;
    }supportArgv;

    String8 mode;
    String8 path;

    static supportArgv Argvs[];

    e_Argv getArgvType( const String8& argv );
    int saveArgv( const String8& key, const String8& value );

public:

  // 这个玩意的配置名字就是argv
    _ArgvData():DATA( String8("argv") ){};
    // 读取数据
    int read( int argc, char ** argv );
    // 是否是特殊模式
    bool isSpecialMode( String8& out );
    // 拿到路径
    int getPath( String8& out );

}ArgvData;

/**
 *  属性数据
 */
typedef class _PropertyData : public DATA
{

private:
    static const String8 propertyName;
public:
    _PropertyData():DATA( String8("property") ){};
    // 是否debug模式
    bool isDebugMode( void );
    int read( void );

}PropertyData;

typedef class _SocketData : public DATA
{

public:
    int read( void );
    _SocketData():DATA( String8("socket") ){};

}SocketData;
/**
 *  配置数据，哦，这个是个大类了，里面包含咱们的DATA,以及继承实现他几个字类
 */
typedef class _ConfigData
{

private:
    /*support mode : boot,ota,recovery,poweroffcharge,normal*/


    DATA *DataBase;

    ArgvData argvData;
    PropertyData propertyData;
    SocketData socketData;

public:

    _ConfigData(){ DataBase = NULL; };
    ~_ConfigData(){};
    // 下面的这几个方法都是应该从上面赋值的类中拿的吧？？？
    int read( int argc, char** argv );
    int getMode( String8& mode );
    int getMaxFiles( void );
    int getLogPath( String8& path );
    int getModemLogMaskPath( String8& path );
    int getDynamicLogMaskPath( String8& path );
    unsigned int getLogMaxSize( const String8& name );
    bool isLogEnable( const String8& name );

}ConfigData;

#endif
