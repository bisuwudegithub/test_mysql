class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        //ѡȡ���Ͻǻ������½ǵ�Ԫ��a��target�Ƚϣ�
        //target<aʱ:target���е����
        //target>aʱ:target���е��±�
        int row = 0;//��һ��
        int col = array[0].size() -1;//���һ��
        while(row <= array[0].size() -1 && col >= 0)
        {
            if(target == array[row][col])
                return true;
            else if(target < array[row][col])
            {
                col --;
            }
            else
            {
                row ++;
            }
        }
        return false;
    }
};