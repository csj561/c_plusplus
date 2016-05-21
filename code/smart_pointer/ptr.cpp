#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
extern "C"{
#include <pthread.h>
}
using namespace std;

//class pointer
template<class V>
class Ptr
{
	//nested class
	class U_Ptr
	{
		friend class Ptr;
		V *ip;
		size_t use;
		pthread_mutex_t mutex;
		U_Ptr(V *p):ip(p),use(1){pthread_mutex_init(&mutex,NULL);}
		void lock(){pthread_mutex_lock(&mutex);}
		void unlock(){pthread_mutex_unlock(&mutex);}
		~U_Ptr(){delete ip;pthread_mutex_destroy(&mutex);}
	};
	U_Ptr *ptr;
public:
	Ptr(V *p):ptr(new U_Ptr(p)){}
	Ptr(const Ptr &orig):ptr(orig.ptr){ptr->lock();++ptr->use;ptr->unlock();}
	V *operator->(){return ptr->ip;}
	Ptr & operator=(const Ptr &rhs){
		rhs.ptr->lock();
		++rhs.ptr->use;
		rhs.ptr->unlock();
		ptr->lock();
		if(--ptr->use==0)
		{
			ptr->unlock();
			delete ptr;
		}
		else
			ptr->unlock();
		ptr=rhs.ptr;
		return *this;
	}

	~Ptr(){
		ptr->lock();
		if(--ptr->use==0)
		{
			ptr->unlock();
			delete ptr;
		}
		else
			ptr->unlock();
	}
};

//void norm pointer 
template<class V>
class cPtr
{
	//nested class
	class U_Ptr
	{
		friend class cPtr;
		V *ip;
		size_t use;
		pthread_mutex_t mutex;
		U_Ptr(V *p):ip(p),use(1){pthread_mutex_init(&mutex,NULL);}
		void lock(){pthread_mutex_lock(&mutex);}
		void unlock(){pthread_mutex_unlock(&mutex);}
		~U_Ptr(){if(ip) free(ip);pthread_mutex_destroy(&mutex);}
	};
	U_Ptr *ptr;
public:
	cPtr(V *p):ptr(new U_Ptr(p)){}
	cPtr(const cPtr &orig):ptr(orig.ptr){ptr->lock();++ptr->use;ptr->unlock();}
	V *get(){return ptr->ip;}
	cPtr & operator=(const cPtr &rhs){
		rhs.ptr->lock();
		++rhs.ptr->use;
		rhs.ptr->unlock();
		ptr->lock();
		if(--ptr->use==0)
		{
			ptr->unlock();
			delete ptr;
		}
		else
			ptr->unlock();
		ptr=rhs.ptr;
		return *this;
	}
	~cPtr(){
		ptr->lock();
		if(--ptr->use==0)
		{
			ptr->unlock();
			delete ptr;
		}
		else
			ptr->unlock();
		}
};

class A
{
int a;
public:
A():a(0){cout<<"init A"<<endl;}
void p(){cout<<"a="<<a<<endl;}
void add(){a++;p();}
~A(){cout<<"destroy A"<<endl;}
};
int main()
{
	{
		cPtr<int> p((int *)malloc(sizeof(int)));
		*p.get()=4;
		cout<<"dat :"<<*p.get()<<endl;
	}
	
	getchar();
	return 0;
}