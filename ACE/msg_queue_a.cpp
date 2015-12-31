#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 
#include "msg_queue_a.h"
QTest::QTest(int num_msgs)
    :no_msgs_(num_msgs)
{
    ACE_TRACE("QTest::QTest");
//First create a message queue of default size.
    if(!(this->mq_=new ACE_Message_Queue<ACE_NULL_SYNCH> ()))
        ACE_DEBUG((LM_ERROR,"Error in message queue initialization \n"));
}
int QTest::enq_msgs()
{
    ACE_TRACE("QTest::enq_msg");
    for(int i=0; i<no_msgs_; i++)
    {
//create a new message block specifying exactly how large
//an underlying data block should be created.
        ACE_Message_Block *mb;
        ACE_NEW_RETURN(mb,
                       ACE_Message_Block(ACE_OS::strlen("This is message 1\n")),
                       -1);

//Insert data into the message block using the wr_ptr
        ACE_OS::sprintf(mb->wr_ptr(), "This is message %d\n", i);
//Be careful to advance the wr_ptr by the necessary amount.
//Note that the argument is of type "size_t" that is mapped to
//bytes.
        mb->wr_ptr(ACE_OS::strlen("This is message 1\n"));
//Enqueue the message block onto the message queue
        if(this->mq_->enqueue_prio(mb)==-1)
        {
            ACE_DEBUG((LM_ERROR,"\nCould not enqueue on to mq!!\n"));
            return -1;
        }
        ACE_DEBUG((LM_INFO,"EQ'd data: %s\n", mb->rd_ptr() ));
    } //end for
//Now dequeue all the messages
    this->deq_msgs();
    return 0;
}
int QTest::deq_msgs()
{
    ACE_TRACE("QTest::dequeue_all");
    ACE_DEBUG((LM_INFO,"No. of Messages on Q:%d Bytes on Q:%d \n"
               ,mq_->message_count(),mq_->message_bytes()));
    ACE_Message_Block *mb;
//dequeue the head of the message queue until no more messages are
//left. Note that I am overwriting the message block mb and I since
//I am using the dequeue_head() method I dont have to worry about
//resetting the rd_ptr() as I did for the wrt_ptr()
    for(int i=0; i <no_msgs_; i++)
    {
        mq_->dequeue_head(mb);
        ACE_DEBUG((LM_INFO,"DQ'd data %s\n", mb->rd_ptr() ));
//Release the memory associated with the mb
        mb->release();
    }

    return 0;
}
int main(int argc, char* argv[])
{
    if(argc <2)
        ACE_ERROR_RETURN((LM_ERROR, "Usage %s num_msgs", argv[0]), -1);
    QTest test(ACE_OS::atoi(argv[1]));
    if(test.enq_msgs() == -1)
        ACE_ERROR_RETURN( (LM_ERROR,"Program failure \n"), -1);
}