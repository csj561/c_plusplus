#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <string>
#include <cctype>
#include <logger.h>
#ifndef K
#define K 1024
#endif

boost::asio::io_service io_svr;
boost::asio::ip::tcp::endpoint _endpoint(
	boost::asio::ip::address::from_string("10.0.2.111"),11111);
boost::asio::ip::tcp::acceptor _acceptor(io_svr,_endpoint);
typedef boost::asio::ip::tcp::socket tcpSock;
using boost::shared_ptr;
static int idx=0;
void read_cb(boost::shared_ptr<tcpSock> _sock_ptr,shared_ptr<char> buf,const boost::system::error_code &ec,size_t sz);
void toUpper(char *s,size_t sz)
{
	while(sz--)
		if(islower(s[sz]))
			s[sz]=toupper(s[sz]);
}

void write_cb(boost::shared_ptr<tcpSock> _sock_ptr,shared_ptr<char> buf,const boost::system::error_code &ec,size_t sz)
{
	if(!ec)
	{
		if(sz)
			_sock_ptr->async_read_some(boost::asio::buffer(buf.get(),sz),boost::bind(&read_cb,_sock_ptr,buf,_1,_2));
		else
			LOG_NOT("Write sz [%d]",sz);
	}
}
void read_cb(boost::shared_ptr<tcpSock> _sock_ptr,shared_ptr<char> buf,const boost::system::error_code &ec,size_t sz)
{
	if(!ec&&sz>0)
	{
		buf.get()[sz]=0;
		LOG_INFO("client [%s] say: [%s]",_sock_ptr->remote_endpoint().address().to_string().c_str(),buf.get());
		toUpper(buf.get(),sz);
		_sock_ptr->async_write_some(boost::asio::buffer(buf.get(),sz),boost::bind(&write_cb,_sock_ptr,buf,_1,_2));
	}
	else
	{
		LOG_NOT("lose client [%s] index [%d]",_sock_ptr->remote_endpoint().address().to_string().c_str(),idx--);
	}
}
void accept_cb(boost::shared_ptr<tcpSock> _sock_ptr,const boost::system::error_code &ec)
{
	if(!ec)
	{
		LOG_NOT("get a client [%s] index [%d]",_sock_ptr->remote_endpoint().address().to_string().c_str(),idx++);
		shared_ptr<char> buf_ptr(new char[K/2]);
		_sock_ptr->async_read_some(boost::asio::buffer(buf_ptr.get(),K/2),boost::bind(&read_cb,_sock_ptr,buf_ptr,_1,_2));
	}
	_sock_ptr.reset(new tcpSock(io_svr));
	_acceptor.async_accept(*_sock_ptr,boost::bind(&accept_cb,_sock_ptr,boost::asio::placeholders::error));
}
int main()
{
	_acceptor.listen();
	shared_ptr<tcpSock> sock_ptr(new tcpSock(io_svr));
	_acceptor.async_accept(*sock_ptr,boost::bind(&accept_cb,sock_ptr,boost::asio::placeholders::error));
	io_svr.run();
}
