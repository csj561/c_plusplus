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
#include <com.h>
#include "udp_punch.hpp"
typedef ACE_Singleton <ACE_Reactor,  ACE_Thread_Mutex > Reactor;
using namespace std;
struct hole_pair
{
	struct hole_info
	{
		uint32_t ip;
		u_short port;
		bool request;
		hole_info():ip(0),port(0),response(false),request(false){}
	};
	hole_info holes[2];
	hole_pair():cnt(0){}
};
class udp_svr:ACE_Task<ACE_MT_SYNCH>//,ACE_Event_Handler
{
	typedef fool::security_list<packet> Slist;
	Slist in_dat;
	Slist out_dat;
	Slist proc_dat;
	map<uint32_t,hole_pair> hole_infos;
public:
	udp_svr(const ACE_INET_Addr &local_addr):_sock(local_addr),register_out(false)
	{
	 	activate(THR_NEW_LWP, 1,    // 1 new threads
                 0,         //force active false, if already created don't try again.
                 ACE_DEFAULT_THREAD_PRIORITY,       //Use default thread priority
                 -1, this,  //Which ACE_Task object to create? In this case this one.
                 0,         // don't care about thread handles used
                 0,         // don't care about where stacks are created
                 0,         //don't care about stack sizes
                 thread_names);     // keep identifiers in thread_names
        Reactor::instance()->register_handler(_sock.get_handle(),this,ACE_Event_Handler::READ_MASK);
	}
private:
	ACE_SOCK_Dgram _sock;
	bool register_out;
	void thread_process()
	{
		while(1)
		{
			do
			{
				packet proc_pkg;
				while(in_dat.pop(proc_pkg))/// 取出数据，整理后存入hole_infos
				{
					uint32_t *session=(uint32_t *)proc_pkg.tlv->val;
					hole_pair::hole_info &hinfo = hole_infos[*session].holes[proc_pkg.tlv->tag&0x1];
					if(!hinfo.request)
					{
						hinfo.ip=proc_pkg.ip;
						hinfo.port=proc_pkg.port;
						hinfo.request=true;
					}
					TLV_destroy(proc_pkg.tlv);
				}
			}while(0);
			
			typeof(hole_infos.begin()) iter=hole_infos.begin();
			for(;iter!=hole_infos.end();iter++) /// 发送
			{
				if(iter->holes[0].request&&iter->holes[1].request)
				{
					char buf[10];
					uint32_t *session=buf;
					uint32_t *ip=buf+4;
					uint16_t *port=buf+8;
					*session = htonl(iter->first);
					*ip=htonl( iter->holes[0].ip);
					*port=htons(iter->holes[0].port)
					packet proc_pkg1(iter->holes[1].ip,iter->holes[1].port,TLV_factory(0,sizeof(buf),buf));
					out_dat.push(proc_pkg1);
					
					*session = htonl(iter->first);
					*ip=htonl( iter->holes[1].ip);
					*port=htons(iter->holes[1].port)
					packet proc_pkg2(iter->holes[0].ip,iter->holes[0].port,TLV_factory(0,sizeof(buf),buf));
					out_dat.push(proc_pkg2);
					if(!register_out)
					{
							Reactor::instance()->register_handler(_sock.get_handle(),this,ACE_Event_Handler::WRITE_MASK);
							register_out=true;
					}
				}
			}
			ACE_OS::sleep(1);
		}
	}
	ACE_thread_t thread_names[2];
	int svc(void)
	{
		thread_process();
		return 0;
	}
	int handle_input(ACE_HANDLE fd)
	{
		char buf[2*K];
		ACE_INET_Addr faddr;
		ACE_Time_Value tm(0);
		int sz = _sock.recv(buf,sizeof(buf),faddr,0,&tm);
		if(sz!=sizeof(TLV)+sizeof(ACE::UINT32))
			return 0;
		TLV *tlv=(TLV *)buf;
		tlv->tag = ntohs(tlv->tag);
		tlv->len = ntohs(tlv->len);
		if(tlv->len!=sz)
			return 0;
		uint32_t *session=(uint32_t *)tlv->val;
		*session=ntohl(*session);
		in_dat.push(packet(faddr,tlv->clone()));
		return 0;
	}
	int handle_output(ACE_HANDLE fd)
	{
		packet out_pkg;
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
	udp_svr svr(ACE_INET_Addr(5555));
	while(1)
		Reactor::instance()->handle_events();
}

