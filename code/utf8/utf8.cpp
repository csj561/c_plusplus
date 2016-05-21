#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void delHead2Byte(const string &ifile,const string &ofile)
{
	const int K=1024;
	ifstream ifs(ifile.c_str());
	ofstream ofs(ofile.c_str(),ofstream::out|ofstream::trunc);
	char buf[K];
	if(!ifs||!ofs)
		return ;
	cout<<"i pos : "<<ifs.tellg()<<endl;
	ifs.seekg(2);
	cout<<"i pos : "<<ifs.tellg()<<endl;
	while(!ifs.eof()){
	ifs.read(buf,K);
	if(ifs.gcount()>0)
		ofs.write(buf,ifs.gcount());
	}
	ifs.close();
	ofs.close();
}

int main(int argc,char **argv)
{
	string ifile,ofile;
	ifile=argv[1];
	ofile+="utf8-"+ifile;
	delHead2Byte(ifile,ofile);
	return 0;
}