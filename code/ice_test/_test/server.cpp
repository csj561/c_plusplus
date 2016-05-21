#include <Ice/Ice.h>
#include "testice.h"
#include "testiceImpl.h"
int createSrv ()  try 
{
  int tmpargc = 0;
  char **tmpargv = NULL;
  Ice::CommunicatorPtr ic;
  ic = Ice::initialize (tmpargc, tmpargv);
  Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints ("WGSrv", "default -p 7788");
  Ice::ObjectPtr object = new CTestIceImpl ();
  adapter->add (object, ic->stringToIdentity ("WGInterfaceAgentId"));
  adapter->activate ();
  std::cout << "now server start successfully." << std::endl;
  ic->waitForShutdown ();
  if (ic)
    
  {
    std::cout << "now ice server exit." << std::endl;
    ic->destroy ();
  }
}

catch (const Ice::Exception & ex) 
{
  std::cout << "catch ice exception, " << ex << std::endl;
  return -1;
}

catch (...) 
{
  std::cout << "catch unknown exception." << std::endl;
  return -1;
}

int main (int argc, char **argv) 
{
  std::cout << "before to create Srv" << std::endl;
  return createSrv ();
}


