#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin;
    string s, note;
    int k, n;

    cin >> k >> n >> s;
    fin.open(s + ".txt");

    if(fin.is_open())
    {
        if(k == 0)
            getline(fin, note, '\n');
        else
            while(!fin.eof())
                getline(fin, note, '\n');
        for(int i = 1; i <= n; i++)
            cout << note << endl;
        fin.close();
    }
    else
        cout << "Can't open file";
    return 0;
}