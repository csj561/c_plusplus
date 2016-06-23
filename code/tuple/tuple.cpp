#include <tuple>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	tuple<size_t,string> tp(100,"tuple test");
	size_t sz=tuple_size<decltype(tp)>::value; /// 获取元素个数
	cout<<"size : "<<sz<<endl;
	cout<<"index 0 : "<<get<0>(tp)<<endl;/// 通过下标获取元素
	cout<<"index 1 : "<<get<1>(tp)<<endl;
	
	tuple_element<1,decltype(tp)>::type tp1=("type of index 1");/// 通过下标获取元素类型
	return 0;
}
