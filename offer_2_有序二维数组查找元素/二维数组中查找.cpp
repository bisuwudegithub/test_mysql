class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        //选取右上角或者左下角的元素a与target比较，
        //target<a时:target在行的左边
        //target>a时:target在列的下边
        int row = 0;//第一行
        int col = array[0].size() -1;//最后一列
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