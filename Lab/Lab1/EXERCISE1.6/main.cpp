#include <iostream>
#define MAX 3

using namespace std;

char a[MAX];

void push(int &n, char x)
{
    n++;
    a[n] = x;
}

void pop(int &n)
{
    a[n] = '\0';
    n--;
}

void empty(int &n)
{
    if(n == 0)
        cout << "The stack is empty." << endl;
    else
        cout << "The stack still has " << n << " elements." << endl;
}

void print(int &n, bool &stop)
{
    cout << "- - - - - - - - - - - - - - -" << endl;
    if(n == 0)
        cout << "The stack is empty." << endl;
    else
    {
        cout << "The stack is: [";
        for(int i = 1; i < n; i++)
            cout << a[i] << ", ";
        cout << a[n];
        cout << ']' << endl;
    }
    cout << "Your option: Push, Pop, Stop." << endl;
    cout << "Your choice: ";

    string s;
    cin >> s;

    for(int i = 0; i < s.length(); i++)
        s[i] = toupper(s[i]);
    
    if(s == "PUSH")
    {
        int k;
        char v;

        cout << "How many elements do you want to push?" << endl;
        cout << "N = ";
        cin >> k;

        if(n + k > MAX)
        {
            cout << endl << "The stack can hold " << MAX - n << " elements." << endl;
            cout << "Please pop some elements or push less elements to continue." << endl;
            return;
        }

        cout << "They are: ";
        for(int i = 1; i <= k; i++)
        {
            cin >> v;
            push(n, v);
        }
    }
    else if(s == "POP")
    {
        if(n == 0)
        {
            cout << endl;
            cout << "There aren't any elements in the stack" << endl;
            cout <<  "You can't use the pop command" << endl;
        }
        else
        {
            int k;
            cout << "How many elements do you want to pop?" << endl;
            cout << "N = ";
            cin >> k;

            while(k > n)
            {
                cout << endl;
                cout << "Too few elements to pop off the stack." << endl;
                cout << "Please enter again. N = ";
                cin >> k;
            }

            for(int i = 1; i <= k; i++)
                pop(n);
        }
    }
    else
        stop = true;
}

int main()
{
    int n = 0;
    bool stop = false;

    while(!stop)
        print(n, stop);
    return 0;
}