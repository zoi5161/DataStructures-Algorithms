#include <iostream>
#include <vector>

using namespace std;

vector <int> ds[100];
vector <int> res;
bool visited[100];
int a, b, n, k;

void DFS(int x)
{
    visited[x] = true;
    res.push_back(x);
    for(int i = 0; i < ds[x].size(); i++)
        if(!visited[ds[x][i]])
            DFS(ds[x][i]);
}

int main()
{
    cin >> n >> k;
    for(int i = 1; i <= k; i++)
    {
        cin >> a >> b;
        ds[a].push_back(b);
        //ds[b].push_back(a); // Vô hướng
    }

    memset(visited, false, sizeof(visited));

    DFS(1);

    cout << endl;
    for(int i = 0; i < res.size(); i++)
        cout << res[i] << ' ';
    return 0;
}

/*
Vô hướng DFS(2)
9 9
1 2
1 3
1 5
2 4
3 6
3 7
3 9
5 8
8 9

2 1 3 6 7 9 5 8 1
*/

/*
Có hướng DFS(1)
9 9
1 2
1 3
1 5
2 4
3 6
3 7
5 8
8 9
9 3

1 2 4 3 6 7 5 8 9
*/