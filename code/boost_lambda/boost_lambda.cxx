#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace boost::lambda;
int main()
{
    char buf[]={'a','b','c'};
    for_each(buf,buf+sizeof(buf),cout<< boost::lambda::_1 << std::endl);
}