#include <iostream>
#include <cstring>
#include <syslog.h>
using namespace std;

int main()
{
	
	syslog(LOG_ERR,"%d %s\n",100,"hahaha");
	return 0;
}
