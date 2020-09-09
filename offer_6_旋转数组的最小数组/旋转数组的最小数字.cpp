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
            //判断是否最小的在最左端
            if(rotateArray[left] < rotateArray[right])
            {
                return rotateArray[left];
            }
            //分割后右边的最左端应该相对于最左端的，所以加上left
            int mid = (right - left) / 2 + left;
            
            //判断中间位置的左边是否有序,如果左边无序
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