// app1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
using namespace std;
typedef char  Line[128];
class base
{
public:
	int a;
	virtual int v1()
	{
		cout<<"this is base v1"<<endl;
		return 0;
	}
protected:
	string b;
private:
	char c;
};
class base2:public base
{
public:
	virtual int v1()
	{
		cout<<"this is base2 v1"<<endl;
		return 0;
	}
};
int call_v1(base &item)
{
	item.v1();
	return 0;
}
int main()
{
	base t;
	base2 t2;
	call_v1(t2);
	getchar();
	return 0;
}