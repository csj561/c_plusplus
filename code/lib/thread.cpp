#include <iostream>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace boost;
void fun()
{
std::cout <<
"Hello world, I'm a thread!"
<< std::endl;
}

int main()
{
	thread thd(&fun);
	thd.join();
}
