#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 
#include <ace/Shared_Memory_Pool.h> 
#include <ace/Condition_T.h> 


#include "ace/Thread.h"
#include "ace/Synch.h"
static int number = 0;
static int seed = 0;
class Args 
{
public:Args (ACE_Condition < ACE_Thread_Mutex > *cond, int threads):cond_ (cond), threads_ (threads)
  {
  } ACE_Condition < ACE_Thread_Mutex > *cond_;
  int threads_;
};

static void *worker (void *arguments) 
{
  Args * arg = (Args *) arguments;
  ACE_DEBUG ((LM_DEBUG, "Thread (%t) Created to do some work\n"));
  
  
//Work
      ACE_OS::sleep (ACE_OS::rand () % 10);
  
//Exiting now
      ACE_DEBUG ((LM_DEBUG, "\tThread (%t) Done! \n\tThe number is now: %d\n", number));
  
//If all threads are done signal main thread that
//program can now exit
      //if (number == arg->threads_)
    
  {::number++;
    ACE_DEBUG ((LM_DEBUG, "(%t) Last Thread!\n All threads have done their job! Signal main thread\n"));
    arg->cond_->signal ();
  }
  return 0;
}

int main (int argc, char *argv[]) 
{
  if (argc < 2)
    
  {
    ACE_DEBUG ((LM_DEBUG, "Usage: %s <number of threads>\n", argv[0]));
    ACE_OS::exit (1);
  }
  int n_threads = ACE_OS::atoi (argv[1]);
  
//Setup the random number generator
      ACE_OS::srand (::seed);
  
//Setup arguments for threads
      ACE_Thread_Mutex mutex;
  ACE_Condition < ACE_Thread_Mutex > cond (mutex);
  Args arg (&cond, n_threads);
  
//Spawn off n_threads number of threads
      for (int i = 0; i < n_threads; i++)
    
  {
    if (ACE_Thread::spawn ((ACE_THR_FUNC) worker, (void *) &arg, THR_DETACHED | THR_NEW_LWP) == -1)
      ACE_DEBUG ((LM_DEBUG, "Error in spawning thread\n"));
  } 
//Wait for signal indicating that all threads are done and program
//can exit. The global resource here is "number" and the condition
//that the condition variable is waiting for is number==n_threads.
      mutex.acquire ();
  while (number != n_threads)
  	{
    cond.wait ();
	ACE_DEBUG ((LM_DEBUG, "(%t) Hi, Main Thread got signal.\n"));
  	}
  ACE_DEBUG ((LM_DEBUG, "(%t) Main Thread got signal. Program exiting..\n"));
  mutex.release ();
  ACE_OS::exit (0);
}

 
