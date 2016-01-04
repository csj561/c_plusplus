#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 

#include "ace/Reactor.h"
#include "ace/Svc_Handler.h"
#include "ace/Acceptor.h"
#include "ace/Synch.h"

#include "ace/SOCK_Acceptor.h"
#include <iostream>

using namespace std;

#define PORT_NUM 10101
#define DATA_SIZE 12
//forward declaration
    class My_Svc_Handler;
 
//instantiate a strategy acceptor
typedef ACE_Strategy_Acceptor < My_Svc_Handler, ACE_SOCK_ACCEPTOR > MyAcceptor;
 
//instantiate a concurrency strategy
typedef ACE_Process_Strategy < My_Svc_Handler > Concurrency_Strategy;
 
// Define the Service Handler
class My_Svc_Handler:public ACE_Svc_Handler < ACE_SOCK_STREAM, ACE_NULL_SYNCH > 
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
  int open (void *) 
  {
    cout << "Connection established" << endl;
     
//Register with the reactor
        ACE_Reactor::instance ()->register_handler (this, ACE_Event_Handler::READ_MASK);
    return 0;
  }
  int handle_input (ACE_HANDLE) 
  {
    peer ().recv_n (data, DATA_SIZE);
    ACE_OS::printf ("<< %s\n", data);
     
// keep yourself registered with the reactor
        return 0;
  }
};

 int main (int argc, char *argv[]) 
{
  ACE_INET_Addr addr (PORT_NUM);
   
//Concurrency Strategy
      Concurrency_Strategy my_con_strat;
   
//Instantiate the acceptor
      MyAcceptor acceptor (addr,        //address to accept on
                           ACE_Reactor::instance (),    //the reactor to use
                           0,   // don't care about creation strategy
                           0,   // don't care about connection estb. strategy
                           &my_con_strat);      // use our new process concurrency strategy
  while (1)                     /* Start the reactor's event loop */
    ACE_Reactor::instance ()->handle_events ();
}

  
