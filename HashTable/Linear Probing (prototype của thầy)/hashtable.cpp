#include <iostream>
using namespace std;

int Hash(int x, int n){
    return x%n;
}

//x: non-zero value, a[i]==0: occupied
//enough slots for new numbers
//insert x into the HashTable
//return the index of the slot inserted
//collision resolution: Linear Probing

int insert(int* a, int n, int x)
{
    int index = Hash(x, n);
    while(a[index] != 0 && a[index] != x)
        index = Hash(index + 1, n);
    if(a[index] == 0)
    {
        a[index] = x;
        return index;
    }
    return -1;
}

//search for x from a Hash Table
//return the index where x is. -1 if not found
int SearchHash(int* a, int n, int x)
{
    int index = Hash(x, n);
    while(a[index] != 0 && a[index] != x)
        index = Hash(index + 1, n);
    if(a[index] == x)
        return index;
    return -1;
}