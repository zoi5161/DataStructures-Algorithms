#include <iostream>
#include <stack>

using namespace std;

void B1()
{
    stack <char> res;
    char x;
    cout << "Enter a sequence of characters: ";
    while((x = getchar()) != '\n')
        res.push(x);
    cout << "The reverse sequence of characters is: ";
    while(!res.empty())
    {
        cout << res.top();
        res.pop();
    }
    cout << endl;
}

void B2()
{
    stack <char> res;
    string s;
    int i = 0;

    cout << "Enter a sequence of characters: ";
    cin >> s;
    while(i < s.length())
    {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{')
            res.push(s[i]);
        else
        {
            if((res.top() == '(' && s[i] == ')') || (res.top() == '[' && s[i] == ']') || (res.top() == '{' && s[i] == '}'))
                res.pop();
            else
            {
                cout << "It isn't balanced" << endl;
                return;
            }
        }
        i++;
    }
    if(res.empty())
        cout << "It is balanced" << endl;
    else
        cout << "It isn't balanced" << endl;
}

void B3()
{
    stack <int> res;
    int n = 0;
    
    cout << "Enter an integer: ";
    cin >> n;

    cout << "The binary representation of " << n << " is: ";
    if(n == 0)
        cout << 0;
    while(!!n)
    {
        if(n%2 == 0)
            res.push(0);
        else
            res.push(1);
        n /= 2;
    }

    while(!res.empty())
    {
        cout << res.top();
        res.pop();
    }
}

void B4()
{
    int n, a = 0, b = 0, prevB = 0, cnt = 0;

    cout << "Enter the number of customers: ";
    cin >> n;
    cout << "Enter the arrival time and transaction processing time (in minute): " << endl;
    for(int i = 1; i <= n; i++)
    {
    	prevB = b;
        cin >> a >> b;
        if(i != 1)
        {
        	if(prevB < a)
        		prevB = a;
        		
        	if(prevB <= a + 10)
        		b += prevB;
        	else
        	{
        		cnt++;
        		b = prevB;
        	}
        }
        else
        	b += a;
    }
    cout << "The number of lost customers: " << cnt << endl;
}

int main()
{
    //B1();
    //B2();
    //B3();
    //B4();
    return 0;
}