#include <iostream>
#include <vector>
using namespace std;

// MTK -> DSK

int n, x;
vector <int> adj[100];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cin >> x;
            if(x == 1)
                adj[i].push_back(j);
        }
    }

    cout << endl;
    for(int i = 1; i <= n; i++)
    {
        cout << i << " : ";
        for(int j = 0; j < adj[i].size(); j++)
            cout << adj[i][j] << ' ';
        cout << endl;
    }
    
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