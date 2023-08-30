#include <iostream>
using namespace std;

// MTK -> DSC

int n;
int a[100][100];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> a[i][j];

    cout << endl;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(a[i][j] == 1 && i < j)
                cout << i << ' ' << j << endl;

    return 0;
}

/*
5
0 1 1 1 0 
1 0 1 1 1 
1 1 0 1 1 
1 1 1 0 1 
0 1 1 1 0 
*/