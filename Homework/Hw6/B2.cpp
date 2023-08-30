#include <iostream>

using namespace std;

struct TreeNode 
{
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : key(value), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int value) 
{
    if (root == nullptr)
        return new TreeNode(value);

    if (value < root -> key)
        root -> left = insert(root -> left, value);
    else if (value > root -> key)
        root -> right = insert(root -> right, value);

    return root;
}

bool isEmpty(TreeNode* root) 
{
    return root == nullptr;
}

int getHeight(TreeNode* root) 
{
    if (root == nullptr)
        return -1;
    return 1 + max(getHeight(root -> left), getHeight(root -> right));
}

int getNodeCount(TreeNode* root) 
{
    if (root == nullptr)
        return 0;
    return 1 + getNodeCount(root -> left) + getNodeCount(root -> right);
}

int getRootData(TreeNode* root) 
{
    if (root != nullptr)
        return root -> key;
    return -1;
}

TreeNode* findMinValueNode(TreeNode* node) 
{
    while (node -> left != nullptr)
        node = node -> left;
    return node;
}

TreeNode* remove(TreeNode* root, int value) 
{
    if (root == nullptr)
        return nullptr;

    if (value < root -> key)
        root -> left = remove(root -> left, value);
    else if (value > root -> key)
        root -> right = remove(root -> right, value);
    else 
    {
        if (root -> left == nullptr) 
        {
            TreeNode* temp = root -> right;
            delete root;
            return temp;
        } 
        else if (root -> right == nullptr) 
        {
            TreeNode* temp = root -> left;
            delete root;
            return temp;
        }

        TreeNode* minValueNode = findMinValueNode(root -> right);
        root -> key = minValueNode -> key;
        root -> right = remove(root -> right, minValueNode -> key);
    }

    return root;
}

bool contains(TreeNode* root, int value) 
{
    if (root == nullptr)
        return false;

    if (root -> key == value)
        return true;
    else if (value < root -> key)
        return contains(root -> left, value);
    else
        return contains(root -> right, value);
}

void traversePreOrder(TreeNode* root) 
{
    if (root != nullptr) 
    {
        cout << root -> key << " ";
        traversePreOrder(root -> left);
        traversePreOrder(root -> right);
    }
}

void traverseInOrder(TreeNode* root) 
{
    if (root != nullptr) 
    {
        traverseInOrder(root -> left);
        cout << root -> key << " ";
        traverseInOrder(root -> right);
    }
}

void traversePostOrder(TreeNode* root) 
{
    if (root != nullptr) 
    {
        traversePostOrder(root -> left);
        traversePostOrder(root -> right);
        cout << root -> key << " ";
    }
}

void removeAll(TreeNode* root) 
{
    if (root == nullptr)
        return;

    removeAll(root -> left);
    removeAll(root -> right);
    delete root;
}

int main() 
{
    TreeNode* root = nullptr;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "In-order traversal: ";
    traverseInOrder(root);
    cout << endl;

    cout << "Pre-order traversal: ";
    traversePreOrder(root);
    cout << endl;

    cout << "Post-order traversal: ";
    traversePostOrder(root);
    cout << endl;

    cout << "Tree height: " << getHeight(root) << endl;
    cout << "Node count: " << getNodeCount(root) << endl;

    cout << "Tree contains 40? " << (contains(root, 40) ? "Yes" : "No") << endl;
    cout << "Tree contains 90? " << (contains(root, 90) ? "Yes" : "No") << endl;

    root = remove(root, 30);
    cout << "In-order traversal after removing 30: ";
    traverseInOrder(root);
    cout << endl;

    removeAll(root);
    cout << "Tree is empty? " << (isEmpty(root) ? "Yes" : "No") << endl;

    return 0;
}
