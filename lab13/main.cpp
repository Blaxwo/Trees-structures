#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct TreeNode {
    int data;
    int priority;
    TreeNode *parent;
    TreeNode *leftChild;
    TreeNode *rightChild;

    TreeNode(int value, int priority) : data(value), priority(priority), leftChild(nullptr), rightChild(nullptr), parent(nullptr){}
};

class Tree {
public:
    Tree() : root(nullptr) {}

    void split(TreeNode* current, int value, TreeNode*& left, TreeNode*& right) {
        if (current == nullptr) {
            left = right = nullptr;
        } else if (value < current->data) {
            split(current->leftChild, value, left, current->leftChild);
            right = current;
        } else {
            split(current->rightChild, value, current->rightChild, right);
            left = current;
        }
    }

    void merge(TreeNode* left, TreeNode* right, TreeNode*& result) {
        if (left == nullptr) {
            result = right;
        } else if (right == nullptr) {
            result = left;
        } else if (left->priority > right->priority) {
            merge(left->rightChild, right, left->rightChild);
            result = left;
        } else {
            merge(left, right->leftChild, right->leftChild);
            result = right;
        }
    }

    void addNode(int value) {
        int priority = rand() % 50;
        TreeNode* newNode = new TreeNode(value, priority);
        TreeNode *left, *right;
        split(root, value, left, right);
        newNode->leftChild = newNode->rightChild = nullptr;

        merge(left, newNode, left);
        merge(left, right, root);

        if (newNode->leftChild != nullptr) {
            newNode->leftChild->parent = newNode;
        }
        if (newNode->rightChild != nullptr) {
            newNode->rightChild->parent = newNode;
        }
    }
    void deleteNode(int value) {
        root = deleteNode(root, value);
    }

    TreeNode* deleteNode(TreeNode* current, int value) {
        if (!current) {
            return current;
        }
        if (value < current->data) {
            current->leftChild = deleteNode(current->leftChild, value);
        } else if (value > current->data) {
            current->rightChild = deleteNode(current->rightChild, value);
        } else {
            TreeNode* temp;
            merge(current->leftChild, current->rightChild, temp);
            delete current;
            return temp;
        }
        return current;
    }

    void printTree(TreeNode *node, int level = 0) {
        if (node == nullptr) {
            return;
        }
        printTree(node->rightChild, level + 1);

        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << node->data <<"("<<node->priority<<")"<< endl;

        printTree(node->leftChild, level + 1);
    }

    TreeNode *getRoot() {
        return root;
    }

private:
    TreeNode *root;

};

int main() {
    time_t t;
    srand((unsigned) time(&t));
    int choice;
    Tree tree;
    do {
        cout << "Menu:" << endl;
        cout << "1. Add" << endl;
        cout << "2. Remove" << endl;
        cout << "3. Print" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int element;
                cout << "Input element to add: ";
                cin >> element;
                tree.addNode(element);
                break;
            }
            case 2: {
                int element;
                cout << "Input element to delete: ";
                cin >> element;
                tree.deleteNode(element);
                break;
            }
            case 3: {
                cout << "Tree: " << endl;
                tree.printTree(tree.getRoot());
                cout << endl;
                break;
            }

            case 4: {
                cout << "Ending program" << endl;
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}