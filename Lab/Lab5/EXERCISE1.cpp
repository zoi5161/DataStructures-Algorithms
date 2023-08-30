#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

typedef chrono::milliseconds MSEC;
typedef chrono::high_resolution_clock HRC;

// 1.1
long long Djb2(string s)
{
    long long hash = 5381;
    int c = 0;

    while(c < s.length())
        hash = ((hash << 5) + hash) + int(s[c++]); // hash * 33 + c

    return hash;
}

// 1.2 - 1.3
int Hash(long long x, int n)
{
    return x % n;
}

// 1.4
// Get Input
void Input(string a[], int &n)
{
    ifstream fin;
    fin.open("names.txt");

    if(fin.is_open())
    {
        n = 0;
        while(fin >> a[n])
            n++;
        fin.close();
    }
    else
        cout << "Can't open file";
}

// Linear Search
bool LinearSearch(string a[], string x, int n)
{
    for(int i = 0; i < n; i++)
        if(a[i] == x)
            return true;
    return false;
}

// Binary Search
void Sort(string a[], int n)
{
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(a[i] > a[j])
                swap(a[i], a[j]);
}

bool BinarySearch(string a[], string x, int l, int r)
{
    int m;
    while(l < r)
    {
        m = l + (r-l)/2;
        if(a[m] > x)
            r = m - 1;
        else if(a[m] < x)
            l = m + 1;
        else 
            return true;
    }
    return false;
}

// Linear Probing
bool LinearProbing(long long a[], long long x, int n)
{
    int index = Hash(x, n);
    while(a[index] != 0 && a[index] != x)
        index = Hash(index + 1, n);

    if(a[index] == 0)
    {
        a[index] = x;
        return true;
    }

    return false;
}

bool SearchProbing(long long a[], string x, int Size)
{
    long long k = Djb2(x);
    int index = Hash(k, Size);
    while(a[index] != 0 && a[index] != k)
        index = Hash(index + 1, Size);
    
    if(a[index] == k)
        return true;
    return false;
}

// Chaining Approach
struct Node
{
    long long data;
    Node* pNext;
};

bool ChainingApproach(Node* a[], long long x, int n)
{
    int index = Hash(x, n);
    if(a[index] == nullptr)
    {
        a[index] = new Node;
        a[index] -> data = x;
        a[index] -> pNext = nullptr;
        return true;
    }

    Node* p = a[index];
    while(p -> pNext != nullptr)
    {
        if(p -> data == x)
            return false;
        p = p -> pNext;
    }
    p -> pNext = new Node;
    p = p -> pNext;
    p -> data = x;
    p -> pNext = nullptr;
    return true;
}

bool SearchChaining(Node* a[], string s, int Size)
{
    long long k = Djb2(s);
    int index = Hash(k, Size);

    Node* p = a[index];
    while(p != nullptr)
    {
        if(p -> data == k)
            return true;
        p = p -> pNext;
    }
    return false;
}

// Quadratic Probing
bool QuadraticProbing(long long a[], long long x, int Size)
{
    int v, index = Hash(x, Size);
    if(a[index] == -1)
    {
        a[index] = x;
        return true;
    }
    else
    {
        for(int i = 0; i < Size; i++)
        {
            v = Hash(index + i*i, Size);
            if(a[v] == -1)
            {
                a[v] = x;
                return true; 
            }
        }
        return false;
    }
}

bool SearchQuadratic(long long a[], long long x, int Size)
{
    int v, index = Hash(x, Size);
    if(a[index] == x)
        return true;

    if(a[index] != -1)
    {
        for(int i = 0; i < Size; i++)
        {
            v = Hash(index + i*i, Size);
            if(a[v] == x)
                return true; 
        }
    }
    return false;
}

// Double Hashing
const int N = 2e5 + 6;
bool F[N];
int* Prime;
int NumPrime = 0;

struct People
{
    long long id;
    bool emp;
};

void Sieve()
{
    int n = 0;

    F[0] = 1;
    F[1] = 1;

    for(int i = 2; i <= N; i++)
        if(F[i] == 0)
        {
            for(int j = i*2; j <= N; j += i)
                F[j] = 1;
            n++;
        }

    Prime = new int[n];
    for(int i = 2; i < N; i++)
        if(!F[i])
            Prime[NumPrime++] = i;
}

int BinarySearch2(int n)
{
    int res = 0, l = 1, r = NumPrime;
    while (l <= r)
    {
        int m = l+((r-l)/2);

        if(Prime[m] == n) 
            return m;
        else if(Prime[m] < n) 
        {
            l = m+1;
            res = max(res,m);
        }
        else
            r = m-1;
    }
    return res;
}

