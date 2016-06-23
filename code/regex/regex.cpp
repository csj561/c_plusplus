#include <fool.h>
#include <regex>
using namespace std;

int main(int argc,char **argv)
{
	regex r("aab*cc");
	smatch result;
	string s(argv[1]);
	if(regex_search(s,result,r))
		cout<<result.str()<<endl;
	return 0;
}
