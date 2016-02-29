/*=============================================================================
#     FileName: tconn.cpp
#         Desc: 
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-27 11:01:52
#      History:
=============================================================================*/
#include "tconn.h" 
#include <sys/socket.h> 
#include <sys/epoll.h>
#include <string.h> //strerror函数  
#include <fcntl.h> 
#include "log.h" 
#include <errno.h> //errno 
#include <netinet/tcp.h>//SOL_TCP 
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h>//hton 
#include "task.h" 
#include <unistd.h> //usleep
tconn gtconn;
bool tconn::MakeNonBlocking(int fd)
{
    int flags=fcntl(fd,F_GETFL);
    if(flags<0)
    {
        ERROR("get fcntl fail:%d",flags);
        return false;
    }
    flags|=O_NONBLOCK;
    if(fcntl(fd,F_SETFL,flags))
    {
        ERROR("set fcntl fail:%d",flags);
        return false;
    }
    INFO("make %d nonblock scuceess",fd);
    return true;
}
bool tconn::StartListen()
{
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        ERROR("create socket fail|%d|%s",errno,strerror(errno));
        return false;
    }
    int nodelay=1;

    if(setsockopt(sockfd,SOL_TCP,TCP_NODELAY,&nodelay,sizeof(int))<0)
    {
        ERROR("set socket tcp_nodelay option fail|%d|%s",errno,strerror(errno));
        return(false); 
    }
    int reuse=1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))==-1)
    {
        ERROR("set socket so_reuseaddr fail|%d|%s",errno,strerror(errno));
        return false;
    }
    if(!MakeNonBlocking(sockfd))
        return false;
    struct sockaddr_in svraddr;
    memset(&svraddr,0,sizeof(sockaddr_in));
    svraddr.sin_port=htons(SERVER_PORT);//需要转换为网络编码.
    svraddr.sin_family=AF_INET;
    svraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(sockfd,(struct sockaddr*)&svraddr,sizeof(svraddr))<0)
    {
        ERROR("bind fail|%x|%u|%d|%s",svraddr.sin_addr.s_addr,ntohl(svraddr.sin_port),errno,strerror(errno));
        return false;
    }
    if(listen(sockfd,4096)<0)
    {
        ERROR("listen fail:%d|%s",errno,strerror(errno));
        return false;
    }
    epollfd=epoll_create(EPOLL_MAX_FD_NUM);
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.u32=EPOLL_LISTEN_POS;
    if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&event)!=0)
    {
        ERROR("epoll_ctrl fail %d|%s",errno,strerror(errno));
        return false;
    }
    INFO("INIT success,epollfd:%d",epollfd) ;

    return true;

}


void tconn::Terminate()
{
}

bool tconn::run()
{
    if(!StartListen())
        return false;
    struct epoll_event events[EPOLL_MAX_EVENTS];
    while (true) { 
        bool working=false;
        int rv=epoll_wait(epollfd,events,EPOLL_MAX_EVENTS,0);
        if(rv>0)
        {
            working=true;
            INFO("epoll_wait,receive event%d",rv);
            for(int i=0;i<rv;i++)
            {
                unsigned int pos=events[i].data.u32;
                DEBUG("epoll event pos|%d",pos);
                if(pos==EPOLL_LISTEN_POS)
                {
                    if(events[i].events&EPOLLIN)
                        AcceptTask();
                    else
                        WARN("Listen socket receive event:%d",events[i].events);
                }
                else
                {
                    TaskPtr task=FindTask(pos);
                    if(!task)
                    {
                        WARN("not find client task,pos:%d",pos);
                        continue;
                    }
                    if(events[i].events&EPOLLIN)
                    {
                        DEBUG("recv client package");
                        task->Recv();
                    }
                    if(events[i].events&EPOLLOUT)
                        task->Send();
                    if(events[i].events&EPOLLERR)
                    {
                        task->Terminate();
                        continue;
                    }
                    if(events[i].events&EPOLLRDHUP)
                    {
                        task->Terminate();
                        continue;
                    }
                }
            }
        }
        else 
        {
            if(rv==-1)
            {
                if(errno==EINTR)
                {
                    INFO("epoll_wait no events");
                }
                else
                {
                    WARN("epoll_wait failed|%d|%s",errno,strerror(errno));
                    continue;
                }
            }
        }
        if(!working)
            usleep(1000);
    } 
}

TaskPtr tconn::FindTask(unsigned int pos)
{
    TaskMapIt it=objtaskmap.find(pos);
    if(it==objtaskmap.end())
        return TaskPtr();
    return it->second;

}

void tconn::AcceptTask()
{
    struct sockaddr_in clientaddr;
    socklen_t Len=sizeof(clientaddr);
    memset(&clientaddr,0,sizeof(clientaddr));
    while(true)
    {
        int sock=accept(sockfd,(struct sockaddr*)&clientaddr,&Len);
        if(sock<0)
        {
            if(errno==EAGAIN)
                break;
            WARN("accept fail|%d|%s",errno,strerror(errno));
            break;
        }

        if(!MakeNonBlocking(sock))
            return;
        int iNodely=1;
        if(-1==setsockopt(sock,SOL_TCP,TCP_NODELAY,&iNodely,sizeof(iNodely)))
        {
            ERROR("setsockopt failed|%d%s",errno,strerror(errno));
            return;
        }
        int cbuffsize=4*32768;
        DEBUG("trace");
        if(setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&cbuffsize,sizeof(cbuffsize))==-1)
        {
            WARN("set sendbuff size fail|%d|%s",errno,strerror(errno));
            return;
        }

        if(setsockopt(sock,SOL_TCP,SO_RCVBUF,(void*)&cbuffsize,sizeof(cbuffsize))==-1)
        {
            WARN("set recvbuff size failed|%d|%s",errno,strerror(errno));
            return;
        }
        unsigned int cpos=++curpos;
        INFO("new client connect,pos:%d",cpos);
        TaskPtr task;
        task.reset(new Task(cpos,sock,epollfd));
        struct epoll_event event;
        event.data.u32=cpos;
        event.events=(EPOLLIN|EPOLLRDHUP|EPOLLERR|EPOLLRDHUP|EPOLLET);
        if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sock,&event)!=0)
        {
            ERROR("epoll add failed,%d|%s",errno,strerror(errno));
            return ;
        }

        INFO("new client socket add epoll success");
        if(objtaskmap.insert(std::make_pair(cpos,task)).second==false)
        {
            ERROR("add task map failed,pos:%d",cpos);
            task->Terminate();
            return;
        }
        INFO("add task map success,pos:%d",cpos);

    }
    INFO("add map success");
}

tconn::tconn() : sockfd(0),curpos(0)
{
}

tconn::~tconn()
{
}
