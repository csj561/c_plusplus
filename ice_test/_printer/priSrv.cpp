#include <iostream>
#include <string>
#include <exception>
#include <Ice/Ice.h>
#include "printer.h"
using namespace std;
class PriSrv:public Pri::Printer
{
	virtual string pStr(string & s,const Ice::Current &)
	{cout<<s<<endl;s+=" done ";return s+" deal ";}
};

int main(int argc,char **argv)
{
	Ice::CommunicatorPtr ic=NULL;
	try
	{
		int status=0;
		ic=Ice::initialize(argc,argv);
		Ice::ObjectAdapterPtr adapter
			= ic->createObjectAdapterWithEndpoints(
					"SimplePrinterAdapter", "default -p 10000");
		Ice::ObjectPtr object = new PriSrv;
		adapter->add(object,
				Ice::stringToIdentity("SimplePrinter"));
		adapter->activate();
		ic->waitForShutdown();
	}
	catch(exception e)
	{
		cerr<<e.what()<<endl;
	}
	if(ic)
		ic->destroy();
	return 0;
}
