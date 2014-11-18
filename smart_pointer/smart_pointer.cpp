#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
#ifdef BOOK
template<class V>
class smart_Ptr
{
class U_Ptr
{
	friend class smart_Ptr;
	V *ip;
	size_t use;
	U_Ptr(int *p):ip(p),use(1){}
	~U_Ptr(){delete ip;}
};
U_Ptr *ptr;
V val;
public:
smart_Ptr(V *p,V v):ptr(new U_Ptr(p)),val(v){}
smart_Ptr(const smart_Ptr &orig):ptr(orig.ptr),val(orig.val){--ptr->use;}
smart_Ptr & operator=(const smart_Ptr &);
~smart_Ptr(){if(--ptr->use==0) delete ptr;}
};
smart_Ptr & smart_Ptr::operator=(const smart_Ptr &rhs)
{
++rhs.ptr->use;
if(--ptr->use==0)
	delete ptr;
	ptr=rhs.ptr;
	val=rhs.val();
	return *this;
}
#else
template<class V>
class smart_Ptr
{
class U_Ptr
{
	friend class smart_Ptr;
	V *ip;
	size_t use;
	U_Ptr(V *p):ip(p),use(1){}
	~U_Ptr(){delete ip;}
};
U_Ptr *ptr;
public:
smart_Ptr(V *p):ptr(new U_Ptr(p)){cout << "init smart"<<endl;}
smart_Ptr(const smart_Ptr &orig):ptr(orig.ptr){++ptr->use;cout<<"copy init smart"<<endl;}
V *operator->(){return ptr->ip;}
smart_Ptr & operator=(const smart_Ptr &rhs);
void p(){cout<<"use="<<ptr->use<<endl;}
~smart_Ptr(){if(--ptr->use==0) delete ptr;}
};
template<class V>
smart_Ptr<V> & smart_Ptr<V>::operator=(const smart_Ptr<V> &rhs){
	++rhs.ptr->use;
	if(--ptr->use==0)
	delete ptr;
	ptr=rhs.ptr;
	return *this;
}
#endif
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
	A *a=new A();
	smart_Ptr<A> s(a);
	s.p();
	{
	smart_Ptr<A> b=s;
	b.p();
	s->p();
	b->p();
	s->add();
	b->p();}
	s.p();
	
	getchar();
	return 0;
}