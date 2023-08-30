#include <iostream>
#include <fstream>

using namespace std;

struct Student
{
    int id;
    string name;
    string birth;
    bool graduate;

    Student* Left;
    Student* Right;
};

Student* CreateStudent(Student* x)
{
    Student* p = new Student;
    p -> id = x -> id;
    p -> name = x -> name;
    p -> birth = x -> birth;
    p -> graduate = x -> graduate;
    p -> Left = NULL;
    p -> Right = NULL;
    return p;
}

// Add
bool Add(Student* &p, Student* x)
{
    if(p == NULL)
    {
        p = CreateStudent(x);
        return true;
    }
    if(p -> id > x -> id)
        return Add(p -> Left, x);
    else if(p -> id < x -> id)
        return Add(p -> Right, x);
    else
        return false;
}

// Update
bool Update(Student* &p, Student* x, int i)
{
    if(p == NULL)
        return false;

    if(p -> id < i)
        return Update(p -> Right, x, i);
    else if(p -> id > i)
        return Update(p -> Left, x, i);
    else
    {
        p -> id = x -> id;
        p -> name = x -> name;
        p -> birth = x -> birth;
        p -> graduate = x -> graduate;
        return true;
    }

}

// Find
bool Find(Student* p, int x)
{
    if(p == NULL)
        return false;

    if(p -> id < x)
        return Find(p -> Right, x);
    else if(p -> id > x)
        return Find(p -> Left, x);
    else
        return true;
}

// List sorted name
void GetList(Student* root, Student* a[], int &i)
{
    if(root == NULL)
        return;
    
    a[i++] = root;
    GetList(root -> Left, a, i);
    GetList(root -> Right, a, i);
}

void ListSortedName(Student* p, Student* a[], int n)
{
    int i = 0;
    GetList(p, a, i);

    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(a[i] -> name > a[j] -> name)
                swap(a[i], a[j]);
}

// List graduates
int GetNumGraduates(Student* p, int n)
{
    Student* a[n];
    int i = 0, m = 0;
    GetList(p, a, i);

    for(int i = 0; i < n; i++)
        if(a[i] -> graduate)
            m++;
    
    return m;
}

void ListGraduates(Student* p, Student* b[], int m, int n)
{
    Student* a[n];
    int i = 0, j = 0;
    GetList(p, a, i);

    for(int i = 0; i < n; i++)
        if(a[i] -> graduate)
            b[j++] = a[i];
}

// Delete a student
Student* SearchStandFor(Student* &p, Student* pCur)
{
    if(p -> Right != NULL)
        return SearchStandFor(p -> Right, pCur);

    pCur -> id = p -> id;
    pCur -> name = p -> name;
    pCur -> birth = p -> birth;
    pCur -> graduate = p -> graduate;
    Student* tmp = p;
    p = p -> Left;
    return tmp;
}

bool DeleteStudent(Student* &p, int x)
{
    if(p == NULL)
        return false;
    if(p -> id < x)
        return DeleteStudent(p -> Right, x);
    else if(p -> id > x)
        return DeleteStudent(p -> Left, x);
    
    Student* tmp = p;
    if(p -> Right == NULL)
        p = p -> Left;
    else if(p -> Left == NULL)
        p = p -> Right;
    else 
        tmp = SearchStandFor(p -> Left, p);
    
    delete tmp;
    return true;
}

// Delete all graduates or save all
Student* DeleteGraduated(Student* p)
{
    if (p == NULL)
        return NULL;

    Student* left = DeleteGraduated(p -> Left);
    Student* right = DeleteGraduated(p -> Right);

    if (p -> graduate)
    {
        delete p;
        return NULL;
    }

    p -> Left = left;
    p -> Right = right;
    return p;
}

void Save(Student* &p, ofstream& fout)
{
    if(p == NULL)
        return;
    
    fout << endl << p -> id << endl;
    fout << p -> name << endl;
    fout << p -> birth << endl;
    fout << p -> graduate;

    Save(p -> Left, fout);
    Save(p -> Right, fout);
}

// Get input
void GetInput(Student* &root, int &n)
{
    fstream file;
    ifstream fin("students.txt");

    if(!fin.is_open())
    {
        file.open("students.txt", ios::out | ios::trunc);
        cout << "Created file !!!";
    }
    else
    {
        string s;
        int i = 0;
        Student* p = new Student;
        bool flag = false;
        root = NULL;

        getline(fin, s);
        if(fin.eof())
            return;
        n = stoi(s);

        while(!fin.eof())
        {
            i++;
            getline(fin, s);
            if(i == 1)
                p -> id = stoi(s);
            else if(i == 2)
                p -> name = s;
            else if(i == 3)
                p -> birth = s;
            else
            {
                if(s == "0")
                    p -> graduate = false;
                else
                    p -> graduate = true;
                Add(root, p);
                i = 0;
            }
        }

        fin.close();
    }
}

