#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 

#include <signal.h>
#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
//Create our subclass to handle the signal events
//that we wish to handle. Since we know that this particular
//event handler is going to be using signals we only overload the
//handle_signal method.
/*
MyEventHandler总是动态分配的，否则，全局内存堆可能会崩溃。确保类总是动态地创建的一种办法是将析构器移动到类的私有区域去。
*/
class MyEventHandler:public ACE_Event_Handler  {
    int handle_signal(int signum, siginfo_t *, ucontext_t *)  {
        switch (signum)
            
        {
            case SIGWINCH:
                ACE_DEBUG((LM_DEBUG, "You pressed SIGWINCH \n"));
                break;
                case
                    SIGINT:ACE_DEBUG((LM_DEBUG, "You pressed SIGINT \n"));
                break;
        }
        return 0;
    }

	int handle_input (int fd)
	{
		const int K = 1024;
		char buf[K];
		char c;
		ACE_OS::memset(buf,0,K);
		ACE::read_n(fd,&c,1);
		ACE_DEBUG((LM_DEBUG, "fd [%d] get input [%d]\n",fd,c));
		return 0;
	}
	
	int handle_timeout(const  ACE_Time_Value &current_time,   
        const   void  *act  /* = 0 */ )
	{
		ACE_DEBUG((LM_DEBUG, "get timer [%d] time [%d] \n",(int)act,current_time.sec()));
		return 0;
	}
	virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
	{
		delete this; //commit suicide
	}
	private:
		~MyEventHandler(){/*destroy internal data members*/}
};

/*
可以重载的函数
handle_signal()
信号。当任何在反应器上登记的信号发生时，反应器自动回调该方法。
handle_input()
来自I/O设备的输入。当I/O句柄（比如UNIX中的文件描述符）上的输入可用时，反应器自动回调该方法。
handle_exception()
异常事件。当已在反应器上登记的异常事件发生时（例如，如果收到SIGURG（紧急信号）），反应器自动回调该方法。
handle_timeout()
定时器。当任何已登记的定时器超时的时候，反应器自动回调该方法。
handle_output()
I/O设备输出。当I/O设备的输出队列有可用空间时，反应器自动回调该方法。


隐式拆除是更为常用的从反应器中拆除事件处理器的技术。事件处理器的每个“handle_”方法都会返回一个整数给反应器。
如果此整数为0，在处理器方法完成后、事件处理器将保持在反应器上的登记。但是，如果“handle_”方法返回的整数<0，
反应器将自动回调此事件处理器的handle_close()方法，并将它从自己的内部分派表中拆除。handle_close()方法用于执行
处理器特有的任何清除工作，它们需要在事件处理器被拆除前完成；其中可以包括像删除处理器申请的动态内存、
或关闭日志文件这样的工作。
*/

/*
另一种从反应器的内部表中拆除事件处理器的方法是显式地调用反应器的remove_handler()方法集。
在remove_handler()被调用时，反应器还自动调用事件处理器的handle_close()方法。
可以这样来对其进行控制：将ACE_Event_Handler::DONT_CALL掩码传给remove_handler()，从而使得handle_close()方法不会被调用。
*/
int main(int argc, char *argv[]) 
{
    
//instantiate the handler
        MyEventHandler * eh = new MyEventHandler;
    
//Register the handler asking to call back when either SIGWINCH
//or SIGINT signals occur. Note that in both the cases we asked the
//Reactor to callback the same Event_Handler i.e., MyEventHandler.
//This is the reason why we had to write a switch statement in the
//handle_signal() method above. Also note that the ACE_Reactor is
//being used as a Singleton object (Singleton pattern)
    ACE_Reactor::instance()->register_handler(SIGWINCH, eh);
    ACE_Reactor::instance()->register_handler(SIGINT, eh);

	/*注册文件描述描0(标准输入)上面的事件*/
	ACE_Reactor::instance()->register_handler(ACE_HANDLE(0), eh,ACE_Event_Handler::READ_MASK);

	/*注册时间事件，时间为相对时间。2表示第一次触发事件在2秒后，之后的触周期为5秒*/
	ACE_Reactor::instance()->schedule_timer(eh,(void *)666,ACE_Time_Value(2),ACE_Time_Value(5));
    while (1)
        
//Start the reactors event loop
    ACE_Reactor::instance()->handle_events();
}


