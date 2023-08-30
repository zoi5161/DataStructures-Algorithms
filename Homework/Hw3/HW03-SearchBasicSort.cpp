#include <iostream>

using namespace std;

// B1
void RemovePos(int a[], int &n, int pos)
{
    for(int i = pos; i < n; i++)
        a[i] = a[i+1];
    a[n-1] = NULL;
    n--;
}

void RemoveItemUnsorted(int a[], int &n, int x)
{
    bool check = false;
    for(int i = 0; i < n; i++)
    {
        if(a[i] == x)
        {
            check = true;
            RemovePos(a, n, i);
            i--;
        }
    }
    if(!n)
        cout << "There are not any elements in the array." << endl;
    else if(!check)
        cout << "There isn't element " << x << " in the array." << endl;
    else
    {
        cout << "After remove " << x << " with unsorted array. The array: ";
        for(int i = 0; i < n; i++)
            cout << a[i] << ' ';
        cout << endl;
    } 
    cout << endl;
}

int BinarySearch(int a[], int n, int x)
{
    int l = 0, r = n - 1, m;
    while(l <= r)
    {
        m = (l+r)/2;
        if(a[m] == x)
            return m;
        else if(a[m] > x)
            r = m - 1;
        else 
            l = m + 1;
    }
    return -1;
}

void RemoveItemSorted(int a[], int &n, int x)
{
    int pos = BinarySearch(a, n, x);
    bool check = false;

    while(pos != -1)
    {
        check = true;
        RemovePos(a, n, pos);
        pos = BinarySearch(a, n, x);
    }

    if(!n)
        cout << "There are not any elements in the array." << endl;
    else if(!check)
        cout << "There isn't element " << x << " in the array." << endl;
    else
    {
        cout << "After remove " << x << " with sorted array. The array: ";
        for(int i = 0; i < n; i++)
            cout << a[i] << ' ';
        cout << endl;
    } 
    cout << endl;
}

// B2
void GroneSort(int a[], int n)
{
    int i = 0;
    while(i < n)
    {
        if(i == 0 || a[i] >= a[i-1])
            i++;
        else
        {
            swap(a[i], a[i-1]);
            i--;
        }
    }
    cout << "After sort, the array: ";
    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl << endl;
}

// B3
void CountInversions(int a[], int n)
{
    int cnt = 0;
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(a[j] < a[i])
                cnt++;
    cout << "The number of inversions: " << cnt << endl << endl;
}

// B4
void SortStringArray(string a[], int n)
{
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(a[j] < a[i])
                swap(a[j], a[i]);
    
    cout << "After sort. The array: [";
    for(int i = 0; i < n - 1; i++)
        cout << a[i] << ", ";
    cout << a[n-1] << ']' << endl << endl;
}

void CountString(string a[], int n)
{
    int cnt = 1;
    string tmp = a[0];

    cout << "The number of occurrences of the strings: " << endl; 
    for(int i = 1; i < n; i++)
    {
        if(a[i] != tmp)
        {
            cout << tmp << ": " << cnt << endl;
            cnt = 1;
            tmp = a[i];
        }
        else
            cnt++;
    }
    cout << tmp << ": " << cnt << endl;
}

int main()
{
    // B1
    cout << "- - - - - - - - - - - - - - - - - -" << endl;
    cout << "Lesson B1:" << endl;

    int n, x;

    cout << "Enter the number of elements of the unsorted array: ";
    cin >> n;
    int *a1 = new int[n];

    cout << "Enter elements of the unsorted array: ";
    for(int i = 0; i < n; i++)
        cin >> a1[i];

    cout << "Enter the item to be deleted: ";
    cin >> x;

    RemoveItemUnsorted(a1, n, x);
    delete []a1;


    cout << "Enter the number of elements of the sorted array: ";
    cin >> n;
    int *a2 = new int[n];

    cout << "Enter elements of the sorted array: ";
    for(int i = 0; i < n; i++)
        cin >> a2[i];

    cout << "Enter the item to be deleted: ";
    cin >> x;

    RemoveItemUnsorted(a2, n, x);
    delete []a2;

    // B2
    cout << "- - - - - - - - - - - - - - - - - -" << endl;
    cout << "Lesson B2:" << endl;
    
    cout << "Enter the number of elements of the array: ";
    cin >> n;
    int *b =  new int [n];

    cout << "Enter elements of the array: ";
    for(int i = 0; i < n; i++)
        cin >> b[i];

    GroneSort(b, n);
    delete []b;

    // B3
    cout << "- - - - - - - - - - - - - - - - - -" << endl;
    cout << "Lesson B3:" << endl;

    cout << "Enter the number of elements of the array: ";
    cin >> n;
    int *c =  new int [n];

    cout << "Enter elements of the array: ";
    for(int i = 0; i < n; i++)
        cin >> c[i];

    CountInversions(c, n);
    delete []c;
    
    // B4
    cout << "- - - - - - - - - - - - - - - - - -" << endl;
    cout << "Lesson B4:" << endl;

    cout << "Enter the number of elements of the array: ";
    cin >> n;
    string *d =  new string [n];

    cout << "Enter elements of the array: ";
    for(int i = 0; i < n; i++)
        cin >> d[i];

    SortStringArray(d, n);
    CountString(d, n);
    delete []d;
    return 0;
}