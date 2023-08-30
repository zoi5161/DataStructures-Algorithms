// Trần Gia Bảo
// 22127034
// Nhung cau da lam duoc: Cau 1-a,b,c,d,e

#include <iostream>
#include <fstream>

#define N 100000

using namespace std;

struct Song
{
    string id;
    string name;
    string author;
};

struct Node
{
    Song data;
    Node* next;
};

Node* createNode(Song x)
{
    Node* tmp = new Node();
    tmp -> data = x;
    tmp -> next = NULL;
    return tmp;
}

void insertLast(Node* &p, Song x)
{
    Node* tmp = createNode(x);
    if(p == NULL)
        p = tmp;
    else
    {
        Node* a = p;
        while(a -> next != NULL)
            a = a -> next;
        a -> next = tmp;
    }
}

void input(Song k[], int &n)
{
    ifstream fin("input.txt");
    if(fin.is_open())
    {
        string s, tmp, tmp2;
        int flag;
        n = 0;

        while(!fin.eof())
        {
            tmp = "";
            tmp2 = "";
            flag = 0;
            getline(fin, s);

            for(int i = 0; i < s.length(); i++)
            {
                if(s[i] == ',')
                {
                    flag++;
                    if(flag == 1)
                        k[n].id = tmp;
                    else if(flag == 2)
                        k[n].name = tmp;
                    tmp = "";
                    i++;
                }
                else
                    tmp += s[i];
            }

            k[n++].author = tmp;
        }
        fin.close();
    }
    else 
        cout << "Can't open file";
}

void QuickSort(Song a[], int l, int r)
{
    int i = l, j = r, pilot = (r+l)/2;
    while(i <= j)
    {
        while(a[i].id < a[pilot].id)
            i++;
        while(a[j].id > a[pilot].id)
            j--;
        if(i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if(i < r)
        QuickSort(a, i, r);
    if(j > l)
        QuickSort(a, l, j);
}

void BubbleSort(Song a[], int n)
{
    for(int i = 1; i < n - 1; i++)
        for(int j = n - 1; j >= i; j--)
            if(a[j].name < a[j-1].name)
                swap(a[j], a[j-1]);
}

void FindDup(Song a[], int n)
{
    bool flag, have = false;
    int cnt;
    Song tmp[n];

    for(int i = 0; i < n - 1; i++)
    {
        cnt = 1;
        flag = false;
        tmp[cnt - 1] = a[i];

        for(int j = i + 1; j < n; j++)
            if(a[j].name == a[i].name)
            {
                if(!have)
                    cout << endl;
                have = true;
                flag = true;
                tmp[cnt] = a[j];
                cnt++;
            }

        if(flag)
        {
            cout << tmp[0].name << " - so luong: " << cnt << " - ";
            for(int j = 0; j < cnt; j++)
            {
                cout << tmp[j].id << " (" << tmp[j].author << ")"; 
                if(j != cnt - 1)
                    cout << ", ";
            }
            cout << endl << endl;
        }
    }

    if(!have)
        cout << "Khong co bai hat nao trung ten" << endl;
}

bool Delete(Song a[], int &n, string k)
{
    for(int i = 0; i < n; i++)
    {
        if(a[i].id == k)
        {
            for(int j = i; j < n - 1; j++)
                a[j] = a[j+1];
            n--;
            return true;
        }
    }
    return false;
}

void process(Song a[], int &n, bool &run)
{
    string choose;

    while(1)
    {
        cout << endl << "- - - - - Menu - - - - -" << endl;
        cout << "1. Nhap danh sach bai hat" << endl;
        cout << "2. In ra playlist theo ma bai hat" << endl;
        cout << "3. In ra playlist theo ten bai hat" << endl;
        cout << "4. Tim ten bai hat trung lap" << endl;
        cout << "5. Xoa bai hat" << endl;
        cout << "6. Thoat" << endl << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choose;

        if(choose == "1")
        {
            run = true;
            input(a, n);
            cout << endl << "Them thanh cong!!!" << endl;
        }
        else if(run)
        {
            if(choose == "2")
            {
                QuickSort(a, 0, n - 1);
                ofstream fout1("ListA.txt");
                for(int i = 0; i < n; i++)
                {
                    fout1 << a[i].id << " - " << a[i].name << " - " << a[i].author;
                    if(i != n - 1)
                        fout1 << endl;
                }
                cout << "Da in thanh cong vao file 'ListA.txt'" << endl;
            }
            else if(choose == "3")
            {
                BubbleSort(a, n);
                ofstream fout2("ListB.txt");
                for(int i = 0; i < n; i++)
                {
                    fout2 << a[i].id << " - " << a[i].name << " - " << a[i].author;
                    if(i != n-1)
                        fout2 << endl;
                }
                cout << n << ' ' << a[0].id << ' ' << a[n-1].id << endl;
                cout << "Da in thanh cong vao file 'ListB.txt'" << endl;
            }
            else if(choose == "4")
            {
                BubbleSort(a, n);
                FindDup(a, n);
            }
            else if(choose == "5")
            {
                cout << endl << "Nhap ma bai hat ban muon xoa: ";
                string f;
                cin >> f;

                if(Delete(a, n, f))
                {
                    cout << endl << "Xoa thanh cong bai hat!!!" << endl;
                    for(int i = 0; i < n; i++)
                        cout << a[i].id << " - " << a[i].name << " - " << a[i].author << endl;
                }
                else
                    cout << endl << "Khong tim thay bai hat nay." << endl;
            }
            else if(choose == "6")
                return;
            else
                cout << "Lua chon khong hop le. Vui long chon lai!";
        }
        else if(choose == "6")
            return;
        else
            cout << endl << "Chua co du lieu, vui long chon 1 de lay du lieu danh sach bai hat";
    }
}

int main()
{
    Song k[N];
    int n = 0;
    bool run = false;

    process(k, n, run);
    return 0;
}