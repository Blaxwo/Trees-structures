#include <iostream>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *parent;
    TreeNode *leftChild;
    TreeNode *rightChild;

    TreeNode(int value) : data(value), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}
};

class Tree {
public:
    Tree() : root(nullptr) {}

    TreeNode *findNode(TreeNode *current, int value) {
        if (current == nullptr) {
            return nullptr;
        }

        if (current->data == value) {
            return current;
        }
        TreeNode *sibling = nullptr;
        if (value > current->data) {
            sibling = current->rightChild;
        }
        if (value < current->data) {
            sibling = current->leftChild;
        }
        while (sibling != nullptr) {
            TreeNode *result = findNode(sibling, value);
            if (result) {
                return result;
            }
            break;
        }
        return nullptr;
    }

    void addNode(int value) {
        root = addNodeRecursive(root, value);
    }

    TreeNode *addNodeRecursive(TreeNode *current, int value, TreeNode *parent = nullptr) {
        if (current == nullptr) {
            TreeNode *newNode = new TreeNode(value);
            newNode->parent = parent;
            return newNode;
        }

        if (value > current->data) {
            current->rightChild = addNodeRecursive(current->rightChild, value, current);
        } else if (value < current->data) {
            current->leftChild = addNodeRecursive(current->leftChild, value, current);
        } else {
            current->rightChild = addNodeRecursive(current->rightChild, value, current);
        }
        return current;
    }

    TreeNode *getRoot() {
        return root;
    }

    void deleteNode(int value) {
        TreeNode *elementToDelete = findNode(root, value);
        root = deleteFoundedNode(elementToDelete);
    }

    TreeNode* deleteFoundedNode(TreeNode* element) {
        while (element != nullptr) {
            if (element->rightChild == nullptr && element->leftChild == nullptr) {
                // Node has no children
                if (element->parent != nullptr) {
                    if (element->parent->data > element->data) {
                        element->parent->leftChild = nullptr;
                    } else {
                        element->parent->rightChild = nullptr;
                    }
                } else {
                    root = nullptr;  // Update root if deleting the root node
                }
                delete element;
                break;
            } else if (element->rightChild != nullptr && element->leftChild != nullptr) {
                // Node has both left and right children
                TreeNode* successor = findMin(element->rightChild);
                element->data = successor->data;
                element = successor;
            } else {
                // Node has only one child
                TreeNode* child = (element->leftChild != nullptr) ? element->leftChild : element->rightChild;
                if (element->parent != nullptr) {
                    if (element->parent->data > element->data) {
                        element->parent->leftChild = child;
                    } else {
                        element->parent->rightChild = child;
                    }
                    child->parent = element->parent;
                } else {
                    root = child;
                    child->parent = nullptr;
                }
                delete element;
                break;
            }
        }
        return root;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->leftChild != nullptr) {
            node = node->leftChild;
        }
        return node;
    }

    void printTree(TreeNode *node, int level = 0) {
        if (node == nullptr) {
            return;
        }
        printTree(node->rightChild, level + 1);

        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << node->data << endl;

        printTree(node->leftChild, level + 1);
    }


private:
    TreeNode *root;
};

int main() {
    int choice;
    Tree tree;
    do {
        cout << "Menu:" << endl;
        cout << "1. Add" << endl;
        cout << "2. Remove" << endl;
        cout << "3. Print" << endl;
        cout << "4. Find" << endl;
        cout << "5. Exit" << endl;
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
                if (tree.findNode(tree.getRoot(), element) != nullptr) {
                    tree.deleteNode(element);
                } else {
                    cout << "There is no such element in tree" << endl;
                }
                break;
            }
            case 3: {
                cout << "Tree: " << endl;
                tree.printTree(tree.getRoot());
                cout << endl;
                break;
            }
            case 4: {
                int element;
                cout << "Input element to find: " << endl;
                cin >> element;
                cout << "Founded node: ";
                if (tree.findNode(tree.getRoot(), element) != nullptr) {
                    cout << tree.findNode(tree.getRoot(), element)->data << endl;
                } else {
                    cout << "There is no such element in tree" << endl;
                }
                break;
            }

            case 5: {
                cout << "Ending program" << endl;
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}
