#include "Spider.h"
#include "HTTP.h"
//http��ȡ
int main()
{
	cout<<"********************************************"<<endl;
	cout<<"         ��ӭʹ���˹�������������ϵͳ       "<<endl;
	cout<<"********************************************"<<endl;
	cout<<"������Ҫץȡ��URL����:"<<endl;

	//����ͼƬʱ����Ƭ���ص����ļ���
	//�����ļ��� L���߱��������ַ���Ҫʹ��Unicode����
	CreateDirectory(L"image",NULL);

	std::string starturl;
	cin >> starturl;

	//��ʼץȡ
	StartCatch(starturl);

}

//��ʼץȡ
bool StartCatch(std::string url)
{
	queue<string> q;
	//����һ��url
	q.push(url);

	//ѭ����ͣ�ĴӶ�����ȡ��url
    while(!q.empty())
	{
		string currentUrl = q.front();
		q.pop();

		cout<< "ȡ��" <<currentUrl << endl;
		CHttp http;
		http.AnalyseURL(currentUrl);
		if(FALSE == http.Connect())
		{
			cout << "����ʧ�ܣ�"<<endl;
		}
		else
		{
			cout << "���ӳɹ���"<<endl;
		}
        //��ȡ��ҳ
	    string html;
	    http.GetHtml(html);
	    cout << html << endl;
	}
	

	return true;

}
