#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main()
{
    ifstream fin("input1.8.txt");

    if(fin.is_open())
    {
        string s, up;
        bool flag = false;
        queue <string> ans;

        while(!fin.eof())
        {
            up = "";
            flag = false;
            getline(fin, s, '\n');

            for(int i = 0; i < s.length(); i++)
                if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z' || (s[i] >= '0' && s[i] <= '9')))
                    up += s[i];

            for(int i = 0; i < up.length(); i++)
                up[i] = toupper(up[i]);
            

            for(int i = 0; i < up.length()/2; i++)
                if(up[i] != up[up.length() - i - 1])
                {
                    ans.push("NO");
                    flag = true;
                    break;
                }
            
            if(flag == false)
                ans.push("YES");
        }

        while(!ans.empty())
        {
            cout << ans.front() << endl;
            ans.pop();
        }
        fin.close();
    }
    else
        cout << "Can't open file.";
    return 0;
}