/*=============================================================================
#     FileName: tconn.h
#         Desc: prcatice
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-20 10:42:56
#      History:
=============================================================================*/
#ifndef TCONN_INC
#define TCONN_INC

#define   SERVER_PORT        6666
#define   EPOLL_MAX_FD_NUM   10000
#define   EPOLL_LISTEN_POS   0
#define   EPOLL_MAX_EVENTS   1024

#include "hash_map.h" 
#include "boost/shared_ptr.hpp" 
#include "task.h"

typedef hash_map<unsigned int,TaskPtr> TaskMap;
typedef TaskMap::iterator TaskMapIt;

class tconn 
{ 
    public: 
        tconn (); 
        virtual ~tconn (); 
        bool run();
        void Terminate();
        bool StartListen();
        void AcceptTask();
        bool MakeNonBlocking(int fd);
        void removetask(unsigned int pos);
        TaskPtr FindTask(unsigned int pos);




    private: 
        int epollfd;
        int sockfd;
        TaskMap objtaskmap;
        unsigned int curpos;

}; 

inline void tconn::removetask(unsigned int pos)
{
    TaskMapIt it=objtaskmap.find(pos);
    if(it!=objtaskmap.end())
        objtaskmap.erase(it);
}
extern tconn gtconn;
#endif
