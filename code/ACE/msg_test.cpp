#include "ace/Message_Queue.h"
#include "ace/OS.h"

int main(int argc, char *argv[]) 
{
    ACE_Message_Block *mb = new ACE_Message_Block (30);
   	// ACE_OS::sprintf(mb->wr_ptr(),"%s","hello");
   	mb->copy("xyd",1);
	/*mb->rd_ptr (),mb->wr_ptr()�ĳ�ʼֵ����ͬ�ģ�ʹ��copy wr_ptr������ƶ�*/
    ACE_OS::printf("%p::%p\n",mb->rd_ptr (),mb->wr_ptr());
    mb->release();
    return 0; 
}

