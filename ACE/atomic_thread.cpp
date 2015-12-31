#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 

#include "ace/Thread.h"
#include "ace/Synch.h"
//Global mutable and shared data on which we will perform simple
//arithmetic operations which will be protected.
ACE_Atomic_Op < ACE_Thread_Mutex, int >foo;
// 原理:重载所有算术操作符，并确保在操作前获取锁，在操作后释放它。运算本身被委托给通过模板传入的的类。
//The worker threads will start from here.
static void *worker (void *arg) 
{
  ACE_UNUSED_ARG (arg);
  foo = 5;
  ACE_ASSERT (foo == 5);
  ++foo;
  ACE_ASSERT (foo == 6);
  --foo;
  ACE_ASSERT (foo == 5);
  foo += 10;
  ACE_ASSERT (foo == 15);
  foo -= 10;
  ACE_ASSERT (foo == 5);
  foo = 5L;
  ACE_ASSERT (foo == 5);
  return 0;
}

int main (int argc, char *argv[]) 
{
  if (argc < 2)
    
  {
    ACE_OS::printf ("Usage: %s <number_of_threads>\n", argv[0]);
    ACE_OS::exit (1);
  }
  
//Setup the arguments
  int n_threads = ACE_OS::atoi (argv[1]);
  
//determine the number of threads to be spawned.
      ACE_thread_t * threadID = new ACE_thread_t[n_threads + 1];
  ACE_hthread_t * threadHandles = new ACE_hthread_t[n_threads + 1];
  if (ACE_Thread::spawn_n (threadID,   //id's for each of the threads
                            n_threads,  //number of threads to spawn
                            (ACE_THR_FUNC) worker,      //entry point for new thread
                            NULL,       //args to worker
                            THR_JOINABLE | THR_NEW_LWP, //flags
                            ACE_DEFAULT_THREAD_PRIORITY, 0, 0, threadHandles) == -1)
    ACE_DEBUG ((LM_DEBUG, "Error in spawning thread\n"));
  
//spawn n_threads
      for (int i = 0; i < n_threads; i++)
    ACE_Thread::join (threadHandles[i]);
  
//Wait for all the threads to exit before you let the main fall through
//and have the process exit.
      return 0;
//spawn threads as in previous examples
}  