// Process
void Process(Student* &root, int &n)
{
    cout << endl << endl << endl << "- - - - - OPTION - - - - -" << endl;
    cout << "1. Insert a new student" << endl;
    cout << "2. Find a student" << endl;
    cout << "3. List all students in order of names" << endl;
    cout << "4. List all graduated students" << endl;
    cout << "5. Delete a student" << endl;
    cout << "6. Delete all graduated student" << endl;
    cout << "7. Save all students into file" << endl;
    cout << "8. Exit" << endl;
    cout << endl << "Your choice (1 -> 8): ";

    int choose;
    cin >> choose;
    cout << endl;

    switch(choose)
    {
        case 1:
        {
            Student* p = new Student;
            string s;

            cout << "Id: ";
            cin >> p -> id;
            cout << "Name: ";
            cin >> p -> name;
            cout << "Birth: ";
            cin >> p -> birth;
            cout << "Status (undergraduated or graduated): ";
            cin >> s;
            for(int i = 0; i < s.length(); i++)
                s[i] = toupper(s[i]);
            if(s == "UNDERGRADUATED" || s == "0")
                p -> graduate = false;
            else if(s == "GRADUATED" || s == "1")
                p -> graduate = true;
            else
            {
                cout << endl << "ERROR";
                break;
            }

            if(Add(root, p))
            {
                cout << endl << "SUCCESSFUL !!!" << endl;
                n++;
            }
            else
                cout << "ID: " << p -> id << " already exists." << endl;
            break;
        }
        case 2:
        {
            int id;
            cout << "Id: ";
            cin >> id;

            if(Find(root, id))
            {
                string s;
                cout << "Student with this id was found. You want to update (Yes or No): ";
                cin >> s;
                for(int i = 0; i < s.length(); i++)
                    s[i] = toupper(s[i]);
                if(s == "YES")
                {
                    Student* p = new Student;

                    cout << "Id change to: ";
                    cin >> p -> id;
                    cout << "Name change to: ";
                    cin >> p -> name;
                    cout << "Birth change to: ";
                    cin >> p -> birth;
                    cout << "Status (undergraduated or graduated) change to: ";
                    cin >> s;
                    for(int i = 0; i < s.length(); i++)
                        s[i] = toupper(s[i]);
                    if(s == "UNDERGRADUATED" || s == "0")
                        p -> graduate = false;
                    else if(s == "GRADUATED" || s == "1")
                        p -> graduate = true;
                    else
                        cout << endl << "ERROR";

                    Update(root, p, id);
                    cout << endl << "SUCCESSFUL !!!" << endl;
                }
            }
            else 
                cout << "Student with this id could not be found." << endl;
            break;
        }
        case 3:
        {
            Student* a[n];
            ListSortedName(root, a, n);
            cout << "List all students sorted by name: " << endl << endl;

            for(int i = 0; i < n; i++)
            {
                cout << "Student " << i << ":" << endl;
                cout << "Id: " << a[i] -> id << endl;
                cout << "Name: " << a[i] -> name << endl;
                cout << "Birth: " << a[i] -> birth << endl;
                cout << "Status: ";
                if(a[i] -> graduate)
                    cout << "Graduated" << endl;
                else 
                    cout << "Undergraduated" << endl;
                cout << endl;
            }
            break;
        }
        case 4:
        {
            int m = GetNumGraduates(root, n);
            Student* b[m];
            ListGraduates(root, b, m, n);
        
            cout << "List all graduated students: " << endl << endl;
            for(int i = 0; i < m; i++)
            {
                cout << "Student " << i+1 << ":" << endl;
                cout << "Id: " << b[i] -> id << endl;
                cout << "Name: " << b[i] -> name << endl;
                cout << "Birth: " << b[i] -> birth << endl;
                cout << "Status: ";
                if(b[i] -> graduate)
                    cout << "Graduated" << endl;
                else 
                    cout << "Undergraduated" << endl;
                cout << endl;
            }
            break;
        }
        case 5:
        {
            int id;
            cout << "Id: ";
            cin >> id;

            if(DeleteStudent(root, id))
            {
                cout << "SUCCESSFUL !!!" << endl;
                n--;
            }
            else
                cout << "Student with this id could not be found." << endl;
            break;
        }
        case 6:
        {
            root = DeleteGraduated(root);
            cout << "SUCCESSFUL !!!" << endl;
            break;
        }
        case 7:
        {
            ofstream fout("students.txt");
            fout << n;
            Save(root, fout);
            cout << endl << "SUCCESSFUL !!!" << endl;
            break;
        }
        case 8:
            return;
        default:
        {
            cout << "Please enter the choices from 1 to 8." << endl;
            break;
        }
    }
    Process(root, n);
}

int main() 
{
    Student* root = new Student;
    int n = 0;

    GetInput(root, n);
    Process(root, n);
    return 0;
}