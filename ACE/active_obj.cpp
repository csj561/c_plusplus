/// ACE主动对象模式

#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 
#define ACE_Method_Object ACE_Method_Request
typedef unsigned long u_long;

//The worker thread with which the client will interact
class Logger:public ACE_Task < ACE_MT_SYNCH > 
{
public:
//Initialization and termination methods
      Logger ();
  virtual ~ Logger (void);
  virtual int open (void *);
  virtual int close (u_long flags = 0);
  
//The entry point for all threads created in the Logger
  virtual int svc (void);
  
///////////////////////////////////////////////////////
//Methods which can be invoked by client asynchronously.
///////////////////////////////////////////////////////
//Log message
      ACE_Future < u_long > logMsg (const char *msg);
  
//Return the name of the Task
  ACE_Future < const char *>name (void);
  
///////////////////////////////////////////////////////
//Actual implementation methods for the Logger
///////////////////////////////////////////////////////
      u_long logMsg_i (const char *msg);
  const char *name_i ();
private:char *name_;
  ACE_Activation_Queue activation_queue_;
};

 
//Method Object which implements the logMsg() method of the active
//Logger active object class
class logMsg_MO:public ACE_Method_Object 
{
public:
//Constructor which is passed a reference to the active object, the
//parameters for the method, and a reference to the future which
//contains the result.
      logMsg_MO (Logger * logger, const char *msg, ACE_Future < u_long > &future_result);
  virtual ~ logMsg_MO ();
  
//The call() method will be called by the Logger Active Object
//class, once this method object is dequeued from the activation
//queue. This is implemented so that it does two things. First it
//must execute the actual implementation method (which is specified
//in the Logger class. Second, it must set the result it obtains from
//that call in the future object that it has returned to the client.
//Note that the method object always keeps a reference to the same
//future object that it returned to the client so that it can set the
//result value in it.
  virtual int call (void);
private:Logger * logger_;
  const char *msg_;
  ACE_Future < u_long > future_result_;
};


//Method Object which implements the name() method of the active Logger
//active object class
class name_MO:public ACE_Method_Object 
{
public:
//Constructor which is passed a reference to the active object, the
//parameters for the method, and a reference to the future which
//contains the result.
      name_MO (Logger * logger, ACE_Future < const char *>&future_result);
  virtual ~ name_MO ();
  
//The call() method will be called by the Logger Active Object
//class, once this method object is dequeued from the activation
//queue. This is implemented so that it does two things. First it
//must execute the actual implementation method (which is specified
//in the Logger class. Second, it must set the result it obtains from
//that call in the future object that it has returned to the client.
//Note that the method object always keeps a reference to the same
//future object that it returned to the client so that it can set the
//result value in it.
  virtual int call (void);
private:Logger * logger_;
  ACE_Future < const char *>future_result_;
};

  
//Implementation for the logMsg_MO method object.
//Constructor
logMsg_MO::logMsg_MO (Logger * logger, const char *msg, ACE_Future < u_long > &future_result) :logger_ (logger), msg_ (msg), future_result_ (future_result) 
{
  ACE_DEBUG ((LM_DEBUG, "(%t) logMsg invoked \n"));
} 

//Destructor
    logMsg_MO::~logMsg_MO () 
{
  ACE_DEBUG ((LM_DEBUG, "(%t) logMsg object deleted.\n"));
} 

//Invoke the logMsg() method
int logMsg_MO::call (void) 
{
  return this->future_result_.set (this->logger_->logMsg_i (this->msg_));
}


//Implementation for the name_MO method object.
//Constructor
name_MO::name_MO (Logger * logger, ACE_Future < const char *>&future_result):logger_ (logger), future_result_ (future_result) 
{
  ACE_DEBUG ((LM_DEBUG, "(%t) name() invoked \n"));
} 

//Destructor
    name_MO::~name_MO () 
{
  ACE_DEBUG ((LM_DEBUG, "(%t) name object deleted.\n"));
} 

//Invoke the name() method
int name_MO::call (void) 
{
  return this->future_result_.set (this->logger_->name_i ());
}

 
//Constructor for the Logger
    Logger::Logger () 
{
  this->name_ = new char[sizeof ("Worker")];
ACE_OS:strcpy (name_, "Worker");
}


