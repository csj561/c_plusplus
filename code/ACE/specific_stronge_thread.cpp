#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 
#include <ace/Shared_Memory_Pool.h> 

#include "ace/Synch.h"
#include "ace/Thread_Manager.h"
    class DataType 
{
public: DataType ():data (0)
  {
  }
  void increment ()
  {
    data++;
  } void set (int new_data)
  {
    data = new_data;
  } void decrement ()
  {
    data--;
  } int get ()
  {
    return data;
  }
private:int data;
};

ACE_TSS < DataType > data;
static void *thread1 (void *) 
{
  data->set (10);
  ACE_DEBUG ((LM_DEBUG, "(%t)The value of data is %d \n", data->get ()));
  for (int i = 0; i < 5; i++)
  	{
  	ACE_OS::sleep (1);
    data->increment ();
  	
  ACE_DEBUG ((LM_DEBUG, "(%t)The value of data is %d \n", data->get ()));
  	}
  return 0;
}

static void *thread2 (void *) 
{
  data->set (100);
  ACE_DEBUG ((LM_DEBUG, "(%t)The value of data is %d \n", data->get ()));
  for (int i = 0; i < 5; i++)
  	{
  	ACE_OS::sleep (1);
    data->increment ();
  ACE_DEBUG ((LM_DEBUG, "(%t)The value of data is %d \n", data->get ()));
  	}
  return 0;
}

int main (int argc, char *argv[]) 
{
  
//Spawn off the first thread
      ACE_Thread_Manager::instance ()->spawn ((ACE_THR_FUNC) thread1, 0, THR_NEW_LWP | THR_DETACHED);
  
//Spawn off the second thread
      ACE_Thread_Manager::instance ()->spawn ((ACE_THR_FUNC) thread2, 0, THR_NEW_LWP | THR_DETACHED);
   
//Wait for all threads in the manager to complete.
      ACE_Thread_Manager::instance ()->wait ();
  ACE_DEBUG ((LM_DEBUG, "Both threads done.Exiting.. \n"));
}  
