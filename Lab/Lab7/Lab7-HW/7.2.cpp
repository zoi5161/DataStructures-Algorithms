#include <iostream>
#include <fstream>

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

Node* Insert(Node* root, int x)
{
    if(root == NULL)
    {
        root = CreateNode(x);
        return root;
    }

    if(root -> data > x)
        root -> Left = Insert(root -> Left, x);
    else if(root -> data < x)
        root -> Right = Insert(root -> Right, x);

    root -> height = 1 + max(Height(root -> Left), Height(root -> Right));
    
    return root;
}

bool IsAVLTree(Node* root)
{
    if(root == NULL)
        return true;
    
    int balance = GetBalance(root);
    if(balance > 1 || balance < -1)
        return false;
    return IsAVLTree(root -> Left) && IsAVLTree(root -> Right);
}

void NLR(Node* root)
{
    if(root == NULL)
        return;
    cout << root -> data << ' ';
    NLR(root -> Left);
    NLR(root -> Right);
}

int main()
{
    ifstream fin("Input.txt");
    ofstream fout("Output.txt");

    if(fin.is_open())
    {
        string s, k;
        int n;

        getline(fin, s);

        while(!fin.eof())
        {
            getline(fin, s);

            k = "";
            n = 0;
            Node* root = NULL;

            for(int i = 0; i < s.length(); i++)
            {
                if(s[i] == ' ')
                {
                    root = Insert(root, stoi(k));
                    k = "";
                    n++;
                }
                else
                    k += s[i];
            }
            Insert(root, stoi(k));
            k = "";
            n++;

            if(IsAVLTree(root))
                fout << "Yes";
            else
                fout << "No";
            
            if(!fin.eof())
                fout << endl;
        }
        fin.close();
    }
    else
        cout << "Can't open file";
    return 0;
}