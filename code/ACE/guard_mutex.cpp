#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 
#include <ace/Shared_Memory_Pool.h> 
 
#include "ace/Synch.h"
#include "ace/Thread.h"
//Arguments that are to be passed to the worker thread are passed
//through this class.
    class Args 
{
public:Args (int iterations):mutex_ (), iterations_ (iterations)
  {
  } ACE_Thread_Mutex mutex_;
  int iterations_;
};


//The starting point for the worker threads
static void *worker (void *arguments) 
{
  Args * arg = (Args *) arguments;
  for (int i = 0; i < arg->iterations_; i++)
    
  {
    ACE_DEBUG ((LM_DEBUG, "(%t) Trying to get a hold of this iteration\n"));
    ACE_Guard < ACE_Thread_Mutex > guard (arg->mutex_);
    
    {
      
//This is our critical section
          ACE_DEBUG ((LM_DEBUG, "(%t) This is iteration number %d\n", i));
      
//work
          ACE_OS::sleep (2);
    }                          //end critical section
  }  return 0;
}

int main (int argc, char *argv[]) 
{
  
//same as previous example
}  
