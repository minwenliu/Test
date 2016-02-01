/*=============================================================================
#     FileName: student.h
#         Desc: this is a student class
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-19 17:21:46
#      History:
=============================================================================*/
class student 
{ 
    const static int MAX_NAME_LEN=10;
    public: 
        student (); 
        virtual ~student (); 
        int getage();
        void setage(int age);
        char* getname();
        void setname(char* name);
        bool isman();
        int getscore();

    private: 
        int age;
        bool sex;
        char name[MAX_NAME_LEN];
        int score;
}; 
