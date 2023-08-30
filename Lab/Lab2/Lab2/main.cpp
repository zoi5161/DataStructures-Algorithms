#include <iostream>
#include <fstream>

using namespace std;

// 2.2
struct Birth
{
    int date;
    int month;
    int year;
};

struct Student
{
    int id;
    string FamilyName;
    string Name;
    Birth dOb;
};

Student student[100];
int n = 0;

void Load(string s)
{
    ifstream fin(s + ".txt");
    if(fin.is_open())
    {
        string line, num;
        int i = 0;
        bool flag = false;

        while(!fin.eof())
        {
            getline(fin, line, '\n');
            student[n].id = stoi(line);

            getline(fin, line, '\n');
            student[n].FamilyName = line;

            getline(fin, line, '\n');
            student[n].Name = line;

            getline(fin, line, '\n');
            num = "";
            flag = false;

            for(int j = 0; j < line.length(); j++)
            {
                if(line[j] == '/' && !flag)
                {
                    flag = true;
                    student[n].dOb.date = stoi(num);
                    num = "";
                }
                else if(line[j] == '/')
                {
                    student[n].dOb.month = stoi(num);
                    num = "";
                }
                else 
                    num += line[j];
            }
            student[n].dOb.year = stoi(num);
            n++;

            getline(fin, line, '\n');
        }

        // for(int i = 0; i < n; i++)
        // {
        //     cout << "- - - - - - - - - - - -" << endl;
        //     cout << "       Student " << i << "        "<< endl;
        //     cout << "ID: " << student[i].id << endl;
        //     cout << "Family Name: " << student[i].FamilyName << endl;
        //     cout << "Name: " << student[i].Name << endl;
        //     cout << "Birthday: ";
        //     if(student[i].dOb.date < 10)
        //         cout << 0;
        //     cout << student[i].dOb.date << '/';
        //     if(student[i].dOb.month < 10)
        //         cout << 0;
        //     cout << student[i].dOb.month << '/' << student[i].dOb.year << endl;
        //     cout << "- - - - - - - - - - - -" << endl << endl;
        // }

        fin.close();
    }
    else
        cout << "Can't open file";
}

void Save(string s)
{
    ofstream fout(s + ".txt");
    if(fout.is_open())
    {
        for(int i = 0; i < n; i++)
        {
            fout << student[i].id << endl;
            fout << student[i].FamilyName << endl;
            fout << student[i].Name << endl;
            if(i == n-1)
            {
                if(student[i].dOb.date < 10)
                    fout << 0;
                fout << student[i].dOb.date << '/';
                if(student[i].dOb.month < 10)
                    fout << 0;
                fout << student[i].dOb.month << '/' << student[i].dOb.year;
            }
            else
            {
                if(student[i].dOb.date < 10)
                    fout << 0;
                fout << student[i].dOb.date << '/';
                if(student[i].dOb.month < 10)
                    fout << 0;
                fout << student[i].dOb.month << '/' << student[i].dOb.year << endl;
                fout << endl;
            }
        }
        fout.close();
    }
    else    
        cout << "Can't open file";
}

// 2.3
void BubbleSortName()
{
    for(int i = 1; i < n; i++)
        for(int j = n - 1; j >= i; j--)
        {
            if(student[j].Name < student[j-1].Name)
                swap(student[j], student[j-1]);
            else if (student[j].Name == student[j-1].Name)
                if(student[j].FamilyName < student[j-1].FamilyName)
                    swap(student[j], student[j-1]);
        }
}

void SelectionSortName()
{
    int idx;
    string mnName, mnFamilyName;

    for(int i = 0; i < n - 1; i++)
    {
        mnName = student[i].Name;
        mnFamilyName = student[i].FamilyName;
        idx = i;
        for(int j = i + 1; j < n; j++)
        {
            if(student[j].Name < mnName)
            {
                mnName = student[j].Name;
                idx = j;
            }
            else if(student[j].Name == mnName)
            {
                if(student[j].FamilyName < mnFamilyName)
                {
                    mnFamilyName = student[j].FamilyName;
                    idx = j;
                }
            }
        }
        swap(student[i], student[idx]);
    }
}

void InsertionSortName()
{
    int j;
    Student tmp;

    for(int i = 1; i < n; i++)
    {
        tmp = student[i];
        j = i - 1;
        while(j >= 0)
        {
            if(student[j].Name < tmp.Name)
                break;
            else if(student[j].Name == tmp.Name)
                if(student[j].FamilyName < tmp.FamilyName)
                    break;
            student[j+1] = student[j];
            j--;
        }
        student[j+1] = tmp;
    }
}

void InterchangeSortName()
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(student[j].Name < student[i].Name)
                swap(student[j], student[i]);
            else if (student[j].Name == student[i].Name)
                if(student[j].FamilyName < student[i].FamilyName)
                    swap(student[j], student[i]);
        }
    }
}

void ShakerSortName()
{
    int sur = 0, bot = n - 1, k = 0;
    while(sur < bot)
    {
        for(int j = bot; j > sur; j--)
        {
            if(student[j].Name < student[j-1].Name)
            {
                swap(student[j], student[j-1]);
                k = j;
            }
            else if (student[j].Name == student[j-1].Name)
                if(student[j].FamilyName < student[j-1].FamilyName)
                {
                    swap(student[j], student[j+1]);
                    k = j;
                }
        }

        sur = k;

        for(int j = sur; j < bot; j++)
        {
            if(student[j].Name > student[j+1].Name)
            {
                swap(student[j], student[j+1]);
                k = j;
            }
            else if (student[j].Name == student[j+1].Name)
                if(student[j].FamilyName > student[j+1].FamilyName)
                {
                    swap(student[j], student[j+1]);
                    k = j;
                }
        }
        bot = k;
    }
}

// 2.4
bool ComparedDoB(Student a, Student b)
{
    if(a.dOb.year > b.dOb.year)
        return true;
    else if((a.dOb.year == b.dOb.year) && (a.dOb.month > b.dOb.month))
        return true;
    else if((a.dOb.year == b.dOb.year) && (a.dOb.month == b.dOb.month) && (a.dOb.date > b.dOb.date))
        return true;
    return false;
}

void BubbleSortDoB()
{
    for(int i = 1; i < n; i++)
        for(int j = n - 1; j >= i; j--)
            if(ComparedDoB(student[j-1], student[j]))
                swap(student[j], student[j-1]);
}

void SelectionSortDoB()
{
    int idx;
    Student tmp;

    for(int i = 0; i < n - 1; i++)
    {
        tmp = student[i];
        idx = i;

        for(int j = i + 1; j < n; j++)
        {
            if(ComparedDoB(tmp, student[j]))
            {
                tmp = student[j];
                idx = j;
            }
        }
        swap(student[i], student[idx]);
    }
}

void InsertionSortDoB()
{
    int j;
    Student tmp;

    for(int i = 1; i < n; i++)
    {
        tmp = student[i];
        j = i - 1;
        while(j >= 0)
        {
            if(ComparedDoB(tmp, student[j]))
                break;
            student[j+1] = student[j];
            j--;
        }
        student[j+1] = tmp;
    }
}

void InterchangeSortDoB()
{
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(ComparedDoB(student[i], student[j]))
                swap(student[j], student[i]);
}

void ShakerSortDoB()
{
    int sur = 0, bot = n - 1, k = 0;
    while(sur < bot)
    {
        for(int j = bot; j > sur; j--)
            if(ComparedDoB(student[j-1], student[j]))
            {
                swap(student[j], student[j-1]);
                k = j;
            }
        sur = k;

        for(int j = sur; j < bot; j++)
            if(ComparedDoB(student[j], student[j+1]))
            {
                swap(student[j], student[j+1]);
                k = j;
            }
        bot = k;
    }
}

int main()
{
    Load("class");

    // 2.3
    
    // BubbleSortName();
    // SelectionSortName();
    // InsertionSortName();
    // InterchangeSortName();
    // ShakerSortName();

    // 2.4

    // BubbleSortDoB();
    // SelectionSortDoB();
    // InsertionSortDoB();
    // InterchangeSortDoB();
    // ShakerSortDoB();
    Save("save");
    return 0;
}