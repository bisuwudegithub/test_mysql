#include "Spider.h"
#include "HTTP.h"
//http获取
int main()
{
	cout<<"********************************************"<<endl;
	cout<<"         欢迎使用人工智能网络爬虫系统       "<<endl;
	cout<<"********************************************"<<endl;
	cout<<"请输入要抓取的URL链接:"<<endl;

	//下载图片时，照片下载到此文件夹
	//创建文件夹 L告诉编译器：字符串要使用Unicode编码
	CreateDirectory(L"image",NULL);

	std::string starturl;
	cin >> starturl;

	//开始抓取
	StartCatch(starturl);

}

//开始抓取
bool StartCatch(std::string url)
{
	queue<string> q;
	//插入一条url
	q.push(url);

	//循环不停的从队列中取出url
    while(!q.empty())
	{
		string currentUrl = q.front();
		q.pop();

		cout<< "取出" <<currentUrl << endl;
		CHttp http;
		http.AnalyseURL(currentUrl);
		if(FALSE == http.Connect())
		{
			cout << "链接失败！"<<endl;
		}
		else
		{
			cout << "链接成功！"<<endl;
		}
        //获取网页
	    string html;
	    http.GetHtml(html);
	    cout << html << endl;
	}
	

	return true;

}
