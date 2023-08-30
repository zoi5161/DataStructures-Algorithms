#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* Left;
    Node* Right;
    int height;
};

Node* CreateNode(int x)
{
    Node* tmp = new Node();
    tmp -> data = x;
    tmp -> Left = NULL;
    tmp -> Right = NULL;
    tmp -> height = 1;
    return tmp;
}

int Height(Node* p)
{
    if (p == NULL)
        return 0;
    return p -> height;
}

int GetBalance(Node* p)
{
    if (p == NULL)
        return 0;
    return Height(p -> Left) - Height(p -> Right);
}

Node* SingleRotateRight(Node* p)
{
    Node* x = p -> Left;
    Node* y = x -> Right;

    x -> Right = p;
    p -> Left = y;

    x -> height = max(Height(x -> Left), Height(x -> Right)) + 1;
    y -> height = max(Height(y -> Left), Height(y -> Right)) + 1;

    return x;
}

Node* SingleRotateLeft(Node* p)
{
    Node* x = p -> Right;
    Node* y = x -> Left;

    x -> Left = p;
    p -> Right = y;

    x -> height = max(Height(x -> Left), Height(x -> Right)) + 1;
    y -> height = max(Height(y -> Left), Height(y -> Right)) + 1;

    return x;
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

Node* Insert(Node* root, int x)
{
    if (root == NULL)
    {
        root = CreateNode(x);
        return root;
    }

    if (x < root -> data)
        root -> Left = Insert(root -> Left, x);
    else if (x > root -> data)
        root -> Right = Insert(root -> Right, x);
    else
        return root;

    root -> height = 1 + max(Height(root -> Left), Height(root -> Right));

    int balance = GetBalance(root);

    if (balance > 1 && root -> Left -> data > x)
        return SingleRotateRight(root);

    if (balance < -1 && root -> Right -> data < x)
        return SingleRotateLeft(root);

    if (balance > 1 && root -> Left -> data < x)
        return DoubleRotateRight(root);

    if (balance < -1 && root -> Right -> data > x)
        return DoubleRotateLeft(root);

    return root;
}

Node* FindLCA(Node* root, int key1, int key2)
{
    if (root == NULL)
        return NULL;

    if (key1 < root -> data && key2 < root -> data)
        return FindLCA(root -> Left, key1, key2);

    if (key1 > root -> data && key2 > root -> data)
        return FindLCA(root -> Right, key1, key2);

    return root;
}

int main()
{
    Node* root = NULL;
    int n, x;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements: ";
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        root = Insert(root, x);
    }

    int key1, key2;
    cout << "Enter two keys to find their least common ancestor: ";
    cin >> key1 >> key2;

    Node* lca = FindLCA(root, key1, key2);

    if (lca != NULL)
        cout << "The least common ancestor of " << key1 << " and " << key2 << " is: " << lca -> data << endl;
    else
        cout << "One or both keys not found in the AVL tree." << endl;

    return 0;
}