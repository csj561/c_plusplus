#include "ace/Reactor.h"
#include "ace/Svc_Handler.h"
#include "ace/Acceptor.h"
#include "ace/Synch.h"
#include "ace/SOCK_Acceptor.h"
#include <ace/Connector.h>
#include <ace/SOCK_Connector.h> 
#include <iostream>
using namespace std;
 
#define HOSTNAME "127.0.0.1"
    
#define PORT_NO 10101
//Create a Service Handler whose open() method will be called back
//automatically. This class MUST derive from ACE_Svc_Handler which is an
//interface and as can be seen is a template container class itself. The
//first parameter to ACE_Svc_Handler is the underlying stream that it
//may use for communication. Since we are using TCP sockets the stream
//is ACE_SOCK_STREAM. The second is the internal synchronization
//mechanism it could use. Since we have a single threaded application we
//pass it a "null" lock which will do nothing.
int a=0;

class My_Svc_Handler:public ACE_Svc_Handler < ACE_SOCK_STREAM, ACE_NULL_SYNCH > 
{
     
//the open method which will be called back automatically after the
//connection has been established.
/*成功连接时自动调用open方法*/ 
  public:
  int open(void *) 
  	{
        cout << "connector Connection established" << endl;
		ACE_Reactor::instance()->register_handler(this,ACE_Event_Handler::READ_MASK);
		if(ACE_OS::fork()==0)
			a=5;
		ACE_Reactor::instance()->register_handler(this,ACE_Event_Handler::WRITE_MASK);
	}
  int handle_input(ACE_HANDLE)
  	{
  		char buf[100]={0};
		ACE_Time_Value tv(0);
		peer().recv_n(buf,100,&tv);
		cout<<"get data ::"<<buf<<endl;
		
		return 0;
  	}
  int handle_output(ACE_HANDLE)
  	{
  		ACE_OS::sleep(a);
  		const char *buf="I got msg!";
  		cout<<"sent msg :: "<<buf<<endl;
		peer().send_n(buf,ACE_OS::strlen(buf));
		ACE_Reactor::instance()->remove_handler(this, ACE_Event_Handler::DONT_CALL|ACE_Event_Handler::WRITE_MASK);
		return 0;
  	}
};

 typedef ACE_Connector < My_Svc_Handler,  ACE_SOCK_CONNECTOR > MyConnector;
int main(int argc, char *argv[]) 
{
    ACE_INET_Addr addr(PORT_NO, HOSTNAME);
    My_Svc_Handler * handler = new My_Svc_Handler;
     
//Create the connector
        MyConnector connector;
     
//Connects to remote machine
        if (connector.connect(handler, addr) == -1)
        ACE_ERROR((LM_ERROR, "%P|%t, %p", "Connection failed"));
     
//Registers with the Reactor
        while (1)
        ACE_Reactor::instance()->handle_events();
}

  
