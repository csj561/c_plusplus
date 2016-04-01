#include <iostream>
#include <string>
#include <Ice/Ice.h>
#include <exception>
#include <printer.h>
using namespace std;
using namespace Pri;

int main(int argc,char **argv)
{
	Ice::CommunicatorPtr ic=NULL;
	try
	{
		ic = Ice::initialize(argc, argv);
		Ice::ObjectPrx base = ic->stringToProxy(
				"SimplePrinter:default -p 10000");
		PrinterPrx printer = PrinterPrx::checkedCast(base);
		if (!printer)
			throw "Invalid proxy";
		string s="haha... ";
		int i=10000;
		cout<<"start..."<<endl;
		while(i--)
			printer->pStr(s);
		cout<<"end..."<<endl;
	}
	catch(exception e)
	{
		cerr<<e.what()<<endl;
	}
	if(ic)
		ic->destroy();
	return 0;
}
