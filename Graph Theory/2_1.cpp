#include <iostream>
using namespace std;

// DSC -> MTK

int n, k, b, c;
int a[100][100];

int main()
{
    cin >> n >> k;
            
    for(int i = 1; i <= k; i++)
    {
        cin >> b >> c;
        a[b][c] = 1;
        a[c][b] = 1;
    }

    cout << endl;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
    return 0;
}
/*
5 9
1 2
1 3
1 4
2 3
2 4
2 5
3 4
3 5
4 5
*/