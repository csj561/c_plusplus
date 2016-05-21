#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 

#include "ace/OS.h"
#include "ace/Task.h"
class TaskOne:public ACE_Task < ACE_MT_SYNCH >  
{
public:
//Implement the Service Initialization and Termination methods
  int open (void *) 
  {
  //open()方法应该包含所有专属于任务的初始化代码。
    ACE_DEBUG ((LM_DEBUG, "(%t) Active Object opened \n"));
    
//Activate the object with a thread in it.
/*在主动对象实例化后，你必须通过调用activate()启用它。
要在主动对象中创建的线程的数目，以及其他一些参数，被传递给activate()方法。
activate()方法会使svc()方法成为所有它生成的线程的启动点。*/
        activate ();
    return 0;
  }
  int close (u_long) 
  {
  //close()方法是相应的终止方法
    ACE_DEBUG ((LM_DEBUG, "(%t) Active Object being closed down \n"));
    return 0;
  }
  int svc (void) 
  {
    ACE_DEBUG ((LM_DEBUG, "(%t) This is being done in a separate thread \n"));
    
// do thread specific work here
//.......
//.......
        return 0;
  }
};

int main (int argc, char *argv[]) 
{
  
//Create the task
      TaskOne * one = new TaskOne;
  
//Start up the task
      one->open (0);
  
//wait for all the tasks to exit
      ACE_Thread_Manager::instance ()->wait ();
  ACE_DEBUG ((LM_DEBUG, "(%t) Main Task ends \n"));
}  
