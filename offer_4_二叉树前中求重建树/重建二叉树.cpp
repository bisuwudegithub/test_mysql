/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        //�õ��������ĳ��ȣ����п�
        int in_len = vin.size();
        if(in_len == 0)
        {
            return NULL;
        }
        //����������ǰ�����������ǰ����������������ǰ�����������������
        vector<int> left_pre, right_pre, left_in, right_in;
        //����ͷ��㣬��ǰ��ĵ�һ���ڵ�
        TreeNode* head = new TreeNode(pre[0]);
        //������������Ҹ��ڵ㣬��������������е�iλ��
        int root = 0;
        for(int i = 0; i < in_len; i++)
        {
            if(vin[i] == pre[0])
            {
               root  = i;
               break;
            }
        }
        //������������������Ǵ�0��root-1
        //ǰ�������������Ҳ�Ǵ�1��root
         for(int i = 0;i < root ; i++)
        {
            left_in.push_back(vin[i]);
            left_pre.push_back(pre[i+1]);
        }
        //������������������Ǵ�root+1�����һλ
        //ǰ�������������Ҳ��root+1�����һλ
        for(int i = root+1;i < in_len ; i++)
        {
            right_in.push_back(vin[i]);
            right_pre.push_back(pre[i]);
        }
        //�ݹ鴴����������
        head->left = reConstructBinaryTree(left_pre, left_in);
        head->right = reConstructBinaryTree(right_pre, right_in);
        //����ͷ���
        return head;
    }
    
};