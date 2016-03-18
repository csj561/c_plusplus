#include <iostream>
#include <Ice/Ice.h>
#include "testice.h"
Ice::CommunicatorPtr pCommunicator;
Ice::ObjectPrx pObject;
WG::WGTestIcePrx pProxy;
const char *menu = "*****************test ice client ***********************\n" 
    "\t 1 ping\n"  "\t 2 getTime\n"  "\t q quit\n"  "********************************************************\n";
void showMenu () 
{
  std::cout << menu << std::endl;
  return;
}

int doMenu () 
{
  int ret = 0;
  char c;
  std::string strTime;
  showMenu ();
  c = getchar ();
  while (c != 'q')
    
  {
    switch (c)
      
    {
        case '1':
          ret = pProxy->ping ();
          std::cout << "ping ret is " << ret << std::endl;
          break;
        case '2':
          ret = pProxy->GetTime (strTime);
          std::cout << "GetTime ret is " << ret << "retTime is " << strTime << std::endl;
          break;
        case 'q':
          return 0;
          break;
        default:
          break;
    }
    sleep (2);
    showMenu ();
    //system ("clear");
    c = getchar ();
  }
  return 0;
}

int main (int argc, char **argv)
{
  try 
  {
    if (argc < 4)
      
    {
      std::cout << "argc less than 4. example is : testClient WGInterfaceAgentId 127.0.0.1 7788" << std::endl;
      return -1;
    }
    char buf[128] = { 0 };
    snprintf (buf, sizeof (buf) - 1, "%s:default -h %s -p %s", argv[1], argv[2], argv[3]);
    int tmpargc = 0;
    char **tmpargv = NULL;
    pCommunicator = Ice::initialize (tmpargc, tmpargv);
    pObject = pCommunicator->stringToProxy (buf);
    pProxy = WG::WGTestIcePrx::checkedCast (pObject);
    return doMenu ();
  }
  catch (const Ice::Exception & ex) 
  {
    std::cout << "catch ice exception, " << ex << std::endl;
    return -1;
  }
  catch ( ...) 
  {
    std::cout << "catch unknown exception. " << std::endl;
    return -1;
  }
}


