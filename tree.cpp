#include "tree.h"
#include <iostream>
using namespace std;

tree::tree()
{
    root=NULL;
}
void tree::AddNode(int key ,node*& rt)
{
    node* addnode=new node(key);
    if(rt==NULL)
    {
        rt=addnode;
        return;
    }
    node* p=rt;
    if (rt->data>key)
    {
        if(rt->left==NULL)
            rt->left=addnode;
        else
            AddNode(key,rt->left);
    }
    if (rt->data<key)
    {
        if(rt->rigth==NULL)
            rt->rigth=addnode;
        else
            AddNode(key,rt->rigth);
    }
}
void tree::MidTraversal(node* rt)
{
    stack<node*> sk;
    if(rt==NULL)
        return;
    node* cur=rt;
    while(cur||!sk.isempty())
    {
        if(cur->left)
        {
            sk.push(cur);
            cout<<"num:"<<sk.num;
            cur=cur->left;
        }
        else
        {
            cout<<" "<<cur->data;
            cur=cur->rigth;
            while(!cur&&!sk.isempty())
            {
                cur=sk.pop();
                cout<<" "<<cur->data;
                cur=cur->rigth;

            }
        }
    }

}
