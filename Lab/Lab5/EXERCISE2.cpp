#include <iostream>
#include <fstream>

using namespace std;

int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[8] = {1, -1, 0, 1, -1, 1, -1, 0};

void ConvertFromCell(int a[][10], int b[][10])
{
    int u, v, cnt;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cnt = 0;
            for(int o = 0; o < 8; o++)
            {
                u = i + dx[o];
                v = j + dy[o];
                if(a[u][v] && u >= 0 && v >= 0 && u < 10 && v < 10)
                    cnt++;
            }
            b[i][j] = cnt;
        }
    }
}

void ChangeToCell(int a[][10], int b[][10])
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(b[i][j] == 0 || b[i][j] == 1 || b[i][j] >= 4)
                a[i][j] = 0;
            else if(b[i][j] == 3)
                a[i][j] = 1;
        }
    }
}

void GetBase(int a[][10], int base[][10])
{
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            base[i][j] = a[i][j];
}

bool Same(int a[][10], int base[][10])
{
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(a[i][j] != base[i][j])
                return false;
    return true;
}

bool Die(int a[][10])
{
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(a[i][j] != 0)
                return false;
    return true;
}

void Print(int b[][10])
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
            cout << b[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
}

void Process(int &T, int base[][10], int a[][10], int b[][10])
{
    ifstream fin("cell.txt");
    if(fin.is_open())
    {
        string s, tmp = "";
        int k, n = 1;

        getline(fin, s);
        T = stoi(s);

        while(n <= T)
        {
            getline(fin, s);
            for(int i = 0; i < 10; i++)
            {
                k = 0;
                getline(fin, s);
                for(int j = 0; j < s.length(); j++)
                {
                    if(s[j] != ' ')
                    {
                        tmp += s[j];
                        a[i][k++] = stoi(tmp);
                        tmp = "";
                    }
                    if(k == 10)
                        break;
                }
            }

            GetBase(a, base);
            ConvertFromCell(a, b);

            cout << "- - - - - - - - - - - - -" << endl;
            cout << "Test " << n << ':' << endl;
            Print(b);

            cout << "Output: " << endl;
            while(true)
            {
                ChangeToCell(a, b);
                ConvertFromCell(a, b);

                if(Die(a))
                {
                    cout << "All Dead" << endl << endl;
                    break;
                }

                Print(b);
                if(Same(a, base))
                    break;
            }
            
            n++;
        }
        fin.close();
    }
    else
        cout << "Can't open file";
}

int main()
{
    int T;
    int a[10][10];
    int b[10][10];
    int base[10][10];

    Process(T, base, a, b);
    return 0;
}