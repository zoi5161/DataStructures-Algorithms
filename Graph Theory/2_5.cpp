#include <iostream>
#include <sstream>
using namespace std;

// DSK -> MTK

int n, x;
int a[100][100];
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
            a[i][stoi(num)] = 1;
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
5
2 3 4
1 3 4 5
1 2 4 5
1 2 3 5
2 3 4
*/