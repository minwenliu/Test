/*=============================================================================
#     FileName: log.cpp
#         Desc: 
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-20 16:48:25
#      History:
=============================================================================*/
#include "log.h" 
#include <stdarg.h>
#include <stdio.h>
int Log::BuildMsg(const char* file,int linenum,const char* function,const char* format,...)
{
    va_list va;
    int len;
    len=snprintf(buf,MAX_LOG_LEN,"filename:%s:line:%d:function:%s:",file,linenum,function);
    va_start(va,format);
    len=vsprintf(buf+len,format,va);
    va_end(va);
    return len;
}

bool Log::check_level(int level)
{
    return level<=this->level;
}


int Log::Get_Loglevel()
{
    return(level); 
}


void Log::Log_Debug()
{
        printf("Debug:%s\n",buf);
}


void Log::Log_Error()
{
        printf("Error:%s\n",buf);
}


void Log::Log_Info()
{
        printf("Info:%s\n",buf);
}


void Log::Log_Warn()
{
        printf("Warn:%s\n",buf);
}


void Log::Set_Loglevel(int slevel)
{
    level=slevel;
}

Log::~Log()
{
}