//Destructor
    Logger::~Logger (void) 
{
  delete this->name_;
} 

//The open method where the active object is activated
int Logger::open (void *) 
{
  ACE_DEBUG ((LM_DEBUG, "(%t) Logger %s open\n", this->name_));
  return this->activate (THR_NEW_LWP);
}


//Called then the Logger task is destroyed.
int Logger::close (u_long flags) 
{
  ACE_DEBUG ((LM_DEBUG, "Closing Logger \n"));
  return 0;
}


//The svc() method is the starting point for the thread created in the
//Logger active object. The thread created will run in an infinite loop
//waiting for method objects to be enqueued on the private activation
//queue. Once a method object is inserted onto the activation queue the
//thread wakes up, dequeues the method object and then invokes the
//call() method on the method object it just dequeued. If there are no
//method objects on the activation queue, the task blocks and falls
//asleep.
int Logger::svc (void) 
{
  while (1)
    
  {
    
// Dequeue the next method object (we use an auto pointer in
// case an exception is thrown in the <call>).
        ACE_Time_Value tv (ACE_OS::time (NULL) + 10, 0);
    auto_ptr < ACE_Method_Object > mo  (this->activation_queue_.dequeue (&tv));
    ACE_DEBUG ((LM_DEBUG, "(%t) calling method object\n"));
    
// Call it.
        if (!mo.get () || mo->call () == -1)
      break;
    
// Destructor automatically deletes it.
  }
  return 0;
}


//////////////////////////////////////////////////////////////
//Methods which are invoked by client and execute asynchronously.
//////////////////////////////////////////////////////////////
//Log this message
    ACE_Future < u_long > Logger::logMsg (const char *msg) 
{
  ACE_Future < u_long > resultant_future;
  
//Create and enqueue method object onto the activation queue
      this->activation_queue_.enqueue  (new logMsg_MO (this, msg, resultant_future));
  return resultant_future;
}


//Return the name of the Task
ACE_Future < const char *>Logger::name (void) 
{
  ACE_Future < const char *>resultant_future;
  
//Create and enqueue onto the activation queue
      this->activation_queue_.enqueue  (new name_MO (this, resultant_future));
  return resultant_future;
}


///////////////////////////////////////////////////////
//Actual implementation methods for the Logger
///////////////////////////////////////////////////////
    u_long Logger::logMsg_i (const char *msg) 
{
  ACE_DEBUG ((LM_DEBUG, "Logged: %s\n", msg));
  
//Go to sleep for a while to simulate slow I/O device
      ACE_OS::sleep (2);
  return 10;
}

const char *Logger::name_i () 
{
  
//Go to sleep for a while to simulate slow I/O device
      ACE_OS::sleep (2);
  return name_;
}

  
//Client or application code.
int main (int, char *[]) 
{
  
//Create a new instance of the Logger task
      Logger * logger = new Logger ();
  
//The Futures or IOUs for the calls that are made to the logger.
      ACE_Future < u_long > logresult;
  ACE_Future < const char *>name;
  
//Activate the logger
      logger->open (0);
  
//Log a few messages on the logger
      for (size_t i = 0; i < 3; i++)
    
  {
    char *msg = new char[50];
    ACE_DEBUG ((LM_DEBUG, "Issuing a non-blocking logging call\n"));
    ACE_OS::sprintf (msg, "This is iteration %d", i);
    logresult = logger->logMsg (msg);
    
        //Don鈥檛 use the log result here as it isn't that important...
  } ACE_DEBUG ((LM_DEBUG, "(%t)Invoked all the log calls \
                    and can now continue with other work \n"));
  
      //Do some work over here...
      // ...
      // ...
      //Find out the name of the logging task
      name = logger->name ();
  
      //Check to "see" if the result of the name() call is available
      if (name.ready ())
    ACE_DEBUG ((LM_DEBUG, "Name is ready! \n"));
  
  else
    ACE_DEBUG ((LM_DEBUG, "Blocking till I get the result of that call \n"));
  
      //obtain the underlying result from the future object.
  const char *task_name;
  name.get (task_name);
  ACE_DEBUG ((LM_DEBUG, "(%t)==> The name of the task is: %s\n\n\n", task_name));
  
      //Wait for all threads to exit.
      ACE_Thread_Manager::instance ()->wait ();
} 
