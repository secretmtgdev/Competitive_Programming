#include <iostream>
#include <stack>
#include <map>

using namespace std;

////////////////////
// TEST FUNCTIONS //
////////////////////
void testSortedStack();

///////////////////////////
// FUNCTION DECLARATIONS //
///////////////////////////
void sortStack(stack<int> *);
void evaluateExpression(string);

//////////////////////
// HELPER FUNCTIONS //
//////////////////////
void printStack(stack<int>);
int handleOp(char, stack<int> *);

int main()
{
    evaluateExpression("2-6-7*8/2+5");
    //testSortedStack();
}

//////////////////////////////
// FUNCTION IMPLEMENTATIONS //
//////////////////////////////
enum opPriority
{
    SUBTRACT = 0,
    ADD = 0,
    MULTIPLY = 1,
    DIVISION = 1
};

void evaluateExpression(string s)
{
    map<char, int> priorities;
    priorities['*'] = 1;
    priorities['/'] = 1;
    priorities['+'] = 0;
    priorities['-'] = 0;
    stack<int> nums;
    stack<char> ops;
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        if (isdigit(c))
        {
            nums.push(c - '0');
        }
        else
        {
            if (ops.empty())
            {
                ops.push(c);
            }
            else
            {
                char op = ops.top();
                auto opStack = priorities.find(op);
                auto currOp = priorities.find(c);
                //printf("first: %c => %d, second: %c => %d\n", opStack->first, opStack->second, currOp->first, currOp->second);
                while (!ops.empty() && currOp->second <= opStack->second)
                {
                    nums.push(handleOp(op, &nums));

                    ops.pop();
                    op = ops.top();
                    opStack = priorities.find(op);
                }
                ops.push(c);
            }
        }
    }
    while (nums.size() > 1 && !ops.empty())
    {
        printStack(nums);
        char op = ops.top();
        ops.pop();
        nums.push(handleOp(op, &nums));
    }
    cout << "Value: " << nums.top() << endl;
}

void sortStack(stack<int> *st)
{
    stack<int> secondaryStack;
    while (!st->empty())
    {
        int top = st->top();
        st->pop();
        while (!secondaryStack.empty() && secondaryStack.top() > top)
        {
            st->push(secondaryStack.top());
            secondaryStack.pop();
        }
        secondaryStack.push(top);
    }
    while (!secondaryStack.empty())
    {
        st->push(secondaryStack.top());
        secondaryStack.pop();
    }
}

void printStack(stack<int> st)
{
    stack<int> secondaryStack;
    cout << "[";
    while (!st.empty())
    {
        int value = st.top();
        st.pop();
        secondaryStack.push(value);
        cout << value << " ";
    }
    while (!secondaryStack.empty())
    {
        int top = secondaryStack.top();
        secondaryStack.pop();
        st.push(top);
    }
    cout << "]" << endl;
}

void testSortedStack()
{
    stack<int> testStackOne;
    for (auto &value : {5, 1, 3, 4, 2})
    {
        testStackOne.push(value);
    }
    printStack(testStackOne);
    sortStack(&testStackOne);
    printStack(testStackOne);
}

int handleOp(char op, stack<int> *nums)
{
    int y = nums->top();
    nums->pop();
    int x = nums->top();
    int res;
    nums->pop();
    switch (op)
    {
    case '+':
        res = x + y;
        break;
    case '-':
        res = x - y;
        break;
    case '*':
        res = x * y;
        break;
    default:
        res = x / y;
    }
    return res;
}