#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 
#include <ace/Shared_Memory_Pool.h> 

#include "ace/Shared_Memory_MM.h"
#include "ace/Malloc.h"
#include "ace/Malloc_T.h"
#define DATA_SIZE 100
#define MESSAGE1 "Hiya over there client process"
#define MESSAGE2 "Did you hear me the first time?"
const char * poolname = "My_Pool";
typedef ACE_Malloc < ACE_SHARED_MEMORY_POOL, ACE_Null_Mutex > Malloc_Allocator;
static void server (void) 
{
  
//Create the memory allocator passing it the shared memory
//pool that you want to use
      Malloc_Allocator shm_allocator (poolname);
  
//Create a message, allocate memory for it and bind it with
//a name so that the client can the find it in the memory
//pool
  char *Message1 = (char *) shm_allocator.malloc (strlen (MESSAGE1));
  ACE_OS::strcpy (Message1, MESSAGE1);
  shm_allocator.bind ("FirstMessage", Message1);
  ACE_DEBUG ((LM_DEBUG, "<<%s\n", Message1));
//How about a second message
  char *Message2 = (char *) shm_allocator.malloc (strlen (MESSAGE2));
  ACE_OS::strcpy (Message2, MESSAGE2);
  shm_allocator.bind ("SecondMessage", Message2);
  ACE_DEBUG ((LM_DEBUG, "<<%s\n", Message2));
  
//Set the Server to go to sleep for a while so that the client has
//a chance to do its stuff
      ACE_DEBUG ((LM_DEBUG, "Server done writing.. going to sleep zzz..\n\n\n"));
  ACE_OS::sleep (2);
  
//Get rid of all resources allocated by the server. In other
//words get rid of the shared memory pool that had been
//previously allocated
      shm_allocator.remove ();
} 
static void client (void) 
{
  
//Create a memory allocator. Be sure that the client passes
// in the "right" name here so that both the client and the
//server use the same memory pool. We wouldn't want them to
// BOTH create different underlying pools.
      Malloc_Allocator shm_allocator (poolname);
  
//Get that first message. Notice that the find is looking up the
//memory based on the "name" that was bound to it by the server.
  void *Message1;
  if (shm_allocator.find ("FirstMessage", Message1) == -1)
    
  {
    ACE_ERROR ((LM_ERROR, "Client: Problem cant find data that server has sent\n"));
    ACE_OS::exit (1);
  }
  ACE_OS::printf (">>%s\n", (char *) Message1);
  ACE_OS::fflush (stdout);
  
//Lets get that second message now.
  void *Message2;
  if (shm_allocator.find ("SecondMessage", Message2) == -1)
    
  {
    ACE_ERROR ((LM_ERROR, "Client: Problem cant find data that server has sent\n"));
    ACE_OS::exit (1);
  }
  ACE_OS::printf (">>%s\n", (char *) Message2);
  ACE_OS::fflush (stdout);
  ACE_DEBUG ((LM_DEBUG, "Client done reading! BYE NOW\n"));
  ACE_OS::fflush (stdout);
} 
int main (int, char *[]) 
{
  switch (ACE_OS::fork ())
    
  {
      case -1:
        ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "fork"), 1);
      case 0:
        
// Make sure the server starts up first.
            ACE_OS::sleep (1);
        client ();
        break;
      default:
        server ();
        break;
  }
  return 0;
}

 
