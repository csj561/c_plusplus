#include<com.h>
#include<boost/algorithm/string.hpp>
using namespace boost;

int main()
{
	vector<string> v;
	string s("fafdasd23fasfdbaf43asfdafa");
	split(v,s,is_any_of("13"));
	fool::Pri(v);
}
