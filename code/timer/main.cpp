#include "timer.hpp"
#include <unistd.h>
#include <list>
#include <fstream>
int main()
{
	fool::timer t("main timer");
	std::list<int> l;
	std::ofstream ofs("ofs.txt");
	for(int i=0;i<1000000;i++)
		ofs<<i<<std::endl;
	//sleep(1);
}
