#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
 //#include <crypto++/des.h>
#include "crypto++/aes.h"
#include "crypto++/md5.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"
using namespace CryptoPP;
 
 
int main(int argc, char* argv[])
{
  
//======================== MD5算法====================
   std::cout<<"======= MD5算法======="<<std::endl;
   std::string strInput = "";
   std::cout<<"Pls input message info:"<<std::endl;
   std::cin>>strInput;
 
   //MD5算法的输入内容可以是任意长度的字符串
   int len = strInput.length();
   byte *message = new byte[len+1];
   message[len]=0;
   memcpy(message,strInput.c_str(),len+1);
   std::cout<<"message: "<<message<<endl;
 
   //MD5生成的信息摘要固定长度位（个字节）
   byte digest[16];
   MD5 md5;
   md5.CalculateDigest(digest, message, len); //等价于下面两行代码之和
   //注意，此处len必须是message的字符长度,否则生成的哈希值会一次一变
   //md5.Update(message, len);
   //md5.Final(digest);
 
   std::cout<<"Algorithm name :"<<md5.AlgorithmName()<<std::endl;
   std::cout<<"md5 digest：";
   for(int i=0; i<16; i++)
   {
      printf("%02x", digest[i]);
   }
   cout<<endl;
}

