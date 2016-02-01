/*=============================================================================
#     FileName: SingletonHolder.h
#         Desc: 单体类
#       Author: minwenliu
#        Email: minwenliu@tencent.com
#     HomePage: http://www.vimer.cn
#      Version: 0.0.1
#   LastChange: 2016-01-20 16:25:33
#      History:
=============================================================================*/
#ifndef SINGLETONHOLDER_INC
#define SINGLETONHOLDER_INC
template<class T>
class SingletonHolder 
{ 
    private: 
        SingletonHolder (){}; 
        SingletonHolder(const SingletonHolder&);
        SingletonHolder& operator=(const SingletonHolder&);
        virtual ~SingletonHolder (){}; 
        static T* pInstance_;

    public: 
        static T* Instance()
        {
            if(!pInstance_)
                pInstance_=new T();
            return pInstance_;
        }
}; 
template<class T>
T* SingletonHolder<T>::pInstance_=0;
#endif
