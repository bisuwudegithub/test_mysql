/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
       ListNode *listnode_head =  head;
        vector<int> arr;
        while(listnode_head != NULL)
        {
            arr.push_back(listnode_head->val);
            listnode_head = listnode_head->next;
        }
        reverse(arr.begin(),arr.end());
        return arr;
    }
};