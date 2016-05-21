#include <iostream>
#include <crypto++/aes.h>

using namespace std; 
using namespace CryptoPP;

int main()
{

    //AES��ʹ�õĹ̶�����������AES�ж����enum�������ͳ��ֵģ������ǳ�Ա���������
    //�����Ҫ��::����������
    cout << "AES Parameters: " << endl;
    cout << "Algorithm name : " << AES::StaticAlgorithmName() << endl;      

    //Crypto++����һ�����ֽ�������ʾ���ȣ������ǳ��õ��ֽ���
    cout << "Block size     : " << AES::BLOCKSIZE * 8 << endl;
    cout << "Min key length : " << AES::MIN_KEYLENGTH * 8 << endl;
    cout << "Max key length : " << AES::MAX_KEYLENGTH * 8 << endl;

    //AES��ֻ����һЩ�̶������ݣ������ܽ��ܵĹ�����AESEncryption��AESDecryption�����
    //���ܹ���
    AESEncryption aesEncryptor; //������ 

    unsigned char aesKey[AES::DEFAULT_KEYLENGTH];  //��Կ
    unsigned char inBlock[AES::BLOCKSIZE] = "123456789";    //Ҫ���ܵ����ݿ�
    unsigned char outBlock[AES::BLOCKSIZE]; //���ܺ�����Ŀ�
    unsigned char xorBlock[AES::BLOCKSIZE]; //�����趨Ϊȫ��

    memset( xorBlock, 0, AES::BLOCKSIZE ); //����

    aesEncryptor.SetKey( aesKey, AES::DEFAULT_KEYLENGTH );  //�趨������Կ
    aesEncryptor.ProcessAndXorBlock( inBlock, xorBlock, outBlock );  //����

    //��16������ʾ���ܺ������
    for( int i=0; i<16; i++ ) {
        cout << hex << (int)outBlock[i] << " ";
    }
    cout << endl;

    //����
    AESDecryption aesDecryptor;
    unsigned char plainText[AES::BLOCKSIZE];

    aesDecryptor.SetKey( aesKey, AES::DEFAULT_KEYLENGTH );
    //ϸ�ĵ�����ע�⵽����ĺ�������֮ǰ��DES�г��ֹ��ģ�ProcessBlock��
    //���Ƕ���һ��Xor����ʵ��ProcessAndXorBlockҲ��DES�汾���÷���AES�汾��ࡣ
    //���߷ֱ������ݴ������г�����������������Ȥ�����ѿ����Լ��о�һ���кβ��졣
    aesDecryptor.ProcessAndXorBlock( outBlock, xorBlock, plainText );


    for( int i=0; i<16; i++ ) 
    {      
        cout << plainText[i];   
    }
    cout << endl;

    return 0;
}



