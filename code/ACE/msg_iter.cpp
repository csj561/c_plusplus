#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 

#include "ace/Message_Queue.h"
#include "ace/Get_Opt.h"
#include "ace/Malloc_T.h"
#define SIZE_BLOCK 1
class Args
{
public:
    Args(int argc, char*argv[],int& no_msgs, ACE_Message_Queue<ACE_NULL_SYNCH>* &mq)
    {
ACE_Get_Opt get_opts(argc,argv,"h:l:t:n:xsd");
        while((opt=get_opts())!=-1)
            switch(opt)
            {
            case 'n':
//set the number of messages we wish to enqueue and dequeue
                no_msgs=ACE_OS::atoi(get_opts.optarg);
                ACE_DEBUG((LM_INFO,"Number of Messages %d \n",no_msgs));
                break;
            case 'h':
//set the high water mark
                hwm=ACE_OS::atoi(get_opts.optarg);
                mq->high_water_mark(hwm);
                ACE_DEBUG((LM_INFO,"High Water Mark %d msgs \n",hwm));
                break;
            case 'l':
//set the low water mark
                lwm=ACE_OS::atoi(get_opts.optarg);
                mq->low_water_mark(lwm);
                ACE_DEBUG((LM_INFO,"Low Water Mark %d msgs \n",lwm));
                break;
            default:
                ACE_DEBUG((LM_ERROR,
                           "Usage -n<no. messages> -h<hwm> -l<lwm>\n"));
                break;
            }
    }
private:
    int opt;
    int hwm;
    int lwm;
};
class QTest
{
public:
    QTest(int argc, char*argv[])
    {
//First create a message queue of default size.
        if(!(this->mq_=new ACE_Message_Queue<ACE_NULL_SYNCH> ()))
            ACE_DEBUG((LM_ERROR,"Error in message queue initialization \n"));
//Use the arguments to set the water marks and the no of messages
        args_ = new Args(argc,argv,no_msgs_,mq_);
    }
    int start_test()
    {
        for(int i=0; i<no_msgs_; i++)
        {
//Create a new message block of data buffer size 1
            ACE_Message_Block * mb= new ACE_Message_Block(SIZE_BLOCK);
//Insert data into the message block using the rd_ptr
            *mb->wr_ptr()=i;
//Be careful to advance the wr_ptr
            mb->wr_ptr(1);
//Enqueue the message block onto the message queue
            if(this->mq_->enqueue_prio(mb)==-1)
            {
                ACE_DEBUG((LM_ERROR,"\nCould not enqueue on to mq!!\n"));
                return -1;
            }
ACE_DEBUG((LM_INFO,"EQ'd data: %d\n",*mb->rd_ptr()));
        }
//Use the iterators to read
        this->read_all();
//Dequeue all the messages
        this->dequeue_all();
        return 0;
    }
    void read_all()
    {
ACE_DEBUG((LM_INFO,"No. of Messages on Q:%d Bytes on Q:%d \n"
                   ,mq_->message_count(),mq_->message_bytes()));
        ACE_Message_Block *mb;
//Use the forward iterator
        ACE_DEBUG((LM_INFO,"\n\nBeginning Forward Read \n"));
        ACE_Message_Queue_Iterator<ACE_NULL_SYNCH> mq_iter_(*mq_);
        while(mq_iter_.next(mb))
        {
            mq_iter_.advance();
            ACE_DEBUG((LM_INFO,"Read data %d\n",*mb->rd_ptr()));
        }
//Use the reverse iterator
        ACE_DEBUG((LM_INFO,"\n\nBeginning Reverse Read \n"));
        ACE_Message_Queue_Reverse_Iterator<ACE_NULL_SYNCH>
        mq_rev_iter_(*mq_);
        while(mq_rev_iter_.next(mb))
        {
            mq_rev_iter_.advance();
            ACE_DEBUG((LM_INFO,"Read data %d\n",*mb->rd_ptr()));
        }
    }
    void dequeue_all()
    {
        ACE_DEBUG((LM_INFO,"\n\nBeginning DQ \n"));
ACE_DEBUG((LM_INFO,"No. of Messages on Q:%d Bytes on Q:%d \n",
                   mq_->message_count(),mq_->message_bytes()));
        ACE_Message_Block *mb;
//dequeue the head of the message queue until no more messages
//are left
        for(int i=0; i<no_msgs_; i++)
        {
            mq_->dequeue_head(mb);
            ACE_DEBUG((LM_INFO,"DQ'd data %d\n",*mb->rd_ptr()));
        }
    }
private:
    Args *args_;
    ACE_Message_Queue<ACE_NULL_SYNCH> *mq_;
    int no_msgs_;
};
int main(int argc, char* argv[])
{
    QTest test(argc,argv);
    if(test.start_test()<0)
        ACE_DEBUG((LM_ERROR,"Program failure \n"));
}

