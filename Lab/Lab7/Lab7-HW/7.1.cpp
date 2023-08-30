#include <iostream>

using namespace std;

// Create data structure for AVL Tree
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

// Initialize empty tree
Node* Initialize()
{
    return NULL;
}

// Calculate tree height.
int Height(Node* p)
{
    if(p == NULL)
        return 0;
    return p -> height;
}

// Insert some value to tree
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

Node* Insert(Node* root, int x)
{
    if(root == NULL)
    {
        root = CreateNode(x);
        return root;
    }

    if(x < root -> data)
        root -> Left = Insert(root -> Left, x);
    else if(x > root -> data)
        root -> Right = Insert(root -> Right, x);
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

// Delete some value from the tree
Node* GetMin(Node* p)
{
    if(p == NULL)
        return NULL;
    while(p -> Left != NULL)
        p = p -> Left;
    return p;
}

Node* Remove(Node* root, int x)
{
    if (root == NULL)
        return NULL;

    if (x < root->data)
        root->Left = Remove(root->Left, x);
    else if (x > root->data)
        root->Right = Remove(root->Right, x);
    else
    {
        if (root->Left == NULL || root->Right == NULL)
        {
            Node* tmp = root->Left ? root->Left : root->Right;
            delete root;
            root = tmp;
        }
        else
        {
            Node* tmp = GetMin(root->Right);
            root->data = tmp->data;
            root->Right = Remove(root->Right, tmp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(Height(root->Left), Height(root->Right));

    int balance = GetBalance(root);

    if (balance > 1 && GetBalance(root->Left) >= 0)
        return SingleRotateRight(root);

    if (balance > 1 && GetBalance(root->Left) < 0)
        return DoubleRotateRight(root);

    if (balance < -1 && GetBalance(root->Right) <= 0)
        return SingleRotateLeft(root);

    if (balance < -1 && GetBalance(root->Right) > 0)
        return DoubleRotateLeft(root);

    return root;
}

// Identify whether a given value exists in the tree
bool Search(Node* root, int x)
{
    if(root == NULL)
        return false;
    
    if(root -> data > x)
        return Search(root -> Left, x);
    else if(root -> data < x)
        return Search(root -> Right, x);
    return true;
}

// Print tree to console screen in pre-order, in-order, post-order
void PreOrder(Node* p)
{
    if(p == NULL)
        return;
    cout << p -> data << ' ';
    PreOrder(p -> Left);
    PreOrder(p -> Right);
}

void InOrder(Node* p)
{
    if(p == NULL)
        return;
    InOrder(p -> Left);
    cout << p -> data << ' ';
    InOrder(p -> Right);
}

void PostOrder(Node* p)
{
    if(p == NULL)
        return;
    PostOrder(p -> Left);
    PostOrder(p -> Right);
    cout << p -> data << ' ';
}

int main()
{
    Node* root = Initialize();

    // Insert some values
    root = Insert(root, 10);
    root = Insert(root, 5);
    root = Insert(root, 20);
    root = Insert(root, 15);
    root = Insert(root, 30);
    root = Insert(root, 25);

    // Print the tree in pre-order, in-order, and post-order
    cout << "Pre-order: ";
    PreOrder(root);
    cout << endl;

    cout << "In-order: ";
    InOrder(root);
    cout << endl;

    cout << "Post-order: ";
    PostOrder(root);
    cout << endl;

    // Check if a value exists in the tree
    int valueToFind;

    cout << endl << "Enter a value you want to search: ";
    cin >> valueToFind;

    if (Search(root, valueToFind))
        cout << valueToFind << " exists in the tree." << endl;
    else
        cout << valueToFind << " does not exist in the tree." << endl;

    // Delete a value from the tree
    int valueToDelete;

    cout << endl << "Enter a value you want to delete: ";
    cin >> valueToDelete;
    root = Remove(root, valueToDelete);

    // Print the tree in-order after deletion
    cout << "Pre-order after deleting " << valueToDelete << ": ";
    PreOrder(root);
    cout << endl;

    // Get the height of the tree
    cout << "Tree height: " << Height(root) << endl;

    return 0;
}