#include <stdio.h>
#include "hello.h"
#include "log.h" 
#include "SingletonHolder.h" 
#include "test.h"
#include "tconn.h" 
using namespace std;


int main(int argc, char** argv){
    SingletonHolder<Log>::Instance()->Set_Loglevel(LOG_INFO);
    SingletonHolder<tconn>::Instance()->run();

    return 0;
}
