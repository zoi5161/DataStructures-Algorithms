#include <iostream>
#include <fstream>
#include <chrono>
#include <queue>

using namespace std;

typedef chrono::milliseconds MSEC;
typedef chrono::high_resolution_clock HRC;

struct Node 
{
    string data;
    Node* Left;
    Node* Right;
    int height;

    Node(const string& value) : data(value), Left(nullptr), Right(nullptr), height(1) {}
};

int Height(Node* node) 
{
    if (node == nullptr) 
        return 0;
    return node -> height;
}

int getBalance(Node* node) 
{
    if (node == nullptr) 
        return 0;
    return Height(node -> Left) - Height(node -> Right);
}

Node* SingleRotateRight(Node* y) 
{
    Node* x = y -> Left;
    Node* T2 = x -> Right;

    x -> Right = y;
    y -> Left = T2;

    y -> height = 1 + max(Height(y -> Left), Height(y -> Right));
    x -> height = 1 + max(Height(x -> Left), Height(x -> Right));

    return x;
}

Node* SingleRotateLeft(Node* x) 
{
    Node* y = x -> Right;
    Node* T2 = y -> Left;

    y -> Left = x;
    x -> Right = T2;

    x -> height = 1 + max(Height(x -> Left), Height(x -> Right));
    y -> height = 1 + max(Height(y -> Left), Height(y -> Right));

    return y;
}

Node* DoubleRotateLeft(Node* root)
{
    root -> Right = SingleRotateRight(root -> Right);
    return SingleRotateLeft(root);
}

Node* DoubleRotateRight(Node* root)
{
    root -> Left = SingleRotateLeft(root -> Left);
    return SingleRotateRight(root);
}

Node* InsertAVL(Node* root, const string& value) 
{
    if (root == nullptr)
        return new Node(value);

    if (value < root -> data)
        root -> Left = InsertAVL(root -> Left, value);
    else if (value > root -> data)
        root -> Right = InsertAVL(root -> Right, value);
    else
        return root;

    root -> height = 1 + max(Height(root -> Left), Height(root -> Right));

    int balance = getBalance(root);

    if(balance > 1 && root -> Left -> data > value)
        return SingleRotateRight(root);

    if(balance < -1 && root -> Right -> data < value)
        return SingleRotateLeft(root);

    if(balance > 1 && root -> Left -> data < value)
        return DoubleRotateRight(root);

    if(balance < -1 && root -> Right -> data > value)
        return DoubleRotateLeft(root);

    return root;
}

Node* InsertBINTree(Node* root, const string& value)
{
    if (root == NULL) 
        return new Node(value);

    queue<Node*> q;
    q.push(root);
 
    while (!q.empty()) 
    {
        Node* temp = q.front();
        q.pop();
 
        if (temp -> Left != NULL)
            q.push(temp -> Left);
        else 
        {
            temp -> Left = new Node(value);
            return root;
        }
 
        if (temp -> Right != NULL)
            q.push(temp -> Right);
        else 
        {
            temp -> Right = new Node(value);
            return root;
        }
    }
}

bool SearchBINTree(Node* root, const string& value)
{
    if (root == NULL)
        return false;

    if (root -> data == value)
        return true;

    return SearchBINTree(root -> Left, value) || SearchBINTree(root -> Right, value);
}


bool SearchAVLTree(Node* root, const string& value)
{
    if(root == NULL)
        return false;
    
    if(root -> data > value)
        return SearchAVLTree(root -> Left, value);
    else if(root -> data < value)
        return SearchAVLTree(root -> Right, value);
    return true;
}

void Input(string a[], int &n, Node* &avl, Node* &bin)
{
    ifstream fin("names.txt");
    if(fin.is_open())
    {
        n = 0;

        while(!fin.eof())
        {
            fin >> a[n++];
            avl = InsertAVL(avl, a[n-1]);
            bin = InsertBINTree(bin, a[n-1]);
        }
        fin.close();
    }
    else
        cout << "Can't open file";
}

int main()
{
    Node* avl = NULL;
    Node* bin = NULL;
    string name[18500];
    int n;
    
    Input(name, n, avl, bin);

    cout << "Binary Tree: ";
    auto start = HRC::now();

    for(int i = 0; i < n; i++)
        SearchBINTree(bin, name[i]);

    auto end = HRC::now();
    auto time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl;

    cout << "AVL Tree: ";
    start = HRC::now();

    for(int i = 0; i < n; i++)
        SearchAVLTree(avl, name[i]);

    end = HRC::now();
    time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl;
    return 0;
}