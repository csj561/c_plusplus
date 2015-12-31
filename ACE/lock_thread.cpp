#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 
#include "ace/Synch.h"
#include "ace/Thread.h"
#include <ace/Lock_Adapter_T.h> 


//Arguments that are to be passed to the worker thread are passed
//through this class.
struct Args 
{
public:Args (ACE_Lock * lock, int iterations):mutex_ (lock), iterations_ (iterations)
  {
  } ACE_Lock * mutex_;
  int iterations_;
};


//The starting point for the worker threads
static void *worker (void *arguments) 
{
  Args * arg = (Args *) arguments;
  for (int i = 0; i < arg->iterations_; i++)
    
  {
    ACE_DEBUG ((LM_DEBUG, "(%t) Trying to get a hold of this iteration\n"));
    
//This is our critical section
        arg->mutex_->acquire ();
    ACE_DEBUG ((LM_DEBUG, "(%t) This is iteration number %d\n", i));
    ACE_OS::sleep (2);
    
//simulate critical work
        arg->mutex_->release ();
  } return 0;
}

int main (int argc, char *argv[]) 
{
  if (argc < 4)
    
  {
    ACE_OS::printf ("Usage: %s <number_of_threads><number_of_iterations> <lock_type>\n", argv[0]);
    ACE_OS::exit (1);
  }
  
//Polymorphic lock that will be used by the application
      ACE_Lock * lock;
  
//Decide which lock you want to use at run time,
//recursive or non-recursive.
      if (ACE_OS::strcmp (argv[3], "Recursive"))
    lock = new ACE_Lock_Adapter< ACE_Recursive_Thread_Mutex >;
  
  else
    lock = new ACE_Lock_Adapter< ACE_Thread_Mutex > ;
//Setup the arguments
        Args arg (lock, ACE_OS::atoi (argv[2]));
  
//spawn threads and wait as in previous examples..
//Setup the arguments
  int n_threads = ACE_OS::atoi (argv[1]);
  
//determine the number of threads to be spawned.
      ACE_thread_t * threadID = new ACE_thread_t[n_threads + 1];
  ACE_hthread_t * threadHandles = new ACE_hthread_t[n_threads + 1];
  if (ACE_Thread::spawn_n (threadID,   //id's for each of the threads
                            n_threads,  //number of threads to spawn
                            (ACE_THR_FUNC) worker,      //entry point for new thread
                            &arg,       //args to worker
                            THR_JOINABLE | THR_NEW_LWP, //flags
                            ACE_DEFAULT_THREAD_PRIORITY, 0, 0, threadHandles) == -1)
    ACE_DEBUG ((LM_DEBUG, "Error in spawning thread\n"));
  
//spawn n_threads
      for (int i = 0; i < n_threads; i++)
    ACE_Thread::join (threadHandles[i]);
  
//Wait for all the threads to exit before you let the main fall through
//and have the process exit.

}

 
