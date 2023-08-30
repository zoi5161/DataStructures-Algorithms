#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* pNext;
};

int Hash(int x, int n)
{
    return x%n;
}

void InsertHash(Node* a[], int n, int x)
{
    int index = Hash(x, n);
    if(a[index] == nullptr)
    {
        Node* p = new Node;
        p -> data = x;
        p -> pNext = nullptr;
        a[index] = p;
        return;
    }

    Node* p = a[index];
    while(p -> pNext != nullptr)
        p = p -> pNext;
    p -> pNext = new Node;
    p = p -> pNext;
    p -> data = x;
    p -> pNext = nullptr;
}

void PrintHash(Node* a[], int n)
{
    Node* p;
    for(int i = 0; i < n; i++)
    {
        p = a[i];
        cout << i << ": ";
        while(p != NULL)
        {
            cout << p -> data << ' ';
            p = p -> pNext;
        }
        cout << endl;
    }
}

// delete
int main()
{
    int n, x;
    cin >> n;

    Node* a[n];
    for (int i = 0; i < n; i++)
        a[i] = nullptr;

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        InsertHash(a, n, x);
    }

    PrintHash(a, n);
    return 0;
}