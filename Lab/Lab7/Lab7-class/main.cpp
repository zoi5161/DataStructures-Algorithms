#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Node
{
    string data;
    Node* left;
    Node* right;
    int height;

    Node(const string& value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

int Height(Node* p)
{
    if(p == NULL)
        return 0;
    return p -> height;
}

void MakeTree(Node* &p, ifstream &fin, int &n)
{
    string s;
    getline(fin, s);

    if (s.empty())
        return;

    bool Ques = s[1] == 'Q';
    p = new Node(s);
    n++;

    if (Ques)
    {
        MakeTree(p -> left, fin, n);
        MakeTree(p -> right, fin, n);
    }
}

void Input(Node* &root, string s, int &n)
{
    ifstream fin(s + ".txt");
    if (!fin)
    {
        cout << "Can't open file";
        return;
    }
    MakeTree(root, fin, n);

    fin.close();
}

void Save(Node* p, ofstream& fout, bool isFirst = true)
{
    if (p == nullptr)
        return;

    if (!isFirst)
        fout << '\n';

    fout << p -> data;

    Save(p -> left, fout, false);
    Save(p -> right, fout, false);
}

void Game(Node* p, Node* pPre, string was[], int &i, bool &yes, bool English)
{
    string s;
    bool Ques;

    if(p == NULL)
    {
        if(yes)
        {
            if(English)
                cout << "YAY! I guessed your animal!" << endl << endl;
            else 
                cout << "Yeah! Tôi đã đoán đúng con vật của bạn!" << endl << endl;
            return;
        }
        else
        {
            if(English)
            {
                cout << "BOO! I don't know!" << endl << endl;
                cout << "Would you like to expand the game tree (y/n)?: ";
            }
            else
            {
                cout << "Oh no! Tôi chịu thua" << endl << endl;
                cout << "Bạn có muốn mở rộng cho con vật này cho trò chơi (y/n)?: ";
            }

            string k;
            bool ok = false;

            while(1)
            {
                cin >> k;
                cin.ignore();
                if(k == "y" || k == "Y")
                {
                    if(pPre == NULL)
                    {
                        if(English)
                        {
                            cout << endl << "Enter a new animal in the form of a question," << endl;
                            cout << "e.g., Ex 'Is it a whale?': ";
                        }
                        else
                        {
                            cout << endl << "Nhập một con vật mới dưới dạng một câu hỏi," << endl;
                            cout << "e.g., Ví dụ 'Nó là con cá voi phải không?': ";
                        }

                        string tmp1, tmp2, newA = "#A ", newQ = "#Q ";
                        getline(cin, tmp1);
                        newA += tmp1;
                        
                        if(English)
                        {
                            cout << endl << "Now enter a question for which the answer is 'yes' for your new animal," << endl;
                            cout << "a question about the animal's distinctive identity, Example 'Does it have stripes?': ";
                        }
                        else
                        {
                            cout << endl << "Bây giờ hãy nhập một câu hỏi mà câu trả lời là 'có' cho" << endl;
                            cout << "câu hỏi về đặc điểm nhận dạng riêng biệt con vật đó, Ví dụ 'Nó có sọc không?': ";
                        }
                        
                        getline(cin, tmp2);
                        newQ += tmp2;

                        p = new Node(newQ);
                        p -> left = new Node(newA);
                        return;
                    }
                    else
                    {
                        if(English)
                            cout << endl << "I asked the following:" << endl;
                        else
                            cout << endl << "Tôi sẽ hỏi như sau:" << endl;

                        for(int j = 0; j < i-1; j++)
                            cout << was[j] << endl;

                        if(English)
                        {
                            cout << endl << "Enter a new animal in the form of a question," << endl;
                            cout << "e.g., Ex 'Is it a whale?': ";
                        }
                        else
                        {
                            cout << endl << "Nhập một con vật mới dưới dạng một câu hỏi," << endl;
                            cout << "e.g., Ví dụ 'Nó là con cá voi phải không?': ";
                        }

                        string newA = "#A ", newQ = "#Q ", s, tmp = pPre -> data;
                        getline(cin, s);

                        newA += s;
                        
                        if(English)
                        {
                            cout << endl << "Now enter a question for which the answer is 'yes' for your new animal," << endl;
                            cout << "a question about the animal's distinctive identity, Example 'Does it have stripes?': ";
                        }
                        else
                        {
                            cout << endl << "Bây giờ hãy nhập một câu hỏi mà câu trả lời là 'có' cho" << endl;
                            cout << "câu hỏi về đặc điểm nhận dạng riêng biệt con vật đó, Ví dụ 'Nó có sọc không?': ";
                        }

                        getline(cin, s);
                        newQ += s;

                        pPre -> data =  newQ;
                        pPre -> left = new Node(newA);
                        pPre -> right = new Node(tmp);
                        return;
                    }
                }
                else if(k == "n" || k == "N")
                    return;
                else
                {
                    if(English)
                        cout << "Please enter y/Y or n/N: ";
                    else
                        cout << "Làm ơn nhập y/Y hoặc n/N: ";
                }
            }
        }
    }

    string v = p -> data;
    cout << "-";
    for(int i = 2; i < v.length(); i++)
        cout << v[i];
    cout << " (y/n): ";

    while(1)
    {
        cin >> s;
        if(s == "y" || s == "Y")
        {
            was[i++] = p -> data;
            if(English)
                was[i-1] += " Yes";
            else
            {
                if(was[i-1][1] == 'Q')
                    was[i-1] += " Có";
                else
                    was[i-1] += " Phải";
            }
            yes = true;
            Game(p -> left, p, was, i, yes, English);
            break;
        }
        else if(s == "n" || s == "N")
        {
            was[i++] = p -> data;
            if(English)
                was[i-1] += " No";
            else
                was[i-1] += " Không";
            yes = false;
            Game(p -> right, p, was, i, yes, English);
            break;
        }
        else
        {
            if(English)
                cout << "Please enter y/Y or n/N: ";
            else
                cout << "Làm ơn nhập y/Y hoặc n/N: ";
        }
    }
}

void Process(Node* root)
{
    cout << endl << "- - - - - - - - - - - -" << endl;
    cout << "Please choose your language:" << endl;
    cout << "  1) English" << endl;
    cout << "  2) Vietnamese" << endl;
    cout << "Please make your selection: ";

    string k, e, v;
    bool English = false;
    int n = 0;

    ifstream fe("english.txt");
    fe >> e;
    fe.close();

    ifstream fv("vietnamese.txt");
    fv >> v;
    fv.close();

    while(1)
    {
        cin >> k;

        if(k == "1")
        {
            English = true;
            if(e == "")
                break;
            Input(root, "english", n);
            break;
        }
        else if(k == "2")
        {
            if(v == "")
                break;
            Input(root, "vietnamese", n);
            break;
        }
        else
            if(English)
                cout << "Invalid selection. Please choose again (y/n): ";    
            else
                cout << "Lựa chọn không phù hợp. Vui lòng chọn lại (y/n): ";
    }

    if(!n)
        n++;
    int m = int(log2(n)) + 1;
    string trace[m];
    cout << endl;
    if(English)
    {
        cout << endl << "- - - - - - - - - - - -" << endl;
        cout << "Welcome to Animal Game!" << endl;
        cout << "  1) Play the game" << endl;
        cout << "  2) Save the game file" << endl;
        cout << "  3) Quit" << endl;
        cout << "Please make your selection: ";
    }
    else
    {
        cout << endl << "- - - - - - - - - - - -" << endl;
        cout << "Chào mừng đến với trò chơi Animal!" << endl;
        cout << "  1) Chơi ngay" << endl;
        cout << "  2) Lưu lại trò chơi" << endl;
        cout << "  3) Thoát trò chơi" << endl;
        cout << "Hãy nhập lựa chọn của bạn: ";
    }
        
    cin >> k;
    while(1)
    {
        if(k == "1" || k == "2")
            for(int j = 0; j < m; j++)
                trace[j] = "";

        if(k == "1")
        {
            bool yes = true;
            int i = 0;

            cout << endl;
            if(root == NULL)
            {
                if(English)
                    cout << "Because there aren't any animals yet so" << endl;
                else    
                    cout << "Bởi vì chưa có con vật nào trong trò chơi nên" << endl;
                yes = false;
            }
            
            Game(root, root, trace, i, yes, English);
            k = "4";
            if(English)
                cout << endl << "Do you want to play again? (y/n): ";
            else 
                cout << endl << "Bạn có muốn chơi lần nữa? (y/n): ";
            while(1)
            {
                cin >> k;
                if(k == "y" || k == "Y")
                {
                    k = "1";
                    break;
                }
                else if(k == "n" || k == "N")
                {
                    k = "2";

                    if(English)
                        cout << endl << "See you again!!!";
                    else
                        cout << endl << "Hẹn gặp lại!!!";
                    break;
                }
                else
                {
                    if(English)
                        cout << "Invalid selection. Please choose again (y/n): ";    
                    else
                        cout << "Lựa chọn không phù hợp. Vui lòng chọn lại (y/n): ";
                }        
            }

            if(k == "4")
                break;
            else 
            {
                cout << endl << "- - - - - - - - - - - -" << endl;
                continue;
            }
        }
        else if(k == "2")
        {
            if(English)
            {
                ofstream fout("english.txt");
                Save(root, fout, true);
            }
            else
            {
                ofstream fout("vietnamese.txt");
                Save(root, fout, true);
            }
            break;
        }
        else if(k == "3")
            break;
        else
        {
            if(English)
                cout << "Invalid selection. Please choose again (y/n): ";    
            else
                cout << "Lựa chọn không phù hợp. Vui lòng chọn lại (y/n): ";
        }           

        cin >> k;
    }
}

int main()
{
    Node* root = NULL;
    Process(root);
    return 0;
}
