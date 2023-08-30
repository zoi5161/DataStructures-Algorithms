#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Person 
{
    string name;
    string birthday;
};

struct TreeNode 
{
    Person data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* insert(TreeNode* root, const Person& person) 
{
    if (root == nullptr) 
    {
        root = new TreeNode();
        root -> data = person;
        root -> left = nullptr;
        root -> right = nullptr;
    } 
    else if (person.name < root -> data.name)
        root -> left = insert(root -> left, person);
    else
        root -> right = insert(root -> right, person);
    return root;
}

TreeNode* findMin(TreeNode* node) 
{
    while (node -> left != nullptr)
        node = node -> left;
    return node;
}

TreeNode* remove(TreeNode* root, const string& name) 
{
    if (root == nullptr)
        return nullptr;
    else if (name < root -> data.name)
        root -> left = remove(root -> left, name);
    else if (name > root -> data.name)
        root -> right = remove(root -> right, name);
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
        TreeNode* temp = findMin(root -> right);
        root -> data = temp -> data;
        root -> right = remove(root -> right, temp -> data.name);
    }
    return root;
}

void search(TreeNode* root, const string& name) 
{
    if (root == nullptr) 
    {
        cout << "Person not found." << endl;
        return;
    }
    if (name == root -> data.name)
        cout << "Name: " << root -> data.name << ", Birthday: " << root -> data.birthday << endl;
    else if (name < root -> data.name)
        search(root -> left, name);
    else
        search(root -> right, name);
}

void listAll(TreeNode* root) 
{
    if (root != nullptr) 
    {
        listAll(root -> left);
        cout << "Name: " << root -> data.name << ", Birthday: " << root -> data.birthday << endl;
        listAll(root -> right);
    }
}

void saveToFile(TreeNode* root, ofstream& file) 
{
    if (root != nullptr) 
    {
        saveToFile(root -> left, file);
        file << root -> data.name << "," << root -> data.birthday << "\n";
        saveToFile(root -> right, file);
    }
}

int main() 
{
    TreeNode* database = nullptr;

    // Load data from file if needed

    int choice;
    do 
    {
        cout << "\n1. Add Person\n2. Remove Person\n3. Search Person\n4. List All\n5. Save to File\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                Person person;
                cout << "Enter name: ";
                cin >> person.name;
                cout << "Enter birthday: ";
                cin >> person.birthday;
                database = insert(database, person);
                break;
            }
            case 2: 
            {
                string name;
                cout << "Enter name to remove: ";
                cin >> name;
                database = remove(database, name);
                break;
            }
            case 3: 
            {
                string name;
                cout << "Enter name to search: ";
                cin >> name;
                search(database, name);
                break;
            }
            case 4:
                cout << "Listing all people:\n";
                listAll(database);
                break;
            case 5: 
            {
                ofstream outputFile("database.txt");
                if (outputFile.is_open()) 
                {
                    saveToFile(database, outputFile);
                    outputFile.close();
                    cout << "Data saved to file.\n";
                } 
                else 
                    cout << "Unable to open file for saving.\n";
                break;
            }
            case 6:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 6);

    // Clean up the binary search tree (free memory) if needed

    return 0;
}