/*=============================================================================
#     FileName: log_def.h
#         Desc:  日志记录
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-20 15:16:01
#      History:
=============================================================================*/
#ifndef _LOG_DEF_H
#define _LOG_DEF_H
#include "comm/log/pet_log.h" 

#ifndef LOG
#define LOG(id,log_level,format,args ...)\
    do\
    {
        PetLog(id,0,log_level,"%s:%u(%s)|"format, __FILE__,__LINE__,__FUNCTION__, ##args);\
    } while(0)
#endif
