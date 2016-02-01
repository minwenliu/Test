#include <stddef.h>
#include <memory.h> 
struct node{
    node(int key){data=key;left=NULL;rigth=NULL;}
    int data;
    node* left;
    node* rigth;
};
template<typename type>
struct stack{
    const static int MAX_NUM=10;
    stack(){
        memset(this,0,sizeof(*this));
    }
    type SK[MAX_NUM];
    int num;
    void push(type t)
    {
        if(num>=MAX_NUM-1)
            return;
        SK[num++]=t;
    }
    type pop()
    {
        if(num==0)
            return NULL;
        num--;
        return SK[num];
    }
    bool isempty()
    {
        return num==0;
    }
};


struct tree{
    tree();
    node* root;
    static void AddNode(int key,node*& rt);
    static void MidTraversal(node* rt);

};
