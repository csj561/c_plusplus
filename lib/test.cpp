#include <iostream>
#include <fool.h>
using namespace std;
//using namespace fool;

int main(int argc,char **argv)
{
	cout<<fool::mv(argv[1],argv[2])<<endl;
	return 0;
}
