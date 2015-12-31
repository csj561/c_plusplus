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
  //open()����Ӧ�ð�������ר��������ĳ�ʼ�����롣
    ACE_DEBUG ((LM_DEBUG, "(%t) Active Object opened \n"));
    
//Activate the object with a thread in it.
/*����������ʵ�����������ͨ������activate()��������
Ҫ�����������д������̵߳���Ŀ���Լ�����һЩ�����������ݸ�activate()������
activate()������ʹsvc()������Ϊ���������ɵ��̵߳������㡣*/
        activate ();
    return 0;
  }
  int close (u_long) 
  {
  //close()��������Ӧ����ֹ����
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
