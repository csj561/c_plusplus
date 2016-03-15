#include "redis.hpp"

int main()
{
  Redis *r = new Redis();
  if(!r->connect("127.0.0.1", 6379))
  {
    printf("connect error!\n");
    return 0;
  }
  
  printf("Get the name is %s\n", r->cmd("lrange mylist 0 10").c_str());
  delete r;
  return 0;
}

