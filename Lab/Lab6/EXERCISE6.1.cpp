#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Node 
{
    string data;
    vector<Node*> children;
    Node(string val) : data(val) {}
};

void AddChild(Node* &parent, Node* &child) 
{
    parent -> children.push_back(child);
}

void NLR(Node* root) 
{
    if (!root) return;

    cout << root -> data << " ";

    for (size_t i = 0; i < root -> children.size(); ++i)
        NLR(root -> children[i]);
}

void LNR(Node* root) 
{
    if (!root) return;

    if (!root -> children.empty())
        LNR(root -> children.front());

    cout << root -> data << " ";

    for (size_t i = 1; i < root->children.size(); ++i)
        LNR(root -> children[i]);
}

void LRN(Node* root) 
{
    if (!root) return;

    for (size_t i = 0; i < root -> children.size(); ++i)
        LRN(root -> children[i]);

    cout << root -> data << " ";
}

void Init(Node* &root) 
{
        ifstream fin("input.txt");

        if (fin.is_open()) 
        {
            string s, k = "";
            int n, j;
            bool flag = false;

            getline(fin, s);
            n = stoi(s);

            vector<Node*> nodes;

            while (!fin.eof()) 
            {
                getline(fin, s);
                j = 1;

                while (s[j] != ' ')
                    k += s[j++];

                Node* parent = nullptr;
                for (size_t i = 0; i < nodes.size(); ++i) 
                {
                    if (nodes[i] -> data == k) 
                    {
                        parent = nodes[i];
                        break;
                    }
                }

                if (!parent) 
                {
                    parent = new Node(k);
                    nodes.push_back(parent);
                    if (!flag) 
                    {
                        root = parent;
                        flag = true;
                    }
                }
                k = "";

                for (int i = j + 1; i < s.length(); i++) 
                {
                    if (s[i] == ' ' || s[i] == ')') 
                    {
                        if (!k.empty()) 
                        {
                            Node* child = new Node(k);
                            AddChild(parent, child);
                            nodes.push_back(child);
                            k = "";
                        }
                        if (s[i] == ')')
                            break;
                    }
                    if (s[i] != '(' && s[i] != ' ')
                        k += s[i];
                }
            }

        fin.close();
    }
    else
        cout << "Can't open file";
}

int main() 
{
    Node* root;
    Init(root);

    cout << "PreOrder (NLR): ";
    NLR(root);
    cout << endl << endl;

    cout << "InOrder (LNR): ";
    LNR(root);
    cout << endl << endl;

    cout << "PostOrder (LRN): ";
    LRN(root);
    cout << endl << endl;
    return 0;
}