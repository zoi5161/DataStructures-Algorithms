#include <iostream>
#include <sstream>
#include <vector>
#define ii pair<int, int>
using namespace std;

// DSK -> DSC
int n;
vector <ii> edge;
string s, num;

int main()
{
    cin >> n;
    cin.ignore();
    for(int i = 1; i <= n; i++)
    {
        getline(cin, s);
        stringstream ss(s);
        while(ss >> num)
            if(i < stoi(num))
                edge.push_back({i, stoi(num)});
    }
    for(int i = 0; i < edge.size(); i++)
        cout << edge[i].first << ' ' << edge[i].second << endl;
    return 0;
}
/*
5
2 3 4
1 3 4 5
1 2 4 5
1 2 3 5
2 3 4
*/