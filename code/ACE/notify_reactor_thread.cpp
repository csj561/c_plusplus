#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 

#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
//#include "ace/Synch_T.h"
#include "ace/Thread_Manager.h"
class My_Handler:public ACE_Event_Handler  {
  public:
//Start the event handling process.
    My_Handler()  {
        ACE_DEBUG((LM_DEBUG, "Got open\n"));
        activate_threads();
        ACE_Reactor::instance()->max_notify_iterations(5);
        return ;
    }
    
//Spawn a separate thread so that it notifies the reactor
    void activate_threads()  {
    /*线程库的使用要求，也就是，线程的入口必须是文件范围内的静态函数。(这里是svc_start)*/
        ACE_Thread_Manager::instance() ->spawn((ACE_THR_FUNC) svc_start,
                                                 (void *) this);
    } 
//Notify the Reactor 10 times.
    void svc()  {
        for (int i = 0; i < 10; i++)
            ACE_Reactor::instance()->notify(this,
                                              ACE_Event_Handler::READ_MASK);
    } 
//The actual handler which in this case will handle the notifications
    int handle_input(int)  {
        ACE_DEBUG((LM_DEBUG, "Got notification # %d\n", no));
        no++;
        return 0;
    }
    
//The entry point for the new thread that is to be created.
    static int svc_start(void *arg);
  private:static int no;
};


//Static members
int My_Handler::no = 1;
int My_Handler::svc_start(void *arg) 
{
    My_Handler * eh = (My_Handler *) arg;
    eh->svc();
    return -1;                 //de-register from the reactor
}

int main(int argc, char *argv[]) 
{
    ACE_DEBUG((LM_DEBUG, "Starting test \n"));
    My_Handler handler;
    while (1)
    {
        ACE_Reactor::instance()->handle_events();
        sleep(3);
    }
}

 
