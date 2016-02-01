/*=============================================================================
#     FileName: task.cpp
#         Desc:  
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-21 16:38:59
#      History:
=============================================================================*/

#include "task.h" 
#include <sys/socket.h> 
#include <errno.h> 
#include <sys/epoll.h>
#include "tconn.h"
#include <memory.h> 
#include "log.h" 
#include <stdio.h> 
Task::Task(unsigned int cpos,int csock,int efd):recvlen(0),pos(cpos),isock(csock),epollfd(efd)
{
    memset(&event,0,sizeof(event));
    event.data.u32=cpos;
    recvbuff[0]=0;
}


void Task::Recv()
{
    DEBUG("ENTER Recv");
    unsigned int Recvlen=MAX_DATA_LEN-recvlen-1;
    while(Recvlen>0)
    {
        ssize_t rv=recv(isock,recvbuff+recvlen,Recvlen,MSG_NOSIGNAL);
        DEBUG("recv package len%d",rv);
        if(rv<0)
        {
            if(errno!=EAGAIN&&errno!=EWOULDBLOCK)
            {
                ERROR("recv failed:%d|%s",errno,strerror(errno));
                Terminate();
            }
            break;
        }
        else if(rv==0)
        {
            Terminate();
            DEBUG("socket close");
            return;
        }
        Recvlen-=rv;
        recvlen+=rv;
        recvbuff[recvlen]=0;
    }
    Send();
}


bool Task::Send()
{
    DEBUG("Enter Send");
    const char* MSGHEAD="i am receiver,now i'am sendback,please check:";
    int copypos=snprintf(sendbuff,sizeof(sendbuff),"%s",MSGHEAD);
    DEBUG("copy MSGHEAD len:%d",copypos);
    int sendlen=snprintf(sendbuff+copypos,sizeof(sendbuff)-copypos,"%s",recvbuff);
    DEBUG("copy MSG len:%d",sendlen);
    DEBUG("sendbuff:%s|len:%d",sendbuff,strlen(sendbuff));
    DEBUG("recvlen:%d",recvlen);
    recvlen=recvlen-sendlen;
    if(recvlen>0)
    memcpy(recvbuff,recvbuff+sendlen,recvlen-sendlen);
    recvbuff[recvlen]=0;
    DEBUG("recvbuff content:%s|len:%d",recvbuff,strlen(recvbuff));
    ssize_t n=send(isock,sendbuff,strlen(sendbuff),MSG_NOSIGNAL);
    if(n<0)
    {
        if(errno!=EAGAIN && errno!=EWOULDBLOCK)
        {
            WARN("send fail:%d|%s",errno,strerror(errno));
        }
        DEBUG("send blocked,keep in sendbuff,remain length:%d",strlen(sendbuff));
        return 0;
    }
    else if(n==0)
    {
        WARN("socket closed");
        return -1;
    }
    DEBUG("send success,send len:%d",n);
    size_t slen=strlen(sendbuff);
    if(n<slen)
    {
        memcpy(sendbuff,sendbuff+n,slen-n);
    }
    else
    {
        sendbuff[0]=0;
        DEBUG("clean sendbuff");
    }
    return 0;
}

void Task::Record()
{
}

Task::~Task()
{
}

void Task::Terminate()
{
    close(isock);
    isock=-1;
    event.events=0;
    epoll_ctl(epollfd,EPOLL_CTL_DEL,isock,0);
    gtconn.removetask(pos);
}

