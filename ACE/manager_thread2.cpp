#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 

// Test out the group management mechanisms provided by the
// ACE_Thread_Manager, including the group suspension and resumption,
//and cooperative thread cancellation mechanisms.
#include "ace/Thread_Manager.h"
static const int DEFAULT_THREADS = ACE_DEFAULT_THREADS;
static const int DEFAULT_ITERATIONS = 100000;
 static void * worker (int iterations) 
{
  for (int i = 0; i < iterations; i++)
    
  {
    if ((i % 1000) == 0)
      
    {
      ACE_DEBUG ((LM_DEBUG, "(%t) checking cancellation before iteration %d!\n", i));
      
//Before doing work check if you have been canceled. If so don't
//do any more work.
          if (ACE_Thread_Manager::instance ()->testcancel  (ACE_Thread::self ()) != 0)
        
      {
        ACE_DEBUG ((LM_DEBUG, "(%t) has been canceled before iteration %d!\n", i));
        break;
      }
    }
  }
  return 0;
}

int main (int argc, char *argv[]) 
{
  int n_threads = argc > 1 ? ACE_OS::atoi (argv[1]) : DEFAULT_THREADS;
  int n_iterations = argc > 2 ? ACE_OS::atoi (argv[2]) : DEFAULT_ITERATIONS;
  ACE_Thread_Manager * thr_mgr = ACE_Thread_Manager::instance ();
  
//Create a group of threads n_threads that will execute the worker
//function the spawn_n method returns the group ID for the group of
//threads that are spawned. The argument n_iterations is passed back
//to the worker. Notice that all threads are created detached.
  int grp_id = thr_mgr->spawn_n (n_threads, ACE_THR_FUNC (worker), (void *) n_iterations, THR_NEW_LWP | THR_DETACHED);
  
// Wait for 1 second and then suspend every thread in the group.
      ACE_OS::sleep (1);
  ACE_DEBUG ((LM_DEBUG, "(%t) suspending group\n"));
  if (thr_mgr->suspend_grp (grp_id) == -1)
    ACE_ERROR ((LM_DEBUG, "(%t) %p\n", "Could not suspend_grp"));
  
// Wait for 1 more second and then resume every thread in the
// group.
      ACE_OS::sleep (1);
  ACE_DEBUG ((LM_DEBUG, "(%t) resuming group\n"));
  if (thr_mgr->resume_grp (grp_id) == -1)
    ACE_ERROR ((LM_DEBUG, "(%t) %p\n", "resume_grp"));
  
// Wait for 1 more second and then cancel all the threads.
      ACE_OS::sleep (ACE_Time_Value (1));
  ACE_DEBUG ((LM_DEBUG, "(%t) canceling group\n"));
  if (thr_mgr->cancel_grp (grp_id) == -1)
    ACE_ERROR ((LM_DEBUG, "(%t) %p\n", "cancel_grp"));
  
// Perform a barrier wait until all the threads have shut down.
      thr_mgr->wait ();
  return 0;
}

 
