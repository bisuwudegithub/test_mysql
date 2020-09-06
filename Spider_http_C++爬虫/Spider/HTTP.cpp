#include <WinSock2.h>

#include "HTTP.h"
#pragma comment(lib,"ws2_32.lib")
//构造函数
CHttp::CHttp()
{
	WSADATA wd;
	//初始化网络
	WSAStartup(MAKEWORD(2,2),&wd);

	//HTTP协议底层是通过TCP协议实现的
	m_socket = socket(AF_INET,SOCK_STREAM,0);
};

//链接网络
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
	sa.sin_port = htons(80); //将主机字节顺序转换为网络字节顺序

	if(SOCKET_ERROR == connect(m_socket,(sockaddr*)&sa,sizeof(sockaddr)))
	{
		return false;
	}
	return true;
}

//解析URL
bool CHttp::AnalyseURL(string url)
{
	//https://    baike.baidu.com  /item/王北车/22747470?fr=aladdin
	if(string::npos == url.find("http://"))//npos代表枚举常量，为-1
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
	//https://    baike.baidu.com  /item/王北车/22747470?fr=aladdin
	else
	{
		m_host = url.substr(7,pos-7);
		m_object = url.substr(pos);
	}
	if(m_host.empty() )
		return false;

	cout<<"域名：" << m_host <<endl;
	cout<<"资源名：" << m_object <<endl;
	return true;

}

//获取网页
bool CHttp::GetHtml(std::string& html)
{
	//先请求和服务器要需要哪个网页
	//下载软件FiddleSetup.exe,监控网页
	std::string info;
	info += "GET " + m_object + " HTTP/1.1\r\n";
	info += "Host: " + m_host + "\r\n";
	info += "Connection: Close\r\n";
	info += "User-Agent: Mozilla/5.0(Windows NT 10.0; WOW64) AppleWebKit/537.36(KHTML,like Gecko) Chrome/69.0.3497.100 Safari/537.36\r\n";
	info += "\r\n";

	if(SOCKET_ERROR == send(m_socket,info.c_str(),info.length(),0))
		return false;

	//接受
	char ch = 0;
	while(recv(m_socket,&ch,sizeof(ch),0))
	{
		html += ch;
	}

	return true;
}