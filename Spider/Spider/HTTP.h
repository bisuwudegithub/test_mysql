#include <iostream>
#include <string>

using namespace std;
//http��ȡ
class CHttp
{
public:
	bool AnalyseURL(std::string url);//����URL
	CHttp();                        //���캯��
	bool Connect();                 //��������
	bool GetHtml(std::string& html);//��ȡ��ҳ
private:
	std::string m_host;    //����
	std::string m_object;  //��Դ��
	SOCKET m_socket;       //�ͻ����׽��� 
};