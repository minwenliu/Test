/*=============================================================================
#     FileName: tree.h
#         Desc:  树结构，以及stack的定义
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-02-16 10:57:12
#      History:
=============================================================================*/
#ifndef _TREE_H_
#define _TREE_H_
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
#endif
