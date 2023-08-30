#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Birth 
{
    int date, month, year; // 4x3 = 12
};

struct Student // 166
{
    char name[30]; // 30
    Birth birth; // 12
    char address[100]; // 100
    char cla[20]; // 20
    int id; // 4
};

int main()
{
    ifstream fin("input1.9.bin", ios::binary);

    Student student[1000];
    bool stop = false;

    if(fin.is_open())
    {
        fin.seekg(0, ios::end);
        int file_size = fin.tellg();
        fin.seekg(0, ios::beg);
        fin.close();

        int n = file_size / 166;
        ofstream fout("input1.9.bin", ios::binary | ios::app);

        while(!stop)
        {
            cout << endl << "- - - - - - - - - - -" << endl;
            cout << "Your option: Create, Stop." << endl;
            cout << "Your choice: ";

            string s;
            cin >> s;

            for(int i = 0; i < s.length(); i++)
                s[i] = toupper(s[i]);

            if(s == "CREATE")
            {
                cout << endl << "- - - - - - - - - - -" << endl;
                cout << "Name: ";

                string f;
                cin.ignore();
                getline(cin, f, '\n');
                strcpy(student[n].name, f.c_str());

                cout << "Birthday (DD/MM/YYYY): ";
                string k, num = "";
                int flag = 0;
                cin >> k;

                for(int i = 0; i < k.length(); i++)
                {
                    if(k[i] == '/' && flag == 0)
                    {
                        flag++;
                        student[n].birth.date = stoi(num);
                        num = "";
                    }
                    else if(k[i] == '/')
                    {
                        student[n].birth.month = stoi(num);
                        num = "";
                    }
                    else
                        num += k[i];
                }
                student[n].birth.year = stoi(num);

                cout << "Address: ";
                cin.ignore();
                getline(cin, f, '\n');
                strcpy(student[n].address, f.c_str());
                

                cout << "Class: ";
                cin.ignore();
                getline(cin, f, '\n');
                strcpy(student[n].cla, f.c_str());
                

                cout << "ID: ";
                cin >> student[n].id;

                fout.seekp(0, ios::end);
                fout.write(student[n].name, 30);
                fout.write((char*)&student[n].birth.date, 4);
                fout.write((char*)&student[n].birth.month, 4);
                fout.write((char*)&student[n].birth.year, 4);
                fout.write(student[n].address, 100);
                fout.write(student[n].cla, 20);
                fout.write((char*)&student[n].id, 4);

                cout << endl << "Account successfully created!";
            }
            else
                stop = true;
        }
        fout.close();
    }
    else
        cout << "Can't open file";
    return 0;
}