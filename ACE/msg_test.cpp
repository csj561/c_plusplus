#include "ace/Message_Queue.h"
#include "ace/OS.h"

int main(int argc, char *argv[]) 
{
    ACE_Message_Block *mb = new ACE_Message_Block (30);
   	// ACE_OS::sprintf(mb->wr_ptr(),"%s","hello");
   	mb->copy("xyd",1);
	/*mb->rd_ptr (),mb->wr_ptr()的初始值是相同的，使用copy wr_ptr会向后移动*/
    ACE_OS::printf("%p::%p\n",mb->rd_ptr (),mb->wr_ptr());
    mb->release();
    return 0; 
}

