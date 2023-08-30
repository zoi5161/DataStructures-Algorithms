// Trần Gia Bảo
// 22127034
// Nhung cau da lam duoc: Cau 2-a,c,d

#include <iostream>

using namespace std;

struct BSTNode 
{ 
    int key;
    BSTNode* pLeft;
    BSTNode* pRight;
};

struct Tree
{
    int Count;
    BSTNode pRoot;
};

BSTNode* CreateNode(int x)
{
    BSTNode* tmp = new BSTNode;
    tmp -> key = x;
    tmp -> pLeft = nullptr;
    tmp -> pRight = nullptr;
    return tmp;
}

bool Insert(BSTNode* &pCur, int x)
{
    if(pCur == nullptr)
    {
        pCur = CreateNode(x);
        return true;
    }
    
    if(pCur -> key > x)
        return Insert(pCur -> pLeft, x);
    else if(pCur -> key < x)
        return Insert(pCur -> pRight, x);
    else return false;
}

// BSTNode* FindLine(BSTNode* p, int x, string a[], int &i)
// {
//     if(p == nullptr)
//         return NULL;
    
//     if(p -> key == x)
//     {
//         for(int j = 0; j < i; j++)
//             cout << 
//     }
//     return FindLine(p -> pLeft, x);
//     return FindLine(p -> pRight, x);
// }

void Size(BSTNode* p, int &cnt)
{
    if(p == NULL)
        return;
    
    if(p -> pLeft == NULL && p -> pRight == NULL)
        cnt++;
    Size(p -> pLeft, cnt);
    Size(p -> pRight, cnt);
}

void MxMn(BSTNode* p, int &mx, int &mn)
{
    if(p == NULL)
        return;
    
    if(p -> key > mx)
        mx = p -> key;
    if(p -> key < mn)
        mn = p -> key;

    MxMn(p -> pLeft, mx, mn);
    MxMn(p -> pRight, mx, mn);
}

int main()
{
    int n, x, cnt = 0;
    BSTNode* root = NULL;

    cout << "Nhap vao so luong phan tu ban muon them vao cay: ";
    cin >> n;

    cout << endl << "Nhap cac gia tri ban muon them vao: ";
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        Insert(root, x);
    }
    
    cout << endl << "Nhap vao key can tim duong di: ";
    cin >> x;

    cout << endl << "So node la tren cay la: " << cnt; 

    int mx = INT_MIN;
    int mn = INT_MAX;

    MxMn(root, mx, mn);
    cout << endl << "Max: " << mx;
    cout << endl << "Min: " << mn;
    return 0;
}