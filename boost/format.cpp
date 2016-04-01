#include<com.h>
#include<boost/format.hpp>
using namespace boost;

int main()
{
	cout<<format("%s:%d\n")%"xyd"%26;
	format fmt("%1%:%2%\n");
	fmt%"hk";
	fmt%23;
	cout<<fmt;
}
