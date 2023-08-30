#include <iostream>
#include <fstream>

using namespace std;

int main()
{
ifstream fin1("input1.4.1.txt");
    ifstream fin2("input1.4.2.txt");

    if(fin1.is_open() && fin2.is_open())
    {
        int i = 0, j = 0, flag = 0;
        string s1, s2;
        while(!fin1.eof() || !fin2.eof())
        {
            i++;
            j++;
            s1 = "";
            s2 = "";

            if(fin1.eof())
            {
                getline(fin2, s2, '\n');
                cout << i << "//" << endl;
                cout << j << "\\\\" << s2 << endl << endl;
            }
            else if(fin2.eof())
            {
                getline(fin1, s1, '\n');
                cout << i << "//" << s1 << endl;
                cout << j << "\\\\" << endl << endl;
            }
            else
            {
                getline(fin1, s1, '\n');
                getline(fin2, s2, '\n');
                if(s1.length() == s2.length())
                {
                    for(int k = 0; k < s1.length(); k++)
                    {
                        if(s1[k] != s2[k])
                        {
                            cout << i << "//" << s1 << endl;
                            cout << j << "\\\\" << s2 << endl << endl;
                            break;
                        }
                    }
                }
                else
                {
                    cout << i << "//" << s1 << endl;
                    cout << j << "\\\\" << s2 << endl << endl;
                }
            }
        }
        fin1.close();
        fin2.close();
    }
    else
        cout << "Can't open file";
    return 0;
}