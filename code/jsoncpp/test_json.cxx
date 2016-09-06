#include <json/json.h>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
using namespace Json;
int main()
{
	Value root;
	root["num"]=Value(123);
	root["str"]=Value("string");
	Value root1(root);
	root["root1"]=root1;
	Value arr;
	arr.append("aaa");
	arr.append("bbb");
	arr.append(123);
	root["array"]=arr;
	
	cout<<root<<endl;
	const char *str=strdup(FastWriter().write(root).c_str());
	printf("str =  %s \n",str);
	Value out;
	Reader().parse(str,out);
	cout<<out["num"]<<endl;
	cout<<out["root1"]<<endl;
}

