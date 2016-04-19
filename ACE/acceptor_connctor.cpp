#include "ace/Reactor.h"
#include "ace/Svc_Handler.h"
#include "ace/Acceptor.h"
#include "ace/Synch.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Thread.h"
#include <ace/Connector.h> 
#include <ace/SOCK_Connector.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
class MyServiceHandler;
#define PORT_NO 20001
const char * HOSTNAME; 
using namespace std;
//Add our own Reactor singleton
typedef ACE_Singleton < ACE_Reactor, ACE_Null_Mutex > Reactor;
 
//Create an Acceptor
typedef ACE_Acceptor < MyServiceHandler, ACE_SOCK_ACCEPTOR > Acceptor;
 vector<ACE_SOCK_Stream *> vstreams;
//Create a Connector
typedef ACE_Connector < MyServiceHandler, ACE_SOCK_CONNECTOR > Connector;
class MyServiceHandler:public ACE_Svc_Handler < ACE_SOCK_STREAM,
    ACE_NULL_SYNCH > 
{
  public:
//Used by the two threads "globally" to determine their peer stream
     
//Thread ID used to identify the threads
        ACE_thread_t t_id;
		bool thread_creat;
    int open(void *) {
        cout << "Acceptor: received new connection this:: " <<(unsigned long)this<< endl;
         
//Register with the reactor to remember this handle
            Reactor::instance()->register_handler(this,
                                                  ACE_Event_Handler::READ_MASK);
         vstreams.push_back(&peer());
//Determine the peer stream and record it globally
         
//Spawn new thread to send string every second
			if(!thread_creat)
			{
            ACE_Thread::spawn((ACE_THR_FUNC) send_data, NULL, THR_NEW_LWP,
                              &t_id);
			thread_creat=true;
			}
         
//keep the service handler registered by returning 0 to the
//reactor
            return 0;
    }
    static void *send_data(void *p) {
        while (1)
             
        {
        	for(typeof(vstreams.begin()) Peer=vstreams.begin();
				Peer!=vstreams.end();Peer++)
				{
				char buf[20];
				sprintf(buf,"%d",ACE_OS::getpid());
            	(*Peer)->send_n(buf, ACE_OS::strlen(buf));
				}
             
//Go to sleep for a second before sending again
                ACE_OS::sleep(1);
        }
        return 0;
    }
    int handle_input(ACE_HANDLE) {
        char *data = new char[128];
         ACE_Time_Value tv(0);
//Check if peer aborted the connection
            if (peer().recv_n(data, 128,&tv) == 0)
             
        {
            cout << "Peer probably aborted connection" << endl;
            ACE_Thread::cancel(t_id);  //kill sending thread ..
            return -1;          //de-register from the Reactor.
        }
         
//Show what you got..
            cout << "Got data pid:"<<ACE_OS::getpid()<<" ::" << data << endl;
         
//keep yourself registered
            return 0;
    }
};

void main_accept() 
{
    ACE_INET_Addr addr(PORT_NO);
    Acceptor myacceptor(addr, Reactor::instance());
    while (1)
        Reactor::instance()->handle_events();
    return ;
}

 void main_connect() 
{
    ACE_INET_Addr addr(PORT_NO, HOSTNAME);
    Connector myconnector;
	MyServiceHandler * my_svc_handler = new MyServiceHandler();
    myconnector.connect(my_svc_handler, addr);
    while (1)
        Reactor::instance()->handle_events();
}

 int main(int argc, char *argv[]) 
{
     
// Use ACE_Get_Opt to parse and obtain arguments and then call the
// appropriate function for accept or connect.... 
	//pid_t pid = ACE::fork();
	cout<<"My pid is "<<ACE_OS::getpid()<<endl;
	HOSTNAME=argv[1];
	if(argc==1)
	{
		main_accept();
	}
	else if(argc >1)
	{
		ACE_OS::sleep(1);
		main_connect();
	}
	else 
	{
		cerr<<"Fork err !!!"<<endl;
	}
	return 0;
} 
