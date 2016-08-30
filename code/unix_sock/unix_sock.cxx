#include <cstring>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
using namespace std;
#include <boost/asio/local/stream_protocol.hpp>
#include <unistd.h>

using namespace boost::asio::local;
boost::asio::io_service iose;

const char *sock_file="unix.sock";
int main()
{
	::unlink(sock_file);
	stream_protocol::acceptor acceptor(iose,
		stream_protocol::endpoint(sock_file));
	while(1)
	{
		stream_protocol::socket sock(iose);
		char buf[1024];
		memset(buf,0,sizeof(buf));
		acceptor.accept(sock);
		if (sock.read_some( boost::asio::buffer(buf,sizeof(buf)))>0)
		{
			cout<<"read:"<< buf<<endl;
			strcpy(buf,"I got it");
			sock.write_some(boost::asio::buffer(buf,strlen(buf)));
		}
	}
	return 0;
}
