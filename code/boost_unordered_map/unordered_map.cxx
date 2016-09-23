#include <boost/unordered_map.hpp>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
using namespace std;
using namespace boost::lambda;
#define boostmap boost::unordered_map
int main()
{
    boostmap<string ,int > m;
    for(int i=0;i<2000000;i++)
    {
        char buf[100];
        sprintf(buf,"key%09d",i);
        m[buf]=i;
    }
    printf("end init\n");
}