#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;
typedef chrono::milliseconds MSEC;
typedef chrono::high_resolution_clock HRC;

// Selection Sort
void SelectionSort(long long a[], int n)
{
    auto start = HRC::now();
    int idx;
    for(int i = 0; i < n-1; i++)
    {
        idx = i;
        for(int j = i+1; j < n; j++)
            if(a[j] < a[idx])
                idx = j;
        swap(a[i], a[idx]);
    }
    auto end = HRC::now();
    auto time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl << endl;
}

// Insertion Sort
void InsertionSort(long long a[], int n)
{
    auto start = HRC::now();
    int val, j;
    for(int i = 1; i < n; i++)
    {
        val = a[i];
        j = i-1;
        while(j >= 0 && a[j] > val)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1] = val;
    }
    auto end = HRC::now();
    auto time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl << endl;
}

// Interchange Sort
void InterchangeSort(long long a[], int n)
{
    auto start = HRC::now();
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(a[i] > a[j])
                swap(a[i], a[j]);
    auto end = HRC::now();
    auto time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl << endl;
}

// Bubble Sort
void BubbleSort(long long a[], int n)
{
    auto start = HRC::now();
    for(int i = 1; i < n; i++)
        for(int j = n - 1; j >= i; j--)
            if(a[j] < a[j-1])
                swap(a[j], a[j-1]);
    auto end = HRC::now();
    auto time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl << endl;
}

// Shaker Sort
void ShakerSort(long long a[], int n)
{
    auto start = HRC::now();
    int sur = 0, bot = n - 1;
    while(sur < bot)
    {
        for(int j = bot; j > sur; j--)
            if(a[j] < a[j-1])
                swap(a[j], a[j-1]);

        sur++;

        for(int j = sur; j < bot; j++)
            if(a[j] > a[j+1])
                swap(a[j], a[j+1]);
        bot--;
    }
    auto end = HRC::now();
    auto time = chrono::duration_cast<MSEC>(end - start);
    cout << time.count() << " milisec" << endl << endl;
}

// Input
void Sort(long long a[], int n)
{
    int val, j;
    for(int i = 1; i < n; i++)
    {
        val = a[i];
        j = i-1;
        while(j >= 0 && a[j] > val)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1] = val;
    }
}

void Random(int n, long long k, long long a[])
{
    for(int i = 0; i < n; i++)
        a[i] = rand()%(k+1);
}

void Orderly(int n, long long k, long long a[])
{
    Random(n, k, a);
    Sort(a, n);
}

void OrderlyReversed(int n, long long k, long long a[])
{
    Orderly(n, k, a);
    for(int i = 0; i < n/2; i++)
        swap(a[i], a[n-i-1]);
}

void AlmostInOrder(int n, long long k, long long a[])
{
    int wrong = n/20, x;
    int visit[n];

    Orderly(n, k, a);
    if(wrong < 0 && n != 1)
        wrong = 1;

    while(wrong > 0)
    {
        x = rand()%(n+1);
        if(visit[x] == 0)
        {
            swap(a[x], a[n - x - 1]);
            visit[x]++;
            wrong -= 2;
        }
    }
}

// Print
void Print(int n, long long k, string s)
{
    cout << "The type of input: " << s << endl;
    cout << "The number of elements: " << n << endl;
    cout << "The max value of elements: " << k << endl;
    cout << "The execution time: ";
}

int main()
{
    srand(time(0));
    int n;
    long long k;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter the max value of elements: ";
    cin >> k;

    long long *a = new long long[n];

    // Selection Sort
    cout << "- - - - - - - - - - - - - - -" << endl;
    cout << "Selection Sort:" << endl << endl;

    Random(n, k, a);
    Print(n, k, "Random");
    SelectionSort(a, n);

    Orderly(n, k, a);
    Print(n, k, "Orderly");
    SelectionSort(a, n);

    OrderlyReversed(n, k, a);
    Print(n, k, "Reverse order");
    SelectionSort(a, n);

    AlmostInOrder(n, k, a);
    Print(n, k, "Almost in order");
    SelectionSort(a, n);

    // // Insertion Sort
    cout << endl << "- - - - - - - - - - - - - - -" << endl;
    cout << "Insertion Sort:" << endl << endl;

    Random(n, k, a);
    Print(n, k, "Random");
    InsertionSort(a, n);

    Orderly(n, k, a);
    Print(n, k, "Orderly");
    InsertionSort(a, n);

    OrderlyReversed(n, k, a);
    Print(n, k, "Reverse order");
    InsertionSort(a, n);

    AlmostInOrder(n, k, a);
    Print(n, k, "Almost in order");
    InsertionSort(a, n);

    // Interchange Sort
    cout << "- - - - - - - - - - - - - - -" << endl;
    cout << "Interchange Sort:" << endl << endl;

    Random(n, k, a);
    Print(n, k, "Random");
    InterchangeSort(a, n);

    Orderly(n, k, a);
    Print(n, k, "Orderly");
    InterchangeSort(a, n);

    OrderlyReversed(n, k, a);
    Print(n, k, "Reverse order");
    InterchangeSort(a, n);

    AlmostInOrder(n, k, a);
    Print(n, k, "Almost in order");
    InterchangeSort(a, n);

    // Bubble Sort
    cout << "- - - - - - - - - - - - - - -" << endl;
    cout << "Bubble Sort:" << endl << endl;

    Random(n, k, a);
    Print(n, k, "Random");
    BubbleSort(a, n);

    Orderly(n, k, a);
    Print(n, k, "Orderly");
    BubbleSort(a, n);

    OrderlyReversed(n, k, a);
    Print(n, k, "Reverse order");
    BubbleSort(a, n);

    AlmostInOrder(n, k, a);
    Print(n, k, "Almost in order");
    BubbleSort(a, n);

    // Shaker Sort
    cout << "- - - - - - - - - - - - - - -" << endl;
    cout << "Shaker Sort:" << endl << endl;

    Random(n, k, a);
    Print(n, k, "Random");
    ShakerSort(a, n);

    Orderly(n, k, a);
    Print(n, k, "Orderly");
    ShakerSort(a, n);

    OrderlyReversed(n, k, a);
    Print(n, k, "Reverse order");
    ShakerSort(a, n);

    AlmostInOrder(n, k, a);
    Print(n, k, "Almost in order");
    ShakerSort(a, n);
    delete []a;
    return 0;
}