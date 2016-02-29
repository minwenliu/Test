#include <iostream> 

void print(int& a);

void test();
class testoperator 
{ 
    public: 
        testoperator (int n):num(n){} 
        testoperator& operator =(const testoperator a){num=a.num;}
        virtual ~testoperator (){} 
        friend std::ostream& operator <<(std::ostream& os,testoperator& A);

    private: 
        int num;
}; 