void DoubleHashing(int Size, int n, string name[], People h[])
{
    int idx;
    long long x;

    for(int i = 0; i < Size; i++)
        h[i].emp = true;
    
    for(int i = 0; i < n; i++)
    {
        x = abs(Djb2(name[i]));
        idx = x % Size;

        while(!h[idx].emp)
        {
            if(idx == Size - 1)
                idx = 0;
            else
                idx++;
        }
        h[idx].id = x;
        h[idx].emp = false;
    }
}

bool SearchDouble(long long x, int Size, People h[])
{
    int idx = abs(x % Size);
    while(h[idx].emp == 0 && h[idx].id != x)
    {
        if(idx == Size - 1)
            idx = 0;
        else
            idx++;
    }

    if(h[idx].emp == 1)
        return false;
    else
        return true;
}

// Main
int main()
{
    string name[18500];
    string s;
    int cnt, n, Size;
    long long k;

    // 1.1
    cout << "- - - - - - - - - - - - - -" << endl;
    cout << "Question 1:" << endl;
    cout << "Enter a string: ";
    cin >> s;

    k = Djb2(s);
    cout << endl << "After hashing \"" << s << "\" to integer: " << k << endl;

    // 1.2
    cout << endl << "- - - - - - - - - - - - - -" << endl;
    cout << "Question 2:" << endl;
    cout << "Enter the number of elements of the string array: ";
    cin >> n;

    Size = n * 5/4;
    cout << "The size of table: " << Size << endl << endl;

    // 1.3
    cout << endl << "- - - - - - - - - - - - - -" << endl;
    cout << "Question 3:" << endl;
    cout << "The position of \"" << s << "\" in Hash Table is: " << Hash(k, n) << endl << endl;

    // 1.4
    cout << endl << "- - - - - - - - - - - - - -" << endl;
    cout << "Question 4:" << endl;
    cout << "Type of elements: String (From file \"names.txt\")" << endl;
    Input(name, cnt);

    cout << "The number of element: " << cnt << endl << endl;
    Size = cnt * 5/4;
    long long a[Size];

    // Linear Search
    cout << "Linear Search: ";

    auto start = HRC::now();
    for(int i = 0; i < cnt; i++)
        LinearSearch(name, name[i], cnt);
    auto end = HRC::now();
    auto time = chrono::duration_cast<MSEC>(end - start);

    cout << time.count() << " milisec" << endl;

    // Binary Search
    cout << "Binary Search: ";
    Sort(name, cnt);

    start = HRC::now();
    for(int i = 0; i < cnt; i++)
        BinarySearch(name, name[i], 0, cnt);
    end = HRC::now();
    time = chrono::duration_cast<MSEC>(end - start);

    cout << time.count() << " milisec" << endl;

    // Linear Probing
    cout << "Linear Probing: ";
    for(int i = 0; i < cnt; i++)
        LinearProbing(a, Djb2(name[i]), Size);
        
    start = HRC::now();
    for(int i = 0; i < cnt; i++)
        SearchProbing(a, name[i], Size);
    end = HRC::now();
    time = chrono::duration_cast<MSEC>(end - start);

    cout << time.count() << " milisec" << endl;

    // Chaining Approach
    cout << "Chaining Approach: ";
    Node* b[Size];
    for (int i = 0; i < Size; i++)
        b[i] = nullptr;
    for (int i = 0; i < cnt; i++)
        ChainingApproach(b, Djb2(name[i]), Size);

    start = HRC::now();

    for(int i = 0; i < cnt; i++)
        SearchChaining(b, name[i], Size);

    end = HRC::now();
    time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl;

    // Quadratic Probing
    cout << "Quadratic Probing: ";
    long long c[Size];
    for(int i = 0; i < Size; i++)
        c[i] = -1;
    
    for(int i = 0; i < cnt; i++)
        QuadraticProbing(c, Djb2(name[i]), Size);

    start = HRC::now();
    
    for(int i = 0; i < cnt; i++)
        SearchQuadratic(c, Djb2(name[i]), Size);
    
    end = HRC::now();
    time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl;

    // Double Hashing
    cout << "Double Hashing: ";
    Sieve();

    int SizeHash = Prime[BinarySearch2(2*cnt)];
    People* h = new People[SizeHash];

    DoubleHashing(SizeHash, cnt, name, h);
    start = HRC::now();
    for(int i = 0; i < cnt; i++)
        SearchDouble(Djb2(name[i]), SizeHash, h);
    end = HRC::now();
    time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl;
    return 0;
}