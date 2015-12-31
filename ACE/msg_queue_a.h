#ifndef MQ_EG1_H_
#define MQ_EG1_H_
#include "ace/Message_Queue.h"
class QTest
{
public:
//Constructor creates a message queue with no synchronization
    QTest(int num_msgs);
//Enqueue the num of messages required onto the message mq.
    int enq_msgs();
//Dequeue all the messages previously enqueued.
    int deq_msgs ();
private:
//Underlying message queue
    ACE_Message_Queue<ACE_NULL_SYNCH> *mq_;
//Number of messages to enqueue.
    int no_msgs_;
};
#endif /*MQ_EG1.H_*/