#include <iostream>
using namespace std;

#Queue
##Queue using arrrays

const int MAX = 5;

int queueArr[MAX];

int front = 0;
int rear = -1;

// ENQUEUE
void enqueue(int value)
{
	//check if queue is full 
    if(rear == MAX - 1)
    {
        cout << "Queue Overflow\n";
        return;
    }

    rear++;

    queueArr[rear] = value;

    cout << value << " inserted\n";
}

// DEQUEUE
void dequeue()
{
    if(front > rear)
    {
    	//check if its empty
        cout << "Queue Underflow\n";
        return;
    }

    cout << queueArr[front]
         << " removed\n";

    front++;
}

// DISPLAY
void display()
{
    if(front > rear)
    {
        cout << "Queue is empty\n";
        return;
    }

    cout << "Queue elements:\n";

    for(int i = front; i <= rear; i++)
    {
        cout << queueArr[i] << endl;
    }
}

#Binary Search Tree
##Constructing it (using linked lists)
struct Node
{
    int data;

    Node* left;
    Node* right;
};

Node* insert(Node* root, int value)
{
    if(root == NULL)
    {
        Node* newNode = new Node();

        newNode->data = value;

        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if(value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else
    {
        root->right = insert(root->right, value);
    }

    return root;
}

## Inorder Traversal
void inorder(Node* root)
{
    if(root != NULL)
    {
        inorder(root->left);

        cout << root->data << " ";

        inorder(root->right);
    }
}

#Burble sort
void bubbleSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
#Selection sort
void selectionSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for(int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}
#Insertion sort
void insertionSort(int arr[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int key = arr[i];

        int j = i - 1;

        while(j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];

            j--;
        }

        arr[j + 1] = key;
    }
}
#Linear search
int linearSearch(int arr[], int n, int target)
{
    for(int i = 0; i < n; i++)
    {
        if(arr[i] == target)
        {
            return i;
        }
    }

    return -1;
}
#BST implementation using arrays
int binarySearch(int arr[], int n, int target)
{
    int left = 0;
    int right = n - 1;

    while(left <= right)
    {
        int mid = (left + right) / 2;

        if(arr[mid] == target)
        {
            return mid;
        }

        if(arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}