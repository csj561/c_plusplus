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
         return this->peer_acceptor.get_handle();/*返回底层的套接字描述述*/
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
其它掩码

掩码
回调方法
何时
和..一起使用

ACE_Event_Handler::READ_MASK
handle_input()
在句柄上有数据可读时。
register_handler()

ACE_Event_Handler::WRITE_MASK
handle_output()
在I/O设备输出缓冲区上有可用空间、并且新数据可以发送给它时。
register_handler()

ACE_Event_Handler::TIMER_MASK
handle_close()
传给handle_close()以指示调用它的原因是超时。
接受器和连接器的handle_timeout方法。反应器不使用此掩码。

ACE_Event_Handler::ACCEPT_MASK
handle_input()
在OS内部的侦听队列上收到了客户的新连接请求时。
register_handler()

ACE_Event_Handler::CONNECT_MASK
handle_input()
在连接已经建立时。
register_handler()

ACE_Event_Handler::DONT_CALL
None.
在反应器的remove_handler()被调用时保证事件处理器的handle_close()方法不被调用。
remove_handler()

*/
     
//Start the event loop
        while (1)
        ACE_Reactor::instance()->handle_events();
}

  
