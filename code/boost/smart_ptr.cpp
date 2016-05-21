#include <memory>
#include <iostream>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>


using namespace std;
using namespace boost;
/// boost::noncopyable 继承该类的则无法复制和赋值 
/// scoped_ptr 继承自nocopyable
int main()
{
	auto_ptr<int> ip(new int(100));
	auto_ptr<int> ip2(ip);
	//cout<<*ip.get()<<endl;
	cout<<*ip2<<endl;
	scoped_ptr<int> sp(new int(123456));
	scoped_ptr<int> spp();
	//spp = sp;
	cout<<*sp<<endl;
	shared_ptr<int > shp(new int(88888));
	cout<<*shp<<endl;
}
