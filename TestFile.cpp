#include <iostream>
#include <stack>

using namespace std;

int main()
{
	stack<char> myStack;

	myStack.push('(');
    //This will place ( in the stack
	myStack.push('[');
    //This will place [ in the stack
    //Because it is the 2nd item to be added, it will be "on top of" (
	myStack.push('{');
    //This will place { in the stack
    //Because it is the 3rd item to be added, it will be "on top of" [
    
    char Test = myStack.top();
    //For some reason, .peak() doesn't work. However, .top() works as a replacement
    //Returning the value from the top of the stack without removing it

	cout << "Number of char(s on the stack " << myStack.size() << endl;
	cout << "The current char on top is " << Test << endl;

	while(!myStack.empty())
	{
		cout << "popping " << myStack.top() << endl;
		myStack.pop();
        //.pop() will remove the top item from the stack
	}

	cout << "Number of chars on the stack " << myStack.size() << endl;
}
