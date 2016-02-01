/*=============================================================================
#     FileName: task.h
#         Desc: 处理网络消息
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-21 16:35:12
#      History:
=============================================================================*/
#ifndef TASK_INC

#include <boost/shared_ptr.hpp> 
#include <sys/epoll.h> 

#define TASK_INC
#define MAX_DATA_LEN 10240
#include <boost/noncopyable.hpp> 
class Task: private boost::noncopyable
{ 
    public: 
        Task (unsigned int cpos,int csock,int efd); 
        bool Send();
        void Recv();
        void Record();
        virtual ~Task (); 
        void Terminate();

    private: 
        char recvbuff[MAX_DATA_LEN];
        char sendbuff[MAX_DATA_LEN];
        int recvlen;
        struct epoll_event event;
        unsigned int pos;
        int isock;
        int epollfd;
        
}; 
typedef boost::shared_ptr<Task> TaskPtr;
#endif
