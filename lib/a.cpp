#include <iostream>
extern "C"
{
	int p();
}

class A
{
	public:
		void p()
		{
			std::cout<<"This in class a"<<std::endl;
		}
};
int p()
{
	std::cout<<"ha ha ha"<<std::endl;
	A t;
	t.p();
	return 0;
}
