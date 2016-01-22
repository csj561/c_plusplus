#include <iostream>
#include <fool.h>
#include <map>
using namespace std;
//using namespace fool;

int main(int argc,char **argv)
{
	cout<<fool::check_suffix(argv[1],argv[2])<<endl;
	return 0;
}
