#include <iostream>

using namespace std;

// Suport function
struct Node
{
    int key;
    Node* left;
    Node* right;
};

Node* CreateNode(int x)
{
    Node* tmp = new Node;
    tmp -> key = x;
    tmp -> left = NULL;
    tmp -> right = NULL;
    return tmp;
}

bool Insert(Node* &p, int x)
{
    if(p == NULL)
    {
        p = CreateNode(x);
        return true;
    }

    if(p -> key > x)
        return Insert(p -> left, x);
    else if(p -> key < x)
        return Insert(p -> right, x);
    return false;
}

void Init(Node* &p)
{
    Insert(p, 7);
    Insert(p, 3);
    Insert(p, 2);
    Insert(p, 4);
    Insert(p, 8);
    Insert(p , 9);
    Insert(p, 10);
}

// Question a
void LNR(Node* p)
{
    if(p == NULL)
        return;

    LNR(p -> left);
    cout << p -> key << ' ';
    LNR(p -> right);
}

void LRN(Node* p)
{
    if(p == NULL)
        return;

    LRN(p -> left);
    LRN(p -> right);
    cout << p -> key << ' ';
}

void NLR(Node* p)
{
    if(p == NULL)
        return;

    cout << p -> key << ' ';
    NLR(p -> left);
    NLR(p -> right);
}

void NRL(Node* p)
{
    if(p == NULL)
        return;

    cout << p -> key << ' ';
    NRL(p -> right);
    NRL(p -> left);
}

void RNL(Node* p)
{
    if(p == NULL)
        return;

    RNL(p -> right);
    cout << p -> key << ' ';
    RNL(p -> left);
}

void RLN(Node* p)
{
    if(p == NULL)
        return;

    RLN(p -> right);
    RLN(p -> left);
    cout << p -> key << ' ';
}

void Print(Node* root)
{
    cout << "LNR: ";
    LNR(root);
    cout << endl; 

    cout << "LRN: ";
    LRN(root);
    cout << endl; 

    cout << "NLR: ";
    NLR(root);
    cout << endl; 

    cout << "NRL: ";
    NRL(root);
    cout << endl; 

    cout << "RNL: ";
    RNL(root);
    cout << endl; 

    cout << "RLN: ";
    RLN(root);
    cout << endl << endl; 
}

// Question b
bool Search(Node* p, int x)
{
    if(p == NULL)
        return false;
    
    if(p -> key > x)
        return Search(p -> left, x);
    else if(p -> key < x)
        return Search(p -> right, x);
    return true;
}

// Question c
Node* SearchStandFor(Node* &p, Node* &pCur)
{
    if(p -> right != NULL)
        return SearchStandFor(p -> right, pCur);
    
    pCur -> key = p -> key;
    Node* tmp = p;
    p = p -> left;
    return tmp;
}

bool Delete(Node* &p, int x)
{
    if(p == NULL)
        return false;
    
    if(p -> key > x)
        return Delete(p -> left, x);
    else if(p -> key < x)
        return Delete(p -> right, x);
    
    Node* tmp = p;
    if(p -> right == NULL)
        p = p -> left;
    else if(p -> left == NULL)
        p = p -> right;
    else
        tmp = SearchStandFor(p -> left, p);
    delete tmp;
    return true;
}

// Question d
void CountNode(Node* p, int &cnt)
{
    if(p == NULL)
        return;
    cnt++;
    CountNode(p -> left, cnt);
    CountNode(p -> right, cnt);
}

// Question e
void CountNode2Child(Node* p, int &cnt)
{
    if(p == NULL)
        return;
    if(p -> left != NULL && p -> right != NULL)
        cnt++;
    CountNode2Child(p -> left, cnt);
    CountNode2Child(p -> right, cnt);
}

// Question f
void CountLeafNode(Node* p, int &cnt)
{
    if(p == NULL)
        return;
    if(p -> left == NULL && p -> right == NULL)
        cnt++;
    CountLeafNode(p -> left, cnt);
    CountLeafNode(p -> right, cnt);
}

int main()
{
    Node* root = NULL;

    // Initialize
    Init(root);

    // Question a: Print
    cout << "Tree: " << endl;
    cout << "        7           " << endl;
    cout << "    3       8       " << endl;
    cout << "  2   4        9    " << endl;
    cout << "                  10" << endl << endl;

    Print(root);

    // Question b: Search
    int x;
    cout << "Enter a number that you want to search: ";
    cin >> x;

    if(Search(root, x))
        cout << "Result: " << x << " existed" << endl << endl;
    else
        cout << "Result: " << x << " doesn't exist" << endl << endl;

    // Question c: Delete
    cout << "Enter a number that you want to delete: ";
    cin >> x;

    if(Delete(root, x))
    {
        cout << "After delete " << x << ":" << endl << endl;
        Print(root);
    }
    else
        cout << "Result: Not found " << x << endl << endl;
    
    // Question d: Count node
    x = 0;
    CountNode(root, x);
    cout << "The number of node: " << x << endl << endl;

    // Question e: Count node that has two childs
    x = 0;
    CountNode2Child(root, x);
    cout << "The number of node that has two children: " << x << endl << endl;

    // Question f: Count leaf node 
    x = 0;
    CountLeafNode(root, x);
    cout << "The number of leaves node: " << x << endl << endl;
    return 0;
}

/*
        7           
    3       8       
  2   4        9    
                  10

*/