/*=============================================================================
#     FileName: log.h
#         Desc: 简单的日志记录类，都是printf到控制台。
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-21 16:49:25
#      History:
=============================================================================*/
#ifndef LOG_INC
#define LOG_INC
#include "SingletonHolder.h" 

#define LOG_DEBUG 4 
#define LOG_INFO  3 
#define LOG_WARN  2 
#define LOG_ERROR 1 


#define MAX_LOG_LEN 100
class Log 
{ 
    public: 
        Log (){} 
        virtual ~Log (); 
        void Log_Error();
        void Log_Warn();
        void Log_Info();
        void Log_Debug();
        bool check_level(int level);
        void Set_Loglevel(int slevel);
        int Get_Loglevel();
        int BuildMsg(const char* file,int linenum,const char* function,const char* format,...); 

    private: 
        int level;
        char buf[MAX_LOG_LEN];
}; 

#define ERROR(arg...) if(SingletonHolder<Log>::Instance()->check_level(LOG_ERROR)){\
    SingletonHolder<Log>::Instance()->BuildMsg(__FILE__,__LINE__,__FUNCTION__,##arg);\
    SingletonHolder<Log>::Instance()->Log_Error();\
    }

#define WARN(arg...) if(SingletonHolder<Log>::Instance()->check_level(LOG_WARN)){\
    SingletonHolder<Log>::Instance()->BuildMsg(__FILE__,__LINE__,__FUNCTION__,##arg);\
    SingletonHolder<Log>::Instance()->Log_Warn();\
    }

#define INFO(arg...) if(SingletonHolder<Log>::Instance()->check_level(LOG_INFO)){\
    SingletonHolder<Log>::Instance()->BuildMsg(__FILE__,__LINE__,__FUNCTION__,##arg);\
    SingletonHolder<Log>::Instance()->Log_Info();\
    }
#define DEBUG(arg...) if(SingletonHolder<Log>::Instance()->check_level(LOG_DEBUG)){\
    SingletonHolder<Log>::Instance()->BuildMsg(__FILE__,__LINE__,__FUNCTION__,##arg);\
    SingletonHolder<Log>::Instance()->Log_Debug();\
    }
#endif
