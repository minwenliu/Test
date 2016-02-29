#include <stdio.h>
#include <set>
#include "hello.h"
#include <math.h>
#include <algorithm>
#include <vector>
#include "boost/ref.hpp"
#include <iostream>
#include "td/td.h"
#include "Net.h"
#include "lib/udp_client.h"
#include "tree.h"
#include <tr1/unordered_set>
#include <google/profiler.h>
#include <sys/uio.h>
#include "log.h" 
#include "SingletonHolder.h" 
#include "test.h" 
#include <math.h> 
using namespace std;

ostream& operator<<(ostream& os,testoperator& A)
{
    os<<A.num;
    return os;
}
template<bool, typename>
struct __enable_if 
{ };

template<typename _Tp>
struct __enable_if<true, _Tp>
{ typedef _Tp __type; };

struct square  
{  
    typedef void result_type;  
    void operator()(int& x)  
    {  
        x = x * x;  
        cout << x << endl;  
    }  
};  
typename __enable_if<true,int>::__type tp()
{
    return 5;
}
void print(int& a)
{
    printf("%d",++a);
}
int GetMinNumTeam(int * role,int role_size,int32_t& teamid, int& teamnum) {
    if (role_size<= 0) {
        return -1;
    }
    //! 同一原始队则连续在一起
    teamid = role[0];
    teamnum = role_size;
    int32_t id = teamid;
    int num = 1;
    for (int i=1; i<(int)role_size; i++) {
        if (id == role[i]) {
            num++;
        } else {
            if (teamnum >= num) 
            {
                teamid = id;
                teamnum = num;
            }
            id = role[i];
            num = 1;
            if (teamnum <= 1) {
                for(int j=0;j<role_size;j++)
                    cout<<role[j];
                cout<<endl;
                cout<<"teamid:"<<teamid<<"num:"<<teamnum<<endl;
                return 0;
            }
        }
    }
    if (teamnum > num) {
        teamid = id;
        teamnum = num;
    }
    cout<<"role data:";
    for(int i=0;i<role_size;i++)
        cout<<role[i];
    cout<<endl;
    cout<<"teamid:"<<teamid<<"num:"<<teamnum<<endl;
    return 0;
}

void test(){
    //ProfilerStart("my.prof");
    //int x = 5; 
    /*print(x);*/
    /*print(x);*/
    /*cout << sqrt(boost::ref(x)) << endl;*/
    //std::vector<student> s;
    //student s_a(100,"lmw",true,21);
    //student s_b(99,"kkfnui",true,21);
    //student s_c(99,"zabery",true,21);
    //student s_d(98,"limei",false,21);
    //student s_e(150,"amu",true,21);
    //s.push_back(s_a);
    //s.push_back(s_b);
    //s.push_back(s_c);
    //s.push_back(s_d);
    //s.push_back(s_e);
    //student s_f(160,"tangtian",false,21);
    //student s_g(161,"wanjie",false,21);
    //for(int i=0;i<25;i++)
    //{
    //char name[15]={0};
    //snprintf(name,sizeof(name),"chenyuan%d",i);
    //student s_h(162,name,false,21);
    //s.push_back(s_h);
    //} 
    //cout<<"before rank:"<<endl;
    //for(vector<student>::iterator it=s.begin();it!=s.end();it++)
    //{
    //it->tostring();
    //}
    //std::sort(s.begin(),s.end(),studentgreater());

    //cout<<"after rank:"<<endl;
    //for(vector<student>::iterator it=s.begin();it!=s.end();it++)
    //{
    //it->tostring();
    //}
    //A a;
    //a.P_A();
    //td td_instance;
    //td_instance.print();
    //    UDP u;
    //    snslib::CUdpClient client;
    //    client.Send((unsigned char *)u.sendbuff,UDP::Buff_len);
    //    /*printf("%s", "Hello, Linux World!\n");*/
    //    int teamid=0,tnum=0;
    //    int role1[5]={1,1,1,2,2};
    //    int role2[5]={1,1,1,1,2};
    //    int role3[5]={1,1,2,2,3};
    //    int role4[5]={1,2,2,2,3};
    //    int role5[5]={1,2,3,4,5};
    //    int role6[5]={1,1,2,2,2};
    //    int role7[5]={1,3,2,2,2};
    //    int role8[4]={1,2,3,4};
    //    int role9[4]={1,1,2,2};
    //    int role10[4]={1,2,2,3};
    //    int role11[4]={1,1,2,3};
    //    int role12[4]={1,2,2,2};
    //    GetMinNumTeam(role1,5,teamid,tnum);
    //    GetMinNumTeam(role2,5,teamid,tnum);
    //    GetMinNumTeam(role3,5,teamid,tnum);
    //    GetMinNumTeam(role4,5,teamid,tnum);
    //    GetMinNumTeam(role5,5,teamid,tnum);
    //    GetMinNumTeam(role6,5,teamid,tnum);
    //    GetMinNumTeam(role7,5,teamid,tnum);
    //    GetMinNumTeam(role8,4,teamid,tnum);
    //    GetMinNumTeam(role9,4,teamid,tnum);
    //    GetMinNumTeam(role10,4,teamid,tnum);
    //    GetMinNumTeam(role11,4,teamid,tnum);
    //    GetMinNumTeam(role12,4,teamid,tnum);
    //
    //    tr1::unordered_set<int> ISet;
    //    ISet.insert(4);
    //    ISet.insert(9);
    //    ISet.insert(9);
    //    ISet.insert(7);
    //    ISet.insert(1);
    //    ISet.insert(7);
    //    ISet.insert(7);
    //    ISet.insert(5);
    //    ISet.insert(3);
    //    ISet.insert(11);
    //    ISet.insert(31);
    //    for(tr1::unordered_set<int>::iterator it=ISet.begin();it!=ISet.end();it++)
    //    {
    //        cout<<*it<<":";
    //    }
    //
    //    const char *buf1 = "Hello ";
    //    const char *buf2 = "Wikipedia ";
    //    const char *buf3 = "Community!\n";
    //    const char *buf4= "iiii";
    //    struct iovec bufs[3];
    //    bufs[0].iov_base=(void*) buf1;
    //    bufs[0].iov_len=strlen(buf1);
    //    bufs[1].iov_base=(void*) buf2;
    //    bufs[1].iov_len=strlen(buf2);
    //    bufs[2].iov_base=(void*) buf3;
    //    bufs[2].iov_len=strlen(buf3);
    //
    //    if (-1 == writev(STDOUT_FILENO, bufs, 3))
    //    {
    //        perror("writev()");
    //        exit(EXIT_FAILURE);
    //    }
    //    ProfilerFlush();
    //    ProfilerStop();
    //    
    //    int par_print=45;
    //   printf("\n%0x,%p\n",&par_print,par_print); 
    //  SingletonHolder<Log>::Instance()->Set_Loglevel(LOG_INFO);
    //   
    //   INFO("llllmd%d,%d",par_print,par_print);
    //   WARN("thisiswarn");
    testoperator a(5);
    testoperator b=a;
    cout<<b;
    cout<<sqrt(16)<<sqrt(16.7);
    cout<<sizeof(tp());
    //sqrt(a);
    testoperator c=b=a;


}
