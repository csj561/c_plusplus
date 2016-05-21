#include <iostream>
#include <fool.h>
#include <list>
#include <boost/assign.hpp>
#include <unistd.h>

using namespace std;
using namespace boost::assign;
int main()
{
	list<int > l;
	l.push_back(1000);
	l= (list_of(0),1,2,3);
	fool::Pri(l);
}

