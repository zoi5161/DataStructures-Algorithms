#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

typedef struct tagNode 
{
    char Eword[20];
    char Vmeaning[50]; 
    struct tagNode* pleft; 
    struct tagNode* pright;
}Node;
typedef Node* TREE;

Node* CreateNode(const char Eng[], const char Viet[])
{
    Node* tmp = new Node;
    strcpy(tmp -> Eword, Eng);
    strcpy(tmp -> Vmeaning, Viet);
    tmp -> pleft = NULL;
    tmp -> pright = NULL;
    return tmp;
}

bool Insert(Node* &p, const char Eng[], const char Viet[])
{
    if(p == NULL)
    {
        p = CreateNode(Eng, Viet);
        return true;
    }
    
    int cmp = strcmp(Eng, p -> Eword);
    if(cmp < 0)
        return Insert(p -> pleft, Eng, Viet);
    else if(cmp > 0)
        return Insert(p -> pright, Eng, Viet);
    return false;
}

Node* Search(Node* p, const char x[])
{
    if(p == NULL)
        return p;
    
    int cmp = strcmp(x, p -> Eword);
    if(cmp < 0)
        return Search(p -> pleft, x);
    else if(cmp > 0)
        return Search(p -> pright, x);
    return p;
}

Node* SearchStandFor(Node* &p, Node* &pCur)
{
    if(p -> pright != NULL)
        return SearchStandFor(p -> pright, pCur);
    
    strcpy(pCur -> Eword, p -> Eword);
    strcpy(pCur -> Vmeaning, p -> Vmeaning);

    Node* tmp = p;
    p = p -> pleft;
    return tmp;
}

bool Delete(Node* &p, const char x[])
{
    if(p == NULL)
        return false;
    
    int cmp = strcmp(x, p -> Eword);
    if(cmp < 0)
        return Delete(p -> pleft, x);
    else if(cmp > 0)
        return Delete(p -> pright, x);
    
    Node* tmp = p;
    if(p -> pright == NULL)
        p = p -> pleft;
    else if(p -> pleft == NULL)
        p = p -> pright;
    else
        tmp = SearchStandFor(p -> pleft, p);
    delete tmp;
    return true;
}

void Input(Node* &root)
{
    ifstream fin("dictionary.txt");
    if(fin.is_open())
    {
        string s;
        int i, j;
        char Eword[20];
        char Vmeaning[50];

        while(!fin.eof())
        {
            i = 0;
            j = 0;

            getline(fin, s);
            if(s == "")
                break;

            while(s[i] != ':')
                Eword[j++] = s[i++];
            Eword[i] = '\0';

            i += 2;
            j = 0;
            while(i < s.length())
                Vmeaning[j++] = s[i++];
            Vmeaning[j] = '\0';
            
            Insert(root, Eword, Vmeaning);
        }
        fin.close();
    }
    else
        cout << "Can't open file";
}

void Save(Node* root, ofstream& fout)
{
    if(root == NULL)
        return;

    fout << root -> Eword << ": " << root -> Vmeaning << endl;
    Save(root -> pleft, fout);
    Save(root -> pright, fout);
}

void Process()
{
    Node* root = NULL;
    string s;
    int i;

    Input(root);

    cout << "- - - - - - Dictionary - - - - - -" << endl;
    cout << "Your options: " << endl;
    cout << "1. Add a new word" << endl;
    cout << "2. Delete a word" << endl;
    cout << "3. Search a word" << endl;
    cout << "4. Exit" << endl << endl;

    while(true)
    {
        cout << "Enter your chosen: ";
        cin >> s;
        if(s == "1")
        {
            char E[20];
            char V[50];

            cout << "Enter a word in English which you want to add into dictionary (Ex: 'Bag'): ";
            cin.ignore();
            getline(cin, s);

            i = 0;
            for(; i < s.length(); i++)
                E[i] = tolower(s[i]);
            E[i] = '\0';

            cout << "Enter that word in Vietnamese (Ex: 'Cái cặp'): ";
            getline(cin, s);

            i = 0;
            for(; i < s.length(); i++)
                V[i] = tolower(s[i]);
            V[i] = '\0';

            if(Insert(root, E, V))
                cout << "Result: Add successfully" << endl << endl;
            else
            {
                E[0] = toupper(E[0]);
                cout << "Result: The word '" << E << "' existed in dictionary" << endl << endl;
            }
        }
        else if(s == "2")
        {
            char E[20];
            char V[50];

            cout << "Enter a word in English which you want to delete (Ex: 'Bag'): ";
            cin.ignore();
            getline(cin, s);

            i = 0;
            for(; i < s.length(); i++)
                E[i] = tolower(s[i]);
            E[i] = '\0';

            if(Delete(root, E))
                cout << "Result: Delete successfully" << endl << endl;
            else
            {
                E[0] = toupper(E[0]);
                cout << "Result: The word '" << E << "' doesn't exist in dictionary" << endl << endl;
            }
        }
        else if(s == "3")
        {
            char E[20];

            cout << "Enter a word in English which you want to search in dictionary (Ex: 'Bag'): ";
            cin.ignore();
            getline(cin, s);

            i = 0;
            for(; i < s.length(); i++)
                E[i] = tolower(s[i]);
            E[i] = '\0';

            Node* k = Search(root, E);
            if(k == NULL)
            {
                E[0] = toupper(E[0]);
                cout << "Result: The word '" << E << "' doesn't exist in dictionary" << endl << endl;
            }
            else
            {
                char tmpE[20];
                char tmpV[50];
                i = 1;

                tmpE[0] = toupper((k -> Eword)[0]);
                for(; i < strlen(k -> Eword); i++)
                    tmpE[i] = (k -> Eword)[i];
                tmpE[i] = '\0';

                i = 1;
                tmpV[0] = toupper((k -> Vmeaning)[0]);
                for(; i < strlen(k -> Vmeaning); i++)
                    tmpV[i] = (k -> Vmeaning)[i];
                tmpV[i] = '\0';

                cout << endl << ' ';
                for(int j = 0; j < (strlen(tmpE) + strlen(tmpV) + 1)/2; j++)
                    cout << "- ";
                cout << endl << "| " << tmpE << ": " << tmpV << " |" << endl;
                cout << ' ';
                for(int j = 0; j < (strlen(tmpE) + strlen(tmpV) + 1)/2; j++)
                    cout << "- ";
                cout << endl << endl;
            }
        }
        else if(s == "4")
            break;
        else
            cout << "Invalide option. Please enter again (1 -> 4)" << endl << endl;
    }

    ofstream fout("dictionary.txt");
    Save(root, fout);
}

int main()
{
    Process();
    return 0;
}