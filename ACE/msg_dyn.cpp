#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 

#include "ace/Message_Queue.h"
#include "ace/Get_Opt.h"
#include "ace/OS.h"

class Args 
{
public:Args (int argc, char *argv[], int &no_msgs, int &time, ACE_Message_Queue < ACE_NULL_SYNCH > *&mq) 
  {
    ACE_Get_Opt get_opts (argc, argv, "h:l:t:n:xsd");
    while ((opt = get_opts ()) != -1)
      switch (opt)
        
      {
          case 't':
            time = ACE_OS::atoi (get_opts.optarg);
            ACE_DEBUG ((LM_INFO, "Time: %d \n", time));
            break;
          case 'n':
            no_msgs = ACE_OS::atoi (get_opts.optarg);
            ACE_DEBUG ((LM_INFO, "Number of Messages %d \n", no_msgs));
            break;
          case 'x':
            mq = ACE_Message_Queue_Factory < ACE_NULL_SYNCH >::create_laxity_message_queue ();
            ACE_DEBUG ((LM_DEBUG, "Creating laxity q\n"));
            break;
          case 'd':
            mq = ACE_Message_Queue_Factory < ACE_NULL_SYNCH >::create_deadline_message_queue ();
            ACE_DEBUG ((LM_DEBUG, "Creating deadline q\n"));
            break;
          case 's':
            mq = ACE_Message_Queue_Factory < ACE_NULL_SYNCH >::create_static_message_queue ();
            ACE_DEBUG ((LM_DEBUG, "Creating static q\n"));
            break;
          case 'h':
            hwm = ACE_OS::atoi (get_opts.optarg);
            mq->high_water_mark (hwm);
            ACE_DEBUG ((LM_INFO, "High Water Mark %d msgs \n", hwm));
            break;
          case 'l':
            lwm = ACE_OS::atoi (get_opts.optarg);
            mq->low_water_mark (lwm);
            ACE_DEBUG ((LM_INFO, "Low Water Mark %d msgs \n", lwm));
            break;
          default:
            ACE_DEBUG ((LM_ERROR, "Usage specify queue type\n"));
            break;
      }
  }
private:int opt;
  int hwm;
  int lwm;
};

class QTest 
{
public:QTest (int argc, char *argv[]) 
  {
    args_ = new Args (argc, argv, no_msgs_, time_, mq_);
    array_ = new ACE_Message_Block *[no_msgs_];
  } int start_test () 
  {
    for (int i = 0; i < no_msgs_; i++)
      
    {
      ACE_NEW_RETURN (array_[i], ACE_Message_Block (1), -1);
      set_deadline (i);
      set_execution_time (i);
      enqueue (i);
    } this->dequeue_all ();
    return 0;
  }
  
//Call the underlying ACE_Message_Block method msg_deadline_time() to
//set the deadline of the message.
  void set_deadline (int msg_no) 
  {
    float temp = (float) time_ / (msg_no + 1);
    ACE_Time_Value tv;
    tv.set (temp);
    ACE_Time_Value deadline (ACE_OS::gettimeofday () + tv);
    array_[msg_no]->msg_deadline_time (deadline);
    ACE_DEBUG ((LM_INFO, "EQ'd with DLine %d:%d,", deadline.sec (), deadline.usec ()));
  } 
//Call the underlying ACE_Message_Block method to set the execution time
  void set_execution_time (int msg_no) 
  {
    float temp = (float) time_ / 10 * msg_no;
    ACE_Time_Value tv;
    tv.set (temp);
    ACE_Time_Value xtime (ACE_OS::gettimeofday () + tv);
    array_[msg_no]->msg_execution_time (xtime);
    ACE_DEBUG ((LM_INFO, "Xtime %d:%d,", xtime.sec (), xtime.usec ()));
  } void enqueue (int msg_no) 
  {
    
//Set the value of data at the read position
        *array_[msg_no]->rd_ptr () = msg_no;
    
//Advance write pointer
        array_[msg_no]->wr_ptr (1);
    
//Enqueue on the message queue
        if (mq_->enqueue_prio (array_[msg_no]) == -1)
      
    {
      ACE_DEBUG ((LM_ERROR, "\nCould not enqueue on to mq!!\n"));
      return;
    }
    ACE_DEBUG ((LM_INFO, "Data %d\n", *array_[msg_no]->rd_ptr ()));
  }
  void dequeue_all () 
  {
    ACE_DEBUG ((LM_INFO, "Beginning DQ \n"));
    ACE_DEBUG ((LM_INFO, "No. of Messages on Q:%d Bytes on Q:%d \n", mq_->message_count (), mq_->message_bytes ()));
    for (int i = 0; i < no_msgs_; i++)
      
    {
      ACE_Message_Block * mb;
      if (mq_->dequeue_head (mb) == -1)
        
      {
        ACE_DEBUG ((LM_ERROR, "\nCould not dequeue from mq!!\n"));
        return;
      }
      ACE_DEBUG ((LM_INFO, "DQ'd data %d\n", *mb->rd_ptr ()));
    }
  }
private:Args * args_;
  ACE_Message_Block ** array_;
  ACE_Message_Queue < ACE_NULL_SYNCH > *mq_;
  int no_msgs_;
  int time_;
};

int
main (int argc, char *argv[]) 
{
  QTest test (argc, argv);
  if (test.start_test () < 0)
    ACE_DEBUG ((LM_ERROR, "Program failure \n"));
}

 
