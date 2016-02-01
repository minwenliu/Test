/*=============================================================================
#     FileName: log_warp.h
#         Desc:  日志包装类
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-21 10:33:00
#      History:
=============================================================================*/

#ifndef LOG_WARP_INC
#define LOG_WARP_INC
#include "SingletonHolder.h" 
#include "log.h" 

#define WARN(format,arg...) SingletonHolder<Log>::Instance()->
