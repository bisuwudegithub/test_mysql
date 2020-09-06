#include <iostream>
#include <string>

using namespace std;
//http获取
class CHttp
{
public:
	bool AnalyseURL(std::string url);//解析URL
	CHttp();                        //构造函数
	bool Connect();                 //连接网络
	bool GetHtml(std::string& html);//获取网页
private:
	std::string m_host;    //域名
	std::string m_object;  //资源名
	SOCKET m_socket;       //客户端套接字 
};