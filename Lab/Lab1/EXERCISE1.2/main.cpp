#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int gcd(int a, int b)
{
    for(int i = min(a, b); i >= 1; i--)
        if(a % i == 0 && b % i == 0)
            return i;
    return 1;
}

int main()
{
    ifstream fin("input1.2.txt");
    ofstream fout("output1.2.txt");

    string s, k = "";
    int i = 0, n, m, GCD;
    if(fin.is_open())
    {
        while(!fin.eof())
        {
            i++;
            getline(fin, s, '\n');
            if(i != 1)
            {
                for(int j = 0; j < s.length(); j++)
                {
                    if(s[j] == '/')
                    {
                        n = stoi(k);
                        k = "";
                    }
                    else if(s[j] == ' ')
                    {
                        m = stoi(k);
                        GCD = gcd(n, m);
                        k = "";

                        if(m == 0)
                            fout << '~' << ' ';
                        else if(n == 0)
                            fout << 0 << ' ';
                        else if(m/GCD == 1)
                            fout << n/GCD << ' ';
                        else
                            fout << n/GCD << '/' << m/GCD << ' ';
                    }
                    else 
                        k += s[j];
                }

                m = stoi(k);
                GCD = gcd(n, m);
                k = "";

                if(m == 0)
                    fout << '~' << endl;
                else if(n == 0)
                    fout << 0 << endl;
                else if(m/GCD == 1)
                    fout << n/GCD << endl;
                else
                    fout << n/GCD << '/' << m/GCD << endl;
                
            }
        }
        fin.close();
        fout.close();
    }
    else
        fout << "Can't open file";
    return 0;
}