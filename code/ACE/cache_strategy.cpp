#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 

#include "ace/Reactor.h"
#include "ace/Svc_Handler.h"
#include "ace/Connector.h"
#include "ace/Synch.h"
#include "ace/SOCK_Connector.h"
#include "ace/INET_Addr.h"
#include <ace/Functor_T.h> 


#define PORT_NUM 10101
#define DATA_SIZE 16
//forward declaration
class My_Svc_Handler;

//Function prototype
static void make_connections (void *arg);

// Template specializations for the hashing function for the
// hash_map which is used by the cache. The cache is used internally by the
// Cached Connection Strategy . Here we use ACE_Hash_Addr
// as our external identifier. This utility class has already
// overloaded the == operator and the hash() method. (The
// hashing function). The hash() method delegates the work to
// hash_i() and we use the IP address and port to get a
// a unique integer hash value.
//typedef unsigned long u_long;
//u_long ACE_Hash_Addr < ACE_INET_Addr >::hash_i (const ACE_INET_Addr & addr) const 
//{
//  return addr.get_ip_address () + addr.get_port_number ();
//}


//instantiate a strategy acceptor
typedef ACE_Strategy_Connector < My_Svc_Handler, ACE_SOCK_CONNECTOR >  STRATEGY_CONNECTOR;

//Instantiate the Creation Strategy
typedef ACE_NOOP_Creation_Strategy < My_Svc_Handler >  NULL_CREATION_STRATEGY;

//Instantiate the Concurrency Strategy
typedef ACE_NOOP_Concurrency_Strategy < My_Svc_Handler >  NULL_CONCURRENCY_STRATEGY;

//Instantiate the Connection Strategy
typedef ACE_Cached_Connect_Strategy < My_Svc_Handler, 
    ACE_SOCK_CONNECTOR,   ACE_SYNCH_RW_MUTEX >  CACHED_CONNECT_STRATEGY;
class My_Svc_Handler:public ACE_Svc_Handler < ACE_SOCK_STREAM, ACE_MT_SYNCH > 
{
private:
	char *data;
public:
	My_Svc_Handler () 
  {
    data = new char[DATA_SIZE];
  } 
	My_Svc_Handler (ACE_Thread_Manager * tm) 
  {
    data = new char[DATA_SIZE];
  } 
//Called before the service handler is recycled..
  int recycle (void *a = 0) 
  {
    ACE_DEBUG ((LM_DEBUG, "(%P|%t) recycling Svc_Handler %d with handle %d\n", this, this->peer ().get_handle ()));
    return 0;
  }
  int open (void *) 
  {
    ACE_DEBUG ((LM_DEBUG, "(%t)Connection established \n"));
    
//Register the service handler with the reactor
    ACE_Reactor::instance () ->register_handler (this, ACE_Event_Handler::READ_MASK);
    activate (THR_NEW_LWP | THR_DETACHED);
    return 0;
  }
  int handle_input (ACE_HANDLE) 
  {
    ACE_DEBUG ((LM_DEBUG, "Got input in thread: (%t) \n"));
    peer ().recv_n (data, DATA_SIZE);
     ACE_DEBUG ((LM_DEBUG, "<< %s\n", data));
    
//keep yourself registered with the reactor
        return 0;
  }
  int svc (void) 
  {
    
//send a few messages and then mark connection as idle so that it can
// be recycled later.
        ACE_DEBUG ((LM_DEBUG, "Started the service routine \n"));
    for (int i = 0; i < 3; i++)
      
    {
      ACE_DEBUG ((LM_DEBUG, "(%t)>>Hello World\n"));
      ACE_OS::fflush (stdout);
      peer ().send_n ("Hello World", sizeof ("Hello World"));
    }
    
//Mark the service handler as being idle now and let the
//other threads reuse this connection
        this->idle (1);
    
//Wait for the thread to die
        this->thr_mgr ()->wait ();
    return 0;
  }
};

ACE_INET_Addr * addr;
int main (int argc, char *argv[]) 
{
  addr = new ACE_INET_Addr (PORT_NUM, argv[1]);
  
//Creation Strategy
      NULL_CREATION_STRATEGY creation_strategy;
  
//Concurrency Strategy
      NULL_CONCURRENCY_STRATEGY concurrency_strategy;
  
//Connection Strategy
      CACHED_CONNECT_STRATEGY caching_connect_strategy;
   
//instantiate the connector
      STRATEGY_CONNECTOR connector (ACE_Reactor::instance (),  //the reactor to use
                                    &creation_strategy, &caching_connect_strategy, &concurrency_strategy);
  
//Use the thread manager to spawn a single thread
//to connect multiple times passing it the address
//of the strategy connector
      if (ACE_Thread_Manager::instance ()->spawn (
                                                  (ACE_THR_FUNC) make_connections, 
                                                  (void *) &connector, THR_NEW_LWP) == -1)
    ACE_ERROR ((LM_ERROR, "(%P|%t) %p\n%a", "client thread spawn failed"));
  while (1)                    /* Start the reactor's event loop */
    ACE_Reactor::instance ()->handle_events ();
}


//Connection establishment function, tries to establish connections
//to the same server again and re-uses the connections from the cache
void make_connections (void *arg) 
{
  ACE_DEBUG ((LM_DEBUG, "(%t)Prepared to connect \n"));
  STRATEGY_CONNECTOR * connector = (STRATEGY_CONNECTOR *) arg;
  for (int i = 0; i < 10; i++)
    
  {
    My_Svc_Handler * svc_handler = 0;
    
// Perform a blocking connect to the server using the Strategy
// Connector with a connection caching strategy. Since we are
// connecting to the same <server_addr> these calls will return the
// same dynamically allocated <Svc_Handler> for each <connect> call.
        if (connector->connect (svc_handler, *addr) == -1)
      
    {
      ACE_ERROR ((LM_ERROR, "(%P|%t) %p\n", "connection failed\n"));
      return;
    }
    
// Rest for a few seconds so that the connection has been freed up
        ACE_OS::sleep (5);
  }
 }

 
