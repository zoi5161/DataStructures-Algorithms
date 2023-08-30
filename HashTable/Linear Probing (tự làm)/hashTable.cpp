#include <iostream>
#include <string.h>
using namespace std;

const int N = 2e6+ 5;
bool F[N];
int* prime;
int numPrime = 0;
int m;

struct NID
{
    int id;
    string name;
    bool emp;
};

NID* h;

void ERA()
{
    int n = 0;

    for (int i = 1; i <= N; i++) 
        F[i] = 1;
    F[0] = 0;
    F[1] = 0;

    for (int i = 2; i*i <= N; i++)
        if (F[i] == 1)
        {
            for (int j = i*2; j <= N; j += i) 
                F[j]=0;
            n++;
        }

    prime = new int [n];
    for (int i = 2; i <= N; i++)
        if (F[i] == 1) 
            prime[numPrime++] = i;
}

int BinarySearch(int n)
{
    int res = 0;
    int l = 1, r = numPrime;
    while (l <= r)
    {
        int m = l+((r-l)/2);

        if (prime[m] == n) 
            return m;
        else if (prime[m] < n) 
        {
            l = m+1;
            res = max(res,m);
        }
        else
            r = m-1;
    }
    return res;
}

void buildHash(int n)
{
    for (int i = 0; i < m; i++)
        h[i].emp = 1;
        
    cout << "Enter elements: \n\n";
    int x, ind;
    for (int i = 1; i <= n; i++)
    {
        cout << "Enter ID: ";
        cin >> x;

        ind = x%m;
        while (h[ind].emp == 0)
        {
            if (ind == m-1) 
                ind = 0;
            else 
                ind++;
        }
        h[ind].id = x;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, h[ind].name);
        h[ind].emp = 0;
    }
}

int searchHash(int x)
{
    int ind = x%m;
    while (h[ind].emp == 0 && h[ind].id != x)
    {
        if (ind == m-1) 
            ind = 0;
        else 
            ind++;
    }  
    if (h[ind].emp == 1) 
        return -1;
    else 
        return ind;
}

int main()
{
    ERA();
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    m = prime[BinarySearch(2*n)]; // m là SNT thứ 2*n
    h = new NID[m];

    buildHash(n);

    cout << "Enter number of queries: ";
    int q;
    cin >> q;

    while(q--)
    {
        int x;
        cout << "Search ID: ";
        cin >> x;
        
        int s = searchHash(x);
        if (s == -1) 
            cout << "Not Found ID" << '\n';
        else 
            cout << h[s].name << '\n';
    }
    return 0;
}