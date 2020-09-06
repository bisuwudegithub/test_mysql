#include <WinSock2.h>

#include "HTTP.h"
#pragma comment(lib,"ws2_32.lib")
//���캯��
CHttp::CHttp()
{
	WSADATA wd;
	//��ʼ������
	WSAStartup(MAKEWORD(2,2),&wd);

	//HTTPЭ��ײ���ͨ��TCPЭ��ʵ�ֵ�
	m_socket = socket(AF_INET,SOCK_STREAM,0);
};

//��������
bool CHttp::Connect()
{
	hostent* p = gethostbyname(m_host.c_str());
	if(p == NULL)
	{
		return false;
	}
	sockaddr_in sa;
	memcpy(&sa.sin_addr,p->h_addr,4);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(80); //�������ֽ�˳��ת��Ϊ�����ֽ�˳��

	if(SOCKET_ERROR == connect(m_socket,(sockaddr*)&sa,sizeof(sockaddr)))
	{
		return false;
	}
	return true;
}

//����URL
bool CHttp::AnalyseURL(string url)
{
	//https://    baike.baidu.com  /item/������/22747470?fr=aladdin
	if(string::npos == url.find("http://"))//npos����ö�ٳ�����Ϊ-1
	{
		return false;
	}
	if(url.length() <= 7)
	{
		return false;
	}

	int pos = url.find('/',7);
	//https://    baike.baidu.com
	if(string::npos == pos)
	{
		m_host = url.substr(7);
		m_object = "/";
	}
	//https://    baike.baidu.com  /
	//https://    baike.baidu.com  /item/������/22747470?fr=aladdin
	else
	{
		m_host = url.substr(7,pos-7);
		m_object = url.substr(pos);
	}
	if(m_host.empty() )
		return false;

	cout<<"������" << m_host <<endl;
	cout<<"��Դ����" << m_object <<endl;
	return true;

}

//��ȡ��ҳ
bool CHttp::GetHtml(std::string& html)
{
	//������ͷ�����Ҫ��Ҫ�ĸ���ҳ
	//�������FiddleSetup.exe,�����ҳ
	std::string info;
	info += "GET " + m_object + " HTTP/1.1\r\n";
	info += "Host: " + m_host + "\r\n";
	info += "Connection: Close\r\n";
	info += "User-Agent: Mozilla/5.0(Windows NT 10.0; WOW64) AppleWebKit/537.36(KHTML,like Gecko) Chrome/69.0.3497.100 Safari/537.36\r\n";
	info += "\r\n";

	if(SOCKET_ERROR == send(m_socket,info.c_str(),info.length(),0))
		return false;

	//����
	char ch = 0;
	while(recv(m_socket,&ch,sizeof(ch),0))
	{
		html += ch;
	}

	return true;
}