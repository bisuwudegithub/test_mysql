static int x=[]{
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.empty())
        {
            return 0;
        }
        int right = rotateArray.size()-1;
        int left = 0;
        while(left < right)
        {
            //�ж��Ƿ���С���������
            if(rotateArray[left] < rotateArray[right])
            {
                return rotateArray[left];
            }
            //�ָ���ұߵ������Ӧ�����������˵ģ����Լ���left
            int mid = (right - left) / 2 + left;
            
            //�ж��м�λ�õ�����Ƿ�����,����������
             if(rotateArray[mid] >= rotateArray[left])
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
           
        }
        return rotateArray[right];
    }
};