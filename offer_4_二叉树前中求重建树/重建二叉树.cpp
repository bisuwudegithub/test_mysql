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
        //得到二叉树的长度，并判空
        int in_len = vin.size();
        if(in_len == 0)
        {
            return NULL;
        }
        //创建子树，前序的左子树，前序的右子树，中序的前子树，中序的右子树
        vector<int> left_pre, right_pre, left_in, right_in;
        //创建头结点，是前序的第一个节点
        TreeNode* head = new TreeNode(pre[0]);
        //在中序遍历中找根节点，保存在中序遍历中第i位置
        int root = 0;
        for(int i = 0; i < in_len; i++)
        {
            if(vin[i] == pre[0])
            {
               root  = i;
               break;
            }
        }
        //中序遍历的左子树就是从0到root-1
        //前序遍历的左子树也是从1到root
         for(int i = 0;i < root ; i++)
        {
            left_in.push_back(vin[i]);
            left_pre.push_back(pre[i+1]);
        }
        //中序遍历的右子树就是从root+1到最后一位
        //前序遍历的右子树也是root+1到最后一位
        for(int i = root+1;i < in_len ; i++)
        {
            right_in.push_back(vin[i]);
            right_pre.push_back(pre[i]);
        }
        //递归创建左右子树
        head->left = reConstructBinaryTree(left_pre, left_in);
        head->right = reConstructBinaryTree(right_pre, right_in);
        //返回头结点
        return head;
    }
    
};