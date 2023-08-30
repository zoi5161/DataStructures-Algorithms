#include <iostream>
#include <fstream>
#include <iomanip>

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
    ifstream fin("/Users/macos/Downloads/Cấu trúc dữ liệu & Giải thuật/Lab1/EXERCISE1.9/input1.9.bin", ios::binary);

    if(fin.is_open())
    {   
        Student student[1000];

        fin.seekg(0, ios::end);
        int file_size = fin.tellg();
        fin.seekg(0, ios::beg);
        int n = file_size / 166;

        for(int i = 1; i <= n; i++)
        {
                fin.read(student[i].name, 30);
                fin.read((char*)&student[i].birth.date, 4);
                fin.read((char*)&student[i].birth.month, 4);
                fin.read((char*)&student[i].birth.year, 4);
                fin.read(student[i].address, 100);
                fin.read(student[i].cla, 20);
                fin.read((char*)&student[i].id, 4);
        }   

        for(int i = 1; i <= n; i++)
        {
            cout << "  - - - - - - - - - - - - - - - - - - " << endl;
            cout << "  Student " << i << endl;
            cout << "  Name: " << student[i].name << endl;
            cout << "  Birthday: " << student[i].birth.date << '-' << student[i].birth.month << '-' << student[i].birth.year << endl;
            cout << "  Address: " << student[i].address << endl;
            cout << "  Class: " << student[i].cla << endl;
            cout << "  Id: " << student[i].id << endl;
            cout << "  - - - - - - - - - - - - - - - - - - " << endl << endl;
        }
        fin.close();
    }
    else 
        cout << "Can't open file";
    return 0;
}