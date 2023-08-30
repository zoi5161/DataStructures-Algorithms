#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// B1
long long POWER(int n)
{
    long long s = 1;
    for(int i = 1; i <= n; i++)
        s *= 2;
    return s;
}

void SUMPOWER()
{
    int n;
    long long s = 0;

    cout << "Enter n = ";
    cin >> n;

    for(int i = 1; i <= n; i++)
        s += POWER(i);
    
    for(int i = 1; i <= n; i++)
    {
        if((i == 4 && n < 4)|| i == n)
        {
            cout << "2^" << n << " = " << s << endl << endl;
            break;
        }

        if(i <= 3)
            cout << "2^" << i << " + ";
        else if(i == 4 && n > 4)
            cout << "... + ";
    }
}

void SUMPOWER2()
{
    int n;
    long long s = 0, k = 1;

    cout << "Enter n = ";
    cin >> n;

    for(int i = 1; i <= n; i++)
    {
        k *= 2;
        s += k;
    }

    for(int i = 1; i <= n; i++)
    {
        if((i == 4 && n < 4)|| i == n)
        {
            cout << "2^" << n << " = " << s << endl << endl;
            break;
        }

        if(i <= 3)
            cout << "2^" << i << " + ";
        else if(i == 4 && n > 4)
            cout << "... + ";
    }
}

// B2
int FibonacciRecursive(int n)
{
    if(n <= 1)
        return 1;
    return FibonacciRecursive(n-1) + FibonacciRecursive(n-2);
}

void FibonacciNonRecursive()
{
    int n, f0 = 0, f1 = 1, fn = 1;
    
    cout << "Enter n = ";
    cin >> n;
    cout << "The Fibonacci sequence with non-recursive: ";

    if(n == 1)
        cout << 1 << ' ';
    else
    {
        for(int i = 0; i < n; i++)
        {
            cout << f1 << ' ';
            f0 = f1;
            f1 = fn;
            fn = f1 + f0;
        }
    }
    cout << endl << endl;
}

// B3
void BruteForce()
{
    int n, a[100];
    
    cout << "Enter the number of elements in array: ";
    cin >> n;
    cout << "Enter elements: ";
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    
    stack <int> res;
    stack <int> sub;
    stack <int> result;

    long long sum = 0, mx = INT_MIN;

    for(int i = 1; i <= n; i++)
    {
        for(int j = i; j <= n; j++)
        {
            sum = 0;
            for(int k = i; k <= j; k++)
            {
                sum += a[k];
                sub.push(a[k]);
            }
            if(sum > mx)
            {
                mx = sum;
                res = sub;
            }
            while(!sub.empty())
                sub.pop();
        }
    }

    while(!res.empty())
    {
        result.push(res.top());
        res.pop();
    }

    cout << "The subsequence with largest sum (Brute force with O(N^3)): ";
    while(!result.empty())
    {
        cout << result.top() << ' ';
        result.pop();
    }
    cout << endl << endl;
}

void AnImprovedApproach()
{
    int n, a[100];
    
    cout << "Enter the number of elements in array: ";
    cin >> n;
    cout << "Enter elements: ";
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    stack <int> res;
    stack <int> sub;
    stack <int> result;
    long long sum = 0, mx = INT_MIN;

    for(int i = 1; i <= n; i++)
    {
        sum = 0;
        for(int j = i; j <= n; j++)
        {
            sum += a[j];
            sub.push(a[j]);
            if(sum > mx)
            {
                mx = sum;
                res = sub;
            }
        }
        while(!sub.empty())
            sub.pop();
    }

    while(!res.empty())
    {
        result.push(res.top());
        res.pop();
    }

    cout << "The subsequence with largest sum (An improved approach with O(N^2)): ";
    while(!result.empty())
    {
        cout << result.top() << ' ';
        result.pop();
    }
    cout << endl << endl;
}

void DynamicProgramming()
{
    int n, a[100];
    
    cout << "Enter the number of elements in array: ";
    cin >> n;
    cout << "Enter elements: ";
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    int maxSum = a[1];
    int currentSum = a[1];
    int start = 1;
    int end = 1;
    int currentStart = 1;

    for (int i = 1; i <= n; i++)
    {
        if (currentSum < 0)
        {
            currentSum = a[i];
            currentStart = i;
        }
        else
            currentSum += a[i];

        if (currentSum > maxSum)
        {
            maxSum = currentSum;
            start = currentStart;
            end = i;
        }
    }
    
    cout << "The subsequence with largest sum (Dynamic programming with O(N)): ";
    for(int i = start; i <= end; i++)
        cout << a[i] << ' ';
    cout << endl << endl;
}

// B4
void simulateHydra(string s) 
{
    queue <string> bag;
    bag.push(s);

    while (!bag.empty()) 
    {
        string cur = bag.front();
        bag.pop();

        if (cur.length() > 1) 
        {
            string remain = cur.substr(1);
            bag.push(remain);
            bag.push(remain);
        }

        cout << "Chopped off head: " << cur << endl;
    }

    cout << "The Hydra has been defeated!" << endl;
}

int main()
{
    // B1
    int n;
    cout << "- - - - - - - - - - -" << endl;
    cout << "Lesson B1: " << endl;
    cout << "Enter n = ";
    cin >> n;
    cout << "2^" << n << " = " << POWER(n) << endl << endl;

    SUMPOWER();
    SUMPOWER2();

    // B2
    cout << endl << "- - - - - - - - - - -" << endl;
    cout << "Lesson B2:" << endl; 
    cout << "Enter n = ";
    cin >> n;

    cout << "The Fibonacci sequence with recursive: ";
    for(int i = 0; i < n; i++)
        cout << FibonacciRecursive(i) << ' ';
    cout << endl << endl;

    FibonacciNonRecursive();

    // B3
    cout << "- - - - - - - - - - -" << endl;
    cout << "Lesson B3: " << endl;
    BruteForce();
    AnImprovedApproach();
    DynamicProgramming();

    // B4
    cout << "- - - - - - - - - - -" << endl;
    cout << "Lesson B4: " << endl;
    string word;
    cout << "Enter the initial word: ";
    cin >> word;
    simulateHydra(word);
    return 0;
}