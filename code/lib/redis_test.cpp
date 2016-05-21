#include "redis.hpp"
#include <fool.h>

int main(int argc,char ** main_argv)
{
  if(argc==1)
  	return -1;
  //std::cout<<"Command>> "<<main_argv[1]<<std::endl;
  Redis *r = new Redis();
  if(!r->connect("127.0.0.1", 6379))
  {
    printf("connect error!\n");
    return 0;
  }
  
  //printf("Get the name is %s\n", r->cmd("lrange mylist 0 10").c_str());
  listStr _list;
  r->cmd(argc-1,(const char **)main_argv+1,_list);
  fool::Pri(_list);
  delete r;
  return 0;
}


