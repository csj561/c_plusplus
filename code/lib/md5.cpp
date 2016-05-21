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
  
//======================== MD5�㷨====================
   std::cout<<"======= MD5�㷨======="<<std::endl;
   std::string strInput = "";
   std::cout<<"Pls input message info:"<<std::endl;
   std::cin>>strInput;
 
   //MD5�㷨���������ݿ��������ⳤ�ȵ��ַ���
   int len = strInput.length();
   byte *message = new byte[len+1];
   message[len]=0;
   memcpy(message,strInput.c_str(),len+1);
   std::cout<<"message: "<<message<<endl;
 
   //MD5���ɵ���ϢժҪ�̶�����λ�����ֽڣ�
   byte digest[16];
   MD5 md5;
   md5.CalculateDigest(digest, message, len); //�ȼ����������д���֮��
   //ע�⣬�˴�len������message���ַ�����,�������ɵĹ�ϣֵ��һ��һ��
   //md5.Update(message, len);
   //md5.Final(digest);
 
   std::cout<<"Algorithm name :"<<md5.AlgorithmName()<<std::endl;
   std::cout<<"md5 digest��";
   for(int i=0; i<16; i++)
   {
      printf("%02x", digest[i]);
   }
   cout<<endl;
}

