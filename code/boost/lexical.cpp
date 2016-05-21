#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace std;
using namespace boost;

int main()
{
	double d = lexical_cast<double> ("2.6471444");
	cout<<d<<endl;
	d = 2.6471444;
	string s = lexical_cast<string>(d);
	cout<<s<<endl;
}
