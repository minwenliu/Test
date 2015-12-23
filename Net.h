#include<string.h>
class UDP{
    public:

        UDP(){memset(this,0,sizeof(*this));}
        const static int Buff_len=1024*100;
        char sendbuff[Buff_len];
        char recvbuff[Buff_len];
};
