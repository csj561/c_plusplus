#include "ace/OS.h"
#include "ace/Task.h"
#include <ace/Future.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h> 
#include <ace/Time_Value.h> 
#include <signal.h>
#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include <ace/SOCK_Dgram.h>
#include <ace/INET_Addr.h>
#include <fool.h>
#include <cassert>
#include <udp_punch.hpp>
typedef ACE_Singleton <ACE_Reactor,  ACE_Thread_Mutex > Reactor;
using namespace std;

class udp_sender:ACE_Task<ACE_MT_SYNCH>//,ACE_Event_Handler
{
	typedef fool::security_list<packet> Slist;
	Slist out_dat;
	ACE_INET_Addr remote_addr;
public:
	udp_sender(const ACE_INET_Addr &local_addr):remote_addr(local_addr),register_out(false),_sock(ACE_INET_Addr())
	{
		Reactor::instance()->register_handler(0,this,ACE_Event_Handler::READ_MASK);
        Reactor::instance()->register_handler(_sock.get_handle(),this,ACE_Event_Handler::READ_MASK);
	}
private:
	ACE_SOCK_Dgram _sock;
	bool register_out;
	int handle_input(ACE_HANDLE fd)
	{
		char buf[2*K];
		ACE_Time_Value tm(0);
		memset(buf,0,sizeof(buf));
		if(0==fd)
		{
			cout<<"input ..."<<endl;
			size_t trunc=1;
			int len=0;
			do
			{
				ACE_OS::read_n(fd,buf+len,1);
			}while(buf[len++]!='\n');
			TLV *tlv=TLV_factory(0,len-1,buf);
			out_dat.push(packet(remote_addr,tlv));
			if(!register_out)
			{
				Reactor::instance()->register_handler(_sock.get_handle(),this,ACE_Event_Handler::WRITE_MASK);
				register_out=true;
				DEG("push out!!!");
			}
			//cout<<"push to out"<<endl;
		}
		else
		{
			ACE_INET_Addr faddr;
			int sz = _sock.recv(buf,sizeof(buf),faddr,0,&tm);
			cout<<"Get Data From Sock >> "<<buf<<endl;
		}
		return 0;
	}
	int handle_output(ACE_HANDLE fd)
	{
		packet out_pkg;
		cout<<"out put pkg"<<endl;
		if(out_dat.pop(out_pkg))
		{
			ACE_Time_Value tm(0);
			_sock.send(out_pkg.tlv->val,out_pkg.tlv->len,
				ACE_INET_Addr(out_pkg.port,out_pkg.ip),0,&tm);
		}
		if(!out_dat.size())
		{
			register_out=false;
			return -1;
		}
		return 0;
	}
};

int main()
{
	udp_sender svr(ACE_INET_Addr(5555,"127.0.0.1"));
	while(1)
		Reactor::instance()->handle_events();
}

