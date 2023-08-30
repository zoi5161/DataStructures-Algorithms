#include <iostream>

using namespace std;

void sortAscending(int a[], int n)
{
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(a[i] > a[j])
                swap(a[i], a[j]);
}

int main()
{
    int n, m, k = 0;

    cout << "Enter the number of rows: ";
    cin >> n;
    cout << "Enter the number of columns: "; 
    cin >> m;

    int **a = new int*[n];
    int *b = new int[n*m];

    for(int i = 0; i < n; i++)
        a[i] = new int[m];

    cout << "Enter elements: " << endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            cin >> a[i][j];
            b[k++] = a[i][j];
        }

    sortAscending(b, n*m);

    int i = 0, j = 0, col = m, row = n, cnt = 0;
    
    while(cnt < n*m)
    {
        for(int u = j; u < col; u++)
            a[i][u] = b[cnt++];
        if(cnt == n*m)
            break;
        i++;

        for(int v = i; v < row; v++)
            a[v][col-1] = b[cnt++];
        if(cnt == n*m)
            break;
        col--;

        for(int u = col - 1; u >= j; u--)
            a[row-1][u] = b[cnt++];
        if(cnt == n*m)
            break;
        row--;

        for(int v = row - 1; v >= i; v--)
            a[v][j] = b[cnt++];
        j++;
    }

    cout << endl << "After sort an arbitrary two-dimensional array in spiral:" << endl;
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cout << a[i][j] << ' ';
            if(a[i][j] < 10)
                cout << ' ';
        }
        cout << endl;
    }

    for(int i = 0; i < n; i++)
        delete []a[i];
    delete []a;
    delete []b;
    return 0;
}