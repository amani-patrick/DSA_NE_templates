#include <iostream>
using namespace std;

#Graphs
const int MAX = 100;

int graph[MAX][MAX] = {0};

##Adding edges 
graph[i][j] = 1;
graph[j][i] = 1;

##Dispalying the graph 
for(int i = 0; i < n; i++)
{
    for(int j = 0; j < n; j++)
    {
        cout << graph[i][j] << " ";
    }

    cout << endl;
}

#Stack  ()Using arrays)
const int MAX = 5;

int stackArr[MAX];
int top = -1;

// PUSH
void push(int value)
{
    if(top == MAX - 1)
    {
        cout << "Stack Overflow\n";
        return;
    }

    top++;
    stackArr[top] = value;

    cout << value << " pushed successfully\n";
}

// POP
void pop()
{
    if(top == -1)
    {
        cout << "Stack Underflow\n";
        return;
    }

    cout << stackArr[top]
         << " popped successfully\n";

    top--;
}

// PEEK
void peek()
{
    if(top == -1)
    {
        cout << "Stack is empty\n";
        return;
    }

    cout << "Top element: "
         << stackArr[top] << endl;
}

// DISPLAY
void display()
{
    if(top == -1)
    {
        cout << "Stack is empty\n";
        return;
    }

    cout << "Stack elements:\n";

    for(int i = top; i >= 0; i--)
    {
        cout << stackArr[i] << endl;
    }
}