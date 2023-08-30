#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ifstream fin("input1.3.txt");
    ofstream fout("output1.3.txt");

    string s, k = "";
    int i = 0;
    double sum, mx, mn, x;

    if(fin.is_open())
    {
        while(!fin.eof())
        {
            i++;
            getline(fin, s, '\n');
            if(i != 1)
            {
                sum = 0;
                mx = -9999;
                mn = 9999;
                x = 0;

                for(int j = 0; j < s.length(); j++)
                {
                    if(s[j] != ' ' && s[j] != '.')
                        k += s[j];
                    
                    if(s[j] == '.')
                    {
                        x = stoi(k)*10;
                        k = "";
                    }
                    else if(s[j] == ' ' || j == s.length() - 1)
                    {
                        x += stoi(k);
                        x /= 10;

                        sum += x;
                        if(mx < x)
                            mx = x;
                        if(mn > x)
                            mn = x;
                        k = "";
                    }
                }
                fout << fixed << setprecision(1) << mx << "     " << mn << "      " << sum*1.0/12 << endl;
            }
            else
                fout << "Max      Min       Average" << endl;
        }

        fin.close();
        fout.close();
    }
    else
        fout << "Can't open file";

    return 0;
}