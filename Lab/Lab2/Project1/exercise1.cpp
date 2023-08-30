#include <iostream>

using namespace std;

void SortAscending(int n, int a[])
{
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(a[j] < a[i])
                swap(a[i], a[j]);
}

void SortDescending(int n, int a[])
{
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(a[j] > a[i])
                swap(a[i], a[j]);
}

int main()
{
    int n, ob = 0, ev = 0;  

    cout << "Enter the number of elements of the array: ";
    cin >> n;

    int *a = new int[n];
    int *obb = new int[n];
    int *even = new int[n];

    cout << "Enter elements: ";
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        if(a[i] % 2 == 0)
            even[ev++] = a[i];
        else
            obb[ob++] = a[i];
    }

    SortAscending(ev, even);
    SortDescending(ob, obb);

    ev = 0;
    ob = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] % 2 == 0)
            a[i] = even[ev++];
        else
            a[i] = obb[ob++];
    }

    cout << "After sorting: ";
    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';

    delete []a;
    delete []obb;
    delete []even;

    return 0;
}