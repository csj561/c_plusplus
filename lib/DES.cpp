#include <iostream>
#include <crypto++/des.h>
using namespace std;
using namespace CryptoPP;

int main( void )
{
    //��Ҫ�Ǵ�ӡһЩ������Ϣ��������ԣ�
    cout << "DES Parameters: " << endl;
    cout << "Algorithm name : " << DES::StaticAlgorithmName() << endl; 
    
    unsigned char key[ DES::DEFAULT_KEYLENGTH ];
    unsigned char input[ DES::BLOCKSIZE ] = "12345";
    unsigned char output[ DES::BLOCKSIZE ];
    unsigned char txt[ DES::BLOCKSIZE ];

    cout << "input is: " << input << endl;

    //�����������ȹ���һ��������
    DESEncryption encryption_DES;

    //����һ��֮ǰ�ı������ԳƼ����㷨��Ҫһ���ܳס����ܺͽ��ܶ����õ���
    //��ˣ������ܳס�
    encryption_DES.SetKey( key, DES::KEYLENGTH );
    //���м���
    encryption_DES.ProcessBlock( input, output );

    //��ʾ���
    //for��for֮���cout���п��ޣ���ҪΪ�����е�ʱ�򿴼��ܽ��
    //���ַ����ĳ���д��һ��������ʵ�������Ƽ���
    //������������֪���ַ�������Ϊ�˷�����ԣ���ֱ��д�¡�
    //������Ҫ�ǰ�outputҲ���Ǽ��ܺ�����ݣ���ʮ�����Ƶ�������ʽ�����
    for( int i = 0; i < 5; i++ )
    {
        cout << hex << (int)output[ i ] << ends;
    }
    cout << endl;

    //����һ��������
    DESDecryption decryption_DES;    

    //���ڶԳƼ����㷨�ļ��ܺͽ��ܶ���ͬһ���ܳף�
    //��˽��ܵ�ʱ�����õ��ܳ�Ҳ�Ǹղ��ڼ���ʱ���úõ�key
    decryption_DES.SetKey( key, DES::KEYLENGTH );
    //���н��ܣ��ѽ��д��txt��
    //decryption_DES.ProcessAndXorBlock( output, xorBlock, txt );
    decryption_DES.ProcessBlock( output, txt );

    //���ϣ����ܣ����ܻ�ԭ�����Ѿ������ˡ�������Ϊ����֤��
    //����ǰ�����ĺͽ��ܺ�������Ƿ���ȡ�
    if ( memcmp( input, txt, 5 ) != 0 )
    {
        cerr << "DES Encryption/decryption failed.\n";
        abort();
    }
    cout << "DES Encryption/decryption succeeded.\n";
    
    return 0;
}


