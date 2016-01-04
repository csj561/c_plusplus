#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h>
#include "ace/Reactor.h"
#include "ace/SOCK_Acceptor.h"
#include <ace/Event_Handler.h>
#include <ace/Svc_Handler.h>


#define PORT_NO 19998
typedef ACE_SOCK_Acceptor Acceptor;
 
//forward declaration
    class My_Accept_Handler;
class My_Input_Handler:public ACE_Event_Handler 
{
  public:
//Constructor
        My_Input_Handler() 
    {
        ACE_DEBUG((LM_DEBUG, "Constructor\n"));
    } 
//Called back to handle any input received
    int handle_input(ACE_HANDLE)  {
         
//receive the data
        peer_i().recv_n(data, 12);
        ACE_DEBUG((LM_DEBUG, "%s\n", data));
         
// do something with the input received.
// ...
//keep yourself registered with the reactor
            return 0;
    }
     
//Used by the reactor to determine the underlying handle
    ACE_HANDLE get_handle()const  {
         return peer_.get_handle();
    }
    
//Returns a reference to the underlying stream.
     ACE_SOCK_Stream & peer_i()  {
        return this->peer_;
    }
  private:ACE_SOCK_Stream peer_;
    char data[12];
};

 class My_Accept_Handler:public ACE_Event_Handler 
{
  public:
//Constructor
        My_Accept_Handler(ACE_Addr & addr) 
    {
        this->open(addr);
    } 
//Open the peer_acceptor so it starts to "listen"
//for incoming clients.
    int open(ACE_Addr & addr)  {
	/*Initialize a passive-mode BSD-style acceptor socket (no QoS).
	<local_sap> is the address that we're going to listen for connections on.
	If <reuse_addr> is 1 then we'll use the <SO_REUSEADDR> to reuse this address. 
	Returns 0 on success and -1 on failure. 
    */
        peer_acceptor.open(addr,1);
        return 0;
    }
     
//Overload the handle input method
    int handle_input(ACE_HANDLE handle)  {
         
//Client has requested connection to server.
//Create a handler to handle the connection
            My_Input_Handler * eh = new My_Input_Handler();
         
//Accept the connection "into" the Event Handler
            if (this->peer_acceptor.accept(eh->peer_i(),  // stream
                                           0,   // remote address
                                           0,   // timeout
                                           1) == -1)    //restart if interrupted
            ACE_DEBUG((LM_ERROR, "Error in connection\n"));
        ACE_DEBUG((LM_DEBUG, "Connection established\n"));
         
//Register the input event handler for reading
            ACE_Reactor::instance()->register_handler(eh,
                                                      ACE_Event_Handler::READ_MASK);
         
//Unregister as the acceptor is not expecting new clients
            return -1;
    }
     
//Used by the reactor to determine the underlying handle
    ACE_HANDLE get_handle(void) const  {
         return this->peer_acceptor.get_handle();/*���صײ���׽���������*/
    }
  private: Acceptor peer_acceptor;
};

 int main(int argc, char *argv[]) 
{
     
//Create an address on which to receive connections
        ACE_INET_Addr addr(PORT_NO);
     
//Create the Accept Handler which automatically begins to "listen"
//for client requests for connections
        My_Accept_Handler * eh = new My_Accept_Handler(addr);
     
//Register the reactor to call back when incoming client connects
        ACE_Reactor::instance()->register_handler(eh,
                                                  ACE_Event_Handler::ACCEPT_MASK);

/*
��������

����
�ص�����
��ʱ
��..һ��ʹ��

ACE_Event_Handler::READ_MASK
handle_input()
�ھ���������ݿɶ�ʱ��
register_handler()

ACE_Event_Handler::WRITE_MASK
handle_output()
��I/O�豸������������п��ÿռ䡢���������ݿ��Է��͸���ʱ��
register_handler()

ACE_Event_Handler::TIMER_MASK
handle_close()
����handle_close()��ָʾ��������ԭ���ǳ�ʱ��
����������������handle_timeout��������Ӧ����ʹ�ô����롣

ACE_Event_Handler::ACCEPT_MASK
handle_input()
��OS�ڲ��������������յ��˿ͻ�������������ʱ��
register_handler()

ACE_Event_Handler::CONNECT_MASK
handle_input()
�������Ѿ�����ʱ��
register_handler()

ACE_Event_Handler::DONT_CALL
None.
�ڷ�Ӧ����remove_handler()������ʱ��֤�¼���������handle_close()�����������á�
remove_handler()

*/
     
//Start the event loop
        while (1)
        ACE_Reactor::instance()->handle_events();
}

  
