#include <cstring>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
using namespace std;
#include <boost/asio/local/stream_protocol.hpp>


boost::asio::io_service iose;
using namespace boost::asio::local;

int main()
{

	while(1)
	{
		stream_protocol::socket sock(iose);
		char buf[1024];
		memset(buf,0,sizeof(buf));
		const char *s="I am client.";
		sock.connect(stream_protocol::endpoint("unix.sock"));
		sock.write_some( boost::asio::buffer(s,strlen(s)));
		sock.read_some( boost::asio::buffer(buf,1024));
		cout<<"get response "<< buf<<endl;
		break;
	}
	return 0;
}

