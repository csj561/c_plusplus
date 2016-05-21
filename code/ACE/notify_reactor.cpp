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
#define WAIT_TIME 1
#define SLEEP_TIME 2
class My_Handler:public ACE_Event_Handler  {
  public:
//Start the event handling process.
    My_Handler()  {
        ACE_DEBUG((LM_DEBUG, "Event Handler created\n"));
        ACE_Reactor::instance()->max_notify_iterations(5);
        return;
    }
    
//Perform the notifications i.e., notify the reactor 10 times
    void perform_notifications()  {
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
  private:static int no;
};


//Static members
int My_Handler::no = 1;
int main(int argc, char *argv[]) 
{
    ACE_DEBUG((LM_DEBUG, "Starting test \n"));
    
//Instantiating the handler
        My_Handler handler;
    
//The done flag is set to not done yet.
    int done = 0;
    while (1)
        
    {
        
//After WAIT_TIME the handle_events will fall through if no events
//arrive.
		ACE_Time_Value tv(WAIT_TIME);
        ACE_Reactor::instance()->handle_events(tv);
        if (!done)
            
        {
            handler.perform_notifications();
            done = 1;
        }
        sleep(SLEEP_TIME);
    }
}

 
