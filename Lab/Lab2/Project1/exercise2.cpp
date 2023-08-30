#include <iostream>
#include <fstream>
#define MAX 100

using namespace std;

struct Employee
{
    string id;
    string FamilyName;
    string LastName;
    int year;
};

void Input(Employee employee[], int &n)
{
    ifstream fin;
    fin.open("employee.txt");

    if(fin.is_open())
    {
        string s, tmp;
        bool end = false;
        int time, length;

        fin.ignore();
        while(!fin.eof())
        {
            n++;
            getline(fin, s, '\n');
            if(fin.eof())
                end = true;

            if(n == 1)
                continue;
            else
            {
                tmp = "";
                time = 0;
                length = s.length();
                if(end)
                    length++;

                for(int j = 0; j < length - 1; j++)
                {
                    if(s[j] == ',')
                    {
                        if(!time)
                            employee[n-2].id = tmp;
                        else
                        {
                            string name = "";
                            for(int k = 0; k < tmp.length(); k++)
                            {
                                if(tmp[k] == ' ')
                                {
                                    employee[n-2].FamilyName = name;
                                    name = "";
                                }
                                else
                                    name += tmp[k];
                            }
                            employee[n-2].LastName = name;
                        }
                        time++;
                        tmp = "";
                    }
                    else
                        tmp += s[j];
                }
                employee[n-2].year = stoi(tmp);
            }
        }
        n--;
        fin.close();
    }
    else
        cout << "Can't open file.";
}

void Output(Employee employee[], int n)
{
    ofstream fout;
    fout.open("sortedemponage.txt");
    for(int i = 0; i < n - 1; i++)
        fout << employee[i].id << " - " << employee[i].FamilyName << ' ' << employee[i].LastName << " - " << employee[i].year << endl;
    fout << employee[n-1].id << " - " << employee[n-1].FamilyName << ' ' << employee[n-1].LastName << " - " << employee[n-1].year;
    fout.close();
}

bool Compare(Employee a, Employee b)
{
    if (a.year != b.year)
        return a.year > b.year;
    else if (a.LastName != b.LastName)
        return a.LastName > b.LastName;
    else if (a.FamilyName != b.FamilyName)
        return a.FamilyName > b.FamilyName;
    else
        return a.id < b.id;
}

// Heap Sort
void Heapify(Employee a[], int n, int i)
{
    int l = 2*i + 1, r = 2*i + 2, largest = i;

    if(l < n && Compare(a[l], a[largest]))
            largest = l;

    if(r < n && Compare(a[r], a[largest]))
            largest = r;

    if(largest != i)
    {
        swap(a[i], a[largest]);
        Heapify(a, n, largest);
    }
}

void HeapSort(Employee a[], int n)
{
    for(int i = n/2 - 1; i >= 0; i--)
        Heapify(a, n, i);
    
    for(int i = n-1; i >= 1; i--)
    {
        swap(a[0], a[i]);
        Heapify(a, i, 0);
    }
}

// Quick Sort
void QuickSort(Employee a[], int left, int right)
{
    Employee k = a[(right+left)/2];
	int i = left, j = right;
	while(i <= j)
	{
		while(Compare(k, a[i]))
			i++;
		while(Compare(a[j], k))
			j--;
		if(i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	if(left < j)
		QuickSort(a, left, j);
	if(right > i)
		QuickSort(a, i, right);
}

// Merge Sort
void Merge(Employee a[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Employee L[n1];
    Employee R[n2];

    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) 
    {
        if (Compare(R[j], L[i])) 
        {
            a[k] = L[i];
            i++;
        }
        else 
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        a[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(Employee a[], int l, int r)
{
    if(l < r)
    {
        int m = l + (r-l)/2;
        MergeSort(a, l, m);
        MergeSort(a, m+1, r);
        Merge(a, l, m, r);
    }
}

int main()
{
    int n = 0;
    Employee employee[MAX];

    Input(employee, n);
    HeapSort(employee, n);
    QuickSort(employee, 0, n);
    MergeSort(employee, 0, n-1);
    Output(employee, n);
    return 0;
}