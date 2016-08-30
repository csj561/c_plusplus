#define BOOST_ALL_NO_LIB 
#include <boost/program_options.hpp>
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char **argv)
{
	using namespace boost::program_options;
	options_description opt("demo description");
	opt.add_options()
		("help,h","help option")
		("filename,f",value<string>(),"file option");
	variables_map vm;
	store(parse_command_line(argc,argv,opt),vm);
	if(vm.count("help"))
	{
		cout<<opt<<endl;
		return 0;
	}
	if(vm.count("f"))
	{
		cout<<"file:"<<vm["filename"].as<string>()<<endl;
	}
	if(vm.count("filename"))
	{
		cout<<"filename:"<<vm["filename"].as<string>()<<endl;
	}
	return 0;
}
