#include <iostream>
#include <math.h>
#define st first
#define nd second

using namespace std;

const int N = 2e7 + 6;
pair<long long, string> HashTable[N];
int SizeTable = N * 5/4;

struct Monster
{
    string name;
    long long phone;
};

int HashCode(string x)
{
    int k = 0; 
    for(int i = 0; i < x.length(); i++)
        k += int(x[i]) + (int(x[i]))*(26+i);
    return k;
}

int H(long long x, int n)
{
    return x % n;
}

bool Add(Monster m, long long p)
{
    int idx = H(HashCode(m.name), SizeTable);
     
    while(HashTable[idx].st != 0 && HashTable[idx].st != p)
        idx = H(idx + 1, SizeTable);
    if(HashTable[idx].st != p)
    {
        HashTable[idx].st = p;
        HashTable[idx].nd = m.name;
        return true;
    }
    return false;
}

bool Delete(Monster m)
{
    int idx = H(HashCode(m.name), SizeTable);

    if(HashTable[idx].st == 0)
        return false;
    else 
    {
        while(HashTable[idx].nd != m.name)
            idx = H(idx + 1, SizeTable);
        HashTable[idx].st = 0;
        HashTable[idx].nd = "\0";
        return true;
    }
}

bool Update(Monster m, long long p)
{
    int idx = H(HashCode(m.name), SizeTable);
    if(HashTable[idx].st == 0)
        return false;
    else
    {
        while(HashTable[idx].nd != m.name)
            idx = H(idx + 1, SizeTable);
        HashTable[idx].st = p;
        return true;
    }
}

long long Find(Monster m)
{
    int idx = H(HashCode(m.name), SizeTable);
    if(HashTable[idx].st == 0)
        return -1;
    else
    {
        while(HashTable[idx].nd != m.name)
            idx = H(idx + 1, SizeTable);
        return HashTable[idx].st;
    }
}

void Process()
{
    string choose, s;
    Monster m;
    bool flag;

    while(choose != "EXIT")
    {
        cout << "-  -  -  -  Telephone Directory  -  -  -  -" << endl;
        cout << "Your options: Add, Delete, Update, Find, Exit" << endl << endl;
        cout << "Your choose: ";

        cin >> choose;
        cin.ignore();

        for(int i = 0; i < choose.length(); i++)
            choose[i] = toupper(choose[i]);
        
        flag = false;

        if(choose == "ADD")
        {
            cout << "Enter the name of monster (Add): ";
            getline(cin, m.name, '\n');
            cout << "Enter the phone of monster (Add): ";
            getline(cin, s, '\n');
            for(int i = 0; i < s.length(); i++)
            {
                if(s[i] < '0' || s[i] > '9')
                {
                    cout << endl << "Please choose from the available options!" << endl << endl << endl << endl << endl << endl << endl << endl;
                    flag = true;
                    break;
                }
            }

            if(!flag)
            {   
                if(s.length() < 4)
                    m.phone = stoi(s);
                else
                {
                    string k = "";

                    for(int i = 0; i < 4; i++)
                        k += s[i];
                    m.phone = stoi(k);

                    k = "";
                    for(int i = 4; i < s.length(); i++)
                        k += s[i];
                    m.phone *= pow(10, s.length() - 4);
                    m.phone += stoi(k);
                }

                Add(m, m.phone);
                cout << endl << "SUCCESSFUL !!!" << endl << endl << endl << endl << endl << endl;
            }
        }
        else if(choose == "DELETE")
        {
            cout << "Enter the name of monster (Delete): ";
            getline(cin, m.name, '\n');

            Delete(m);
            cout << endl << "SUCCESSFUL !!!" << endl << endl << endl << endl << endl << endl;
        }
        else if(choose == "UPDATE")
        {
            cout << "Enter the name of monster (Update): ";
            getline(cin, m.name, '\n');
            cout << "Enter the phone of monster will change: ";
            getline(cin, s, '\n');
            for(int i = 0; i < s.length(); i++)
            {
                if(s[i] < '0' || s[i] > '9')
                {
                    cout << endl << "Please choose from the available options!" << endl << endl << endl << endl << endl << endl << endl << endl;
                    flag = true;
                    break;
                }
            }

            if(!flag)
            {
                m.phone = stoi(s);

                if(!Update(m, m.phone))
                    cout << "There isn't " << m.name << " in Telephone Directory." << endl << endl << endl << endl;
                else
                    cout << endl << "SUCCESSFUL !!!" << endl << endl << endl << endl << endl << endl;
            }
        }
        else if(choose == "FIND")
        {
            cout << "Enter the name of monster (Find): ";
            getline(cin, m.name, '\n');
            
            if(Find(m) == -1)
                cout << "There isn't " << m.name << " in Telephone Directory." << endl << endl << endl << endl << endl << endl << endl << endl;
            else 
                cout << "The phone number: " << Find(m) << endl << endl << endl << endl << endl << endl;
        }
        else if(choose != "EXIT")
            cout << "Please choose from the available options!" << endl << endl << endl << endl << endl << endl << endl << endl;
    }
}

int main()
{
    Process();
    return 0;
}