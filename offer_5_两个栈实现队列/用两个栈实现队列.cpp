class Solution
{
    //栈，先进后出
    //队列，先进先出
    //stack1用来入push队列，stack2用来出pop队列
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