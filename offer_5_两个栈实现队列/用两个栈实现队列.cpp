class Solution
{
    //ջ���Ƚ����
    //���У��Ƚ��ȳ�
    //stack1������push���У�stack2������pop����
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
         if(stack2.empty()){
            while(!stack1.empty()){
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int t=stack2.top();
        stack2.pop();
        return t;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};