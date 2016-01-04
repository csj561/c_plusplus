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
MyEventHandler���Ƕ�̬����ģ�����ȫ���ڴ�ѿ��ܻ������ȷ�������Ƕ�̬�ش�����һ�ְ취�ǽ��������ƶ������˽������ȥ��
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
�������صĺ���
handle_signal()
�źš����κ��ڷ�Ӧ���ϵǼǵ��źŷ���ʱ����Ӧ���Զ��ص��÷�����
handle_input()
����I/O�豸�����롣��I/O���������UNIX�е��ļ����������ϵ��������ʱ����Ӧ���Զ��ص��÷�����
handle_exception()
�쳣�¼��������ڷ�Ӧ���ϵǼǵ��쳣�¼�����ʱ�����磬����յ�SIGURG�������źţ�������Ӧ���Զ��ص��÷�����
handle_timeout()
��ʱ�������κ��ѵǼǵĶ�ʱ����ʱ��ʱ�򣬷�Ӧ���Զ��ص��÷�����
handle_output()
I/O�豸�������I/O�豸����������п��ÿռ�ʱ����Ӧ���Զ��ص��÷�����


��ʽ����Ǹ�Ϊ���õĴӷ�Ӧ���в���¼��������ļ������¼���������ÿ����handle_���������᷵��һ����������Ӧ����
���������Ϊ0���ڴ�����������ɺ��¼��������������ڷ�Ӧ���ϵĵǼǡ����ǣ������handle_���������ص�����<0��
��Ӧ�����Զ��ص����¼���������handle_close()���������������Լ����ڲ����ɱ��в����handle_close()��������ִ��
���������е��κ����������������Ҫ���¼������������ǰ��ɣ����п��԰�����ɾ������������Ķ�̬�ڴ桢
��ر���־�ļ������Ĺ�����
*/

/*
��һ�ִӷ�Ӧ�����ڲ����в���¼��������ķ�������ʽ�ص��÷�Ӧ����remove_handler()��������
��remove_handler()������ʱ����Ӧ�����Զ������¼���������handle_close()������
����������������п��ƣ���ACE_Event_Handler::DONT_CALL���봫��remove_handler()���Ӷ�ʹ��handle_close()�������ᱻ���á�
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

	/*ע���ļ�������0(��׼����)������¼�*/
	ACE_Reactor::instance()->register_handler(ACE_HANDLE(0), eh,ACE_Event_Handler::READ_MASK);

	/*ע��ʱ���¼���ʱ��Ϊ���ʱ�䡣2��ʾ��һ�δ����¼���2���֮��Ĵ�����Ϊ5��*/
	ACE_Reactor::instance()->schedule_timer(eh,(void *)666,ACE_Time_Value(2),ACE_Time_Value(5));
    while (1)
        
//Start the reactors event loop
    ACE_Reactor::instance()->handle_events();
}


