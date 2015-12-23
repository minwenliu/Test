#include <string>
#include <iostream>
using namespace std;
struct student{
    public:
        student(int score,const char * name, bool sex,int age)
        {
            score_=score;
            sex_=sex;
            name_=name;
            age_=age;
        
        }
        void tostring()
        {
            cout<<"name:"<<name_<<" score:"<<score_<<"  age:"<<age_<<endl;
        }
        int score_;
        bool sex_;
        string name_;
        int age_;
};
struct studentgreater{
    bool operator ()(const student& A,const student& B)
    {
        return A.score_>=B.score_; 

    }
};
