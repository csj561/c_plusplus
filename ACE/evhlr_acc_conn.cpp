#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 
#include <ace/Event_Handler.h> 
//#include "ace/Svc_Handler.h"
#include "ace/Acceptor.h"
#include "ace/SOCK_Acceptor.h"

#include "ace/Reactor.h"

#include "ace/Synch.h"
#include <iostream>
using namespace std;
#define PORT_NUM 10101
#define DATA_SIZE 12
//forward declaration
    class My_Event_Handler;

//Create the Acceptor class
typedef ACE_Acceptor < My_Event_Handler/*It's error. The SVC_HANDLER typically inherits from ACE_Svc_Handler.*/, 
	ACE_SOCK_ACCEPTOR >  MyAcceptor;

//Create an event handler similar to as seen in example 2. We have to
//overload the get_handle() method and write the peer() method. We also
//provide the data member peer_ as the underlying stream which is
//used.
class My_Event_Handler:public ACE_Event_Handler 
{
private:
	char *data;
  
//Add a new attribute for the underlying stream which will be used by
//the Event Handler
      ACE_SOCK_Stream peer_;
public:
	My_Event_Handler () 
  {
    data = new char[DATA_SIZE];
  } 
	int open (void *) 
  {
    cout << "Connection established" << endl;
    
//Register the event handler with the reactor
        ACE_Reactor::instance ()->register_handler (this, ACE_Event_Handler::READ_MASK);
    return 0;
  }
  int handle_input (ACE_HANDLE) 
  {
    
// After using the peer() method of our ACE_Event_Handler to obtain a
//reference to the underlying stream of the service handler class we
//call recv_n() on it to read the data which has been received. This
//data is stored in the data array and then printed out
        peer ().recv_n (data, DATA_SIZE);
    ACE_OS::printf ("<< %s\n", data);
    
// keep yourself registered with the reactor
        return 0;
  }
  
// new method which returns the handle to the reactor when it
//asks for it.
  ACE_HANDLE get_handle (void) const 
  {
     return this->peer_.get_handle ();
  }
   
//new method which returns a reference to the peer stream
    ACE_SOCK_Stream & peer (void) const 
  {
     return (ACE_SOCK_Stream &) this->peer_;
  }
 };
int main (int argc, char *argv[]) 
{
  ACE_INET_Addr addr (PORT_NUM);
  
//create the acceptor
  MyAcceptor acceptor (addr,        //address to accept on
                           ACE_Reactor::instance ());   //the reactor to use
  while (1)                     /* Start the reactor's event loop */
    ACE_Reactor::instance ()->handle_events ();
}

 
