class Solution {
public:
	void replaceSpace(char *str,int length) {
        int a = 0;//�����ַ���������ո�ĸ���
        for(int i = 0;i < length;i++){
            if(str[i]==' ')
                a++;
        }
        //int real_length = strlen(str) + a*2;//����
        //�����һ���ַ���ʼ��
        //������ǿո񣬽��ַ���������ǰλ�ã�
        //����ǿո񣬽�%20�ֱ�������õ�λ���У��ո���--
        for(int i = length-1;i >= 0;i--){
            if(str[i]!=' '){
                str[i + 2*a]=str[i];
            }
            else{
                a--;
                str[i + a*2]='%';
                str[i + a*2 + 1]='2';
                str[i + a*2 + 2]='0';
            }
        }
	}
};