#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* Left;
    Node* Right;
    int height;
    int depth;
};

Node* CreateNode(int x)
{
    Node* tmp = new Node();
    tmp -> data = x;
    tmp -> Left = NULL;
    tmp -> Right = NULL;
    tmp -> height = 1;
    tmp -> depth = 1;
    return tmp;
}

int Height(Node* p)
{
    if(p == NULL)
        return 0;
    return p -> height;
}

int GetBalance(Node* p)
{
    if(p == NULL)
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

Node* Insert(Node* root, int x, int d)
{
    if(root == NULL)
    {
        root = CreateNode(x);
        root -> depth = d;
        return root;
    }

    if(x < root -> data)
        root -> Left = Insert(root -> Left, x, d + 1);
    else if(x > root -> data)
        root -> Right = Insert(root -> Right, x, d + 1);
    else
        return root;

    root -> height = 1 + max(Height(root -> Left), Height(root -> Right));

    int balance = GetBalance(root);

    if(balance > 1 && root -> Left -> data > x)
        return SingleRotateRight(root);

    if(balance < -1 && root -> Right -> data < x)
        return SingleRotateLeft(root);

    if(balance > 1 && root -> Left -> data < x)
        return DoubleRotateRight(root);

    if(balance < -1 && root -> Right -> data > x)
        return DoubleRotateLeft(root);

    return root;
}

void Check(Node* p, int &org, bool &same)
{
    if(p == NULL)
        return;

    if(p -> Left == NULL && p -> Right == NULL)
    {
        if(org == -1)
            org = p -> depth;
        else if(org != p -> depth)
            same = false;
    }

    Check(p -> Left, org, same);
    Check(p -> Right, org, same);
}

int main()
{
    Node* root = NULL;
    int org = -1;
    bool same = true;

    root = Insert(root, 10, 1);
    root = Insert(root, 5, 1);
    root = Insert(root, 15, 1);
    root = Insert(root, 3, 1);
    root = Insert(root, 16, 1);

    Check(root, org, same);
    if(same)
        cout << "All leaves have the same depth in the AVL tree." << endl;
    else 
        cout << "All leaves don't have the same depth in the AVL tree." << endl;
    return 0;
}