#include <iostream>
#include <vector>
using namespace std;

// DSC -> DSK

int n, k, a, b;
vector <int> adj[100];

int main()
{
    cin >> n >> k;
    for(int i = 1; i <= k; i++)
    {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
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