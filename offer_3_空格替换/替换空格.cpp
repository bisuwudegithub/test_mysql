class Solution {
public:
	void replaceSpace(char *str,int length) {
        int a = 0;//遍历字符串，保存空格的个数
        for(int i = 0;i < length;i++){
            if(str[i]==' ')
                a++;
        }
        //int real_length = strlen(str) + a*2;//扩容
        //从最后一个字符开始，
        //如果不是空格，将字符拷贝到当前位置，
        //如果是空格，将%20分别填入算好的位置中，空格数--
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