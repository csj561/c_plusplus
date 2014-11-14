#include <iostream>
#include <string>
#include <bitset>

using std::bitset;
int main()
{
bitset<32> n(0xff);
n.reset(33);
std::cout<<n.to_ulong()<<std::endl;
}
