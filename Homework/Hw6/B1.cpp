#include <iostream>
#include <vector>

using namespace std;

const int MAX_NODES = 1000;

int tree[MAX_NODES];
int treeSize = 0;

// Initialize the tree
void initializeTree() 
{
    for (int i = 0; i < MAX_NODES; ++i)
        tree[i] = -1;
    treeSize = 0;
}

// Test whether the tree is empty
bool isEmpty() 
{
    return treeSize == 0;
}

// Get the height of the tree
int getHeight(int index = 0) 
{
    if (index >= treeSize || tree[index] == -1)
        return 0;
    int leftHeight = getHeight(2 * index + 1);
    int rightHeight = getHeight(2 * index + 2);
    return 1 + max(leftHeight, rightHeight);
}

// Get the number of nodes in the tree
int getNodeCount() 
{
    return treeSize;
}

// Get the data in the root of the tree
int getRoot() 
{
    if (isEmpty())
        return -1;
    return tree[0];
}

// Insert a new item into the tree
void insert(int data, int index = 0) 
{
    if (index >= MAX_NODES)
        return; 

    if (tree[index] == -1) 
    {
        tree[index] = data;
        treeSize++;
    } 
    else if (data < tree[index])
        insert(data, 2 * index + 1);
    else
        insert(data, 2 * index + 2);
}

// Helper function to find the minimum value in the tree
int findMin(int index) 
{
    if (tree[2 * index + 1] == -1)
        return tree[index];
    return findMin(2 * index + 1);
}

// Remove a specific entry from the tree
void remove(int data, int index = 0) 
{
    if (index >= treeSize || tree[index] == -1)
        return;

    if (data < tree[index])
        remove(data, 2 * index + 1);
    else if (data > tree[index])
        remove(data, 2 * index + 2);
    else 
    {
        if (tree[2 * index + 1] == -1 && tree[2 * index + 2] == -1) 
        {
            tree[index] = -1;
            treeSize--;
        }
        else if (tree[2 * index + 1] == -1) 
        {
            tree[index] = tree[2 * index + 2];
            remove(tree[2 * index + 2], 2 * index + 2);
        }
        else if (tree[2 * index + 2] == -1) 
        {
            tree[index] = tree[2 * index + 1];
            remove(tree[2 * index + 1], 2 * index + 1);
        }
        else 
        {
            int minValue = findMin(2 * index + 2);
            tree[index] = minValue;
            remove(minValue, 2 * index + 2);
        }
    }
}

// Remove all entries from the tree
void removeAll() 
{
    initializeTree();
}

// Retrieve a specific item from the tree
bool retrieve(int data, int index = 0) 
{
    if (index >= treeSize || tree[index] == -1)
        return false;
    
    if (data == tree[index])
        return true;
    else if (data < tree[index])
        return retrieve(data, 2 * index + 1);
    else
        return retrieve(data, 2 * index + 2);
}

// Test whether the tree contains a specific entry
bool contains(int data) 
{
    return retrieve(data);
}

// Pre-order
void preOrder(int index = 0) 
{
    if (index >= treeSize || tree[index] == -1)
        return;
    
    cout << tree[index] << " ";
    preOrder(2 * index + 1); 
    preOrder(2 * index + 2); 
}

// In-order
void inOrder(int index = 0) 
{
    if (index >= treeSize || tree[index] == -1)
        return;
    
    inOrder(2 * index + 1); 
    cout << tree[index] << " ";
    inOrder(2 * index + 2); 
}

// Post-order
void postOrder(int index = 0) 
{
    if (index >= treeSize || tree[index] == -1)
        return;
    
    postOrder(2 * index + 1); 
    postOrder(2 * index + 2);
    cout << tree[index] << " ";
}

int main() 
{
    initializeTree();
    
    insert(5);
    insert(3);
    insert(7);
    insert(2);
    insert(4);
    insert(6);
    insert(8);
    
    cout << "Tree: " << endl;
    cout << "          5" << endl;
    cout << "      3       7" << endl;
    cout << "    2   4   6   8" << endl << endl;
    
    cout << "Pre-order traversal: ";
    preOrder();
    cout << endl;
    
    cout << "In-order traversal: ";
    inOrder();
    cout << endl;
    
    cout << "Post-order traversal: ";
    postOrder();
    cout << endl;

    return 0;
}

/*
Tree:
          5
      3       7
    2   4   6   8
*/