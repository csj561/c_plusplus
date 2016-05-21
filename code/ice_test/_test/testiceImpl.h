#include <iostream>
#include <string>
#include "testice.h"
#include <sys/time.h>
using namespace WG;
class CTestIceImpl:public WGTestIce 
{
public:CTestIceImpl ()
  {
  }
  ~CTestIceImpl ()
  {
  }
  int ping (const Ice::Current & = Ice::Current ()) 
  {
    std::cout << "ping successfully." << std::endl;
    return 0;
  }
  int GetTime (std::string & strTime, const Ice::Current & = Ice::Current ()) 
  {
    time_t tt = time (NULL);
    struct tm tm1;
    struct tm *pNow;
    pNow = localtime_r (&tt, &tm1);
    if (!pNow)
      
    {
      strTime = "error";
      return -1;
    }
    char buf[32] = { 0 };
    sprintf (buf, "%04d-%02d-%02d %02d:%02d:%02d", pNow->tm_year + 1900, pNow->tm_mon + 1, pNow->tm_mday,
              pNow->tm_hour, pNow->tm_min, pNow->tm_sec);
    strTime = buf;
    return 0;
  }
};


