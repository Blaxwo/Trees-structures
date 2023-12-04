#include <iostream>
#include <windows.h>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *parent;
    TreeNode *leftChild;
    TreeNode *rightChild;
    int colorOfTheNode;
    //red-0
    //black-1

    TreeNode(int value) : data(value), leftChild(nullptr), rightChild(nullptr), parent(nullptr), colorOfTheNode(0) {}
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
        if (root == nullptr) {
            root = new TreeNode(value);
            root->parent = nullptr;
            root->colorOfTheNode = 1;
            cout << "Element inserted.\n";
        } else {
            TreeNode *current = root;
            auto *newNode = new TreeNode(value);

            while (current != nullptr) {
                if (value < current->data) {
                    if (current->leftChild == nullptr) {
                        current->leftChild = newNode;
                        newNode->parent = current;
                        newNode->colorOfTheNode = 0;
                        cout << "Element inserted.\n";
                        break;
                    } else {
                        current = current->leftChild;
                    }
                } else {
                    if (current->rightChild == nullptr) {
                        current->rightChild = newNode;
                        newNode->parent = current;
                        newNode->colorOfTheNode = 0;
                        cout << "Element inserted.\n";
                        break;
                    } else {
                        current = current->rightChild;
                    }
                }
            }

            checkBalancingOfColors(newNode);
        }
    }

    void checkBalancingOfColors(TreeNode *current) {
        while (current->parent != nullptr && current->parent->colorOfTheNode == 0) {
            auto grandparent = current->parent->parent;
            auto uncle = root;
            if (current->parent == grandparent->leftChild) {
                if (grandparent->rightChild) {
                    uncle = grandparent->rightChild;
                }
                if (uncle->colorOfTheNode == 0) {
                    current->parent->colorOfTheNode = 1;
                    uncle->colorOfTheNode = 1;
                    grandparent->colorOfTheNode = 0;
                    current = grandparent;
                } else {
                    if (current == current->parent->rightChild) {
                        current = current->parent;
                        leftRotation(current);
                    }
                    current->parent->colorOfTheNode = 1;
                    grandparent->colorOfTheNode = 0;
                    rightRotation(grandparent);
                }
            } else {
                if (grandparent->leftChild) {
                    uncle = grandparent->leftChild;
                }
                if (uncle->colorOfTheNode == 0) {
                    current->parent->colorOfTheNode = 1;
                    uncle->colorOfTheNode = 1;
                    grandparent->colorOfTheNode = 0;
                    current = grandparent;
                } else {
                    if (current == current->parent->leftChild) {
                        current = current->parent;
                        rightRotation(current);
                    }
                    current->parent->colorOfTheNode = 1;
                    grandparent->colorOfTheNode = 0;
                    leftRotation(grandparent);
                }
            }
        }
        root->colorOfTheNode = 1;
    }


    TreeNode *getRoot() {
        return root;
    }

    void deleteNode(int value) {
        TreeNode *elementToDelete = findNode(root, value);
        root = deleteFoundedNode(elementToDelete);
    }

    TreeNode *deleteFoundedNode(TreeNode *element) {
        while (element != nullptr) {
            TreeNode *parent = element->parent;
            TreeNode *child = nullptr;
            int color = element->colorOfTheNode;
            if (element->rightChild == nullptr && element->leftChild == nullptr) {
                // Node has no children
                if (parent != nullptr) {
                    if (parent->data > element->data) {
                        parent->leftChild = nullptr;
                    } else {
                        parent->rightChild = nullptr;
                    }
                } else {
                    root = nullptr;
                }
                if(color==0){
                    element= nullptr;
                }else if (color == 1) {
                    deleteFixup(child, parent);
                    element= nullptr;
                }
                //
                break;
            } else if (element->rightChild != nullptr && element->leftChild != nullptr) {
                // Node has both left and right children
                TreeNode *successor = findMin(element->rightChild);
                element->data = successor->data;
                element = successor;
            } else {
                // Node has only one child
                TreeNode *child = (element->leftChild != nullptr) ? element->leftChild : element->rightChild;
                if (parent != nullptr) {
                    if (parent->data > element->data) {
                        parent->leftChild = child;
                    } else {
                        parent->rightChild = child;
                    }
                    child->parent = parent;
                } else {
                    root = child;
                    if (child != nullptr) {
                        child->parent = nullptr;
                    }
                }

                if (color == 0) {
                    element= nullptr;
                } else {
                    deleteFixup(child, parent);
                    element= nullptr;
                }
                break;
            }
        }
        return root;
    }

    void deleteFixup(TreeNode *current, TreeNode *parent) {
        while (current != root && (current == nullptr || current->colorOfTheNode == 1)) {
            if (current == parent->leftChild) {
                TreeNode* sibling = parent->rightChild;

                if (sibling != nullptr && sibling->colorOfTheNode == 0) {
                    sibling->colorOfTheNode = 1;
                    parent->colorOfTheNode = 0;
                    leftRotation(parent);
                    sibling = parent->rightChild;
                }

                if ((sibling->leftChild == nullptr || sibling->leftChild->colorOfTheNode == 1) &&
                    (sibling->rightChild == nullptr || sibling->rightChild->colorOfTheNode == 1)) {
                    sibling->colorOfTheNode = 0;
                    current = parent;
                    parent = current->parent;
                } else {
                    if (sibling->rightChild == nullptr || sibling->rightChild->colorOfTheNode == 1) {
                        sibling->leftChild->colorOfTheNode = 1;
                        sibling->colorOfTheNode = 0;
                        rightRotation(sibling);
                        sibling = parent->rightChild;
                    }

                    sibling->colorOfTheNode = parent->colorOfTheNode;
                    parent->colorOfTheNode = 1;
                    sibling->rightChild->colorOfTheNode = 1;
                    leftRotation(parent);
                    current = root;
                }
            } else {
                TreeNode* sibling = parent->leftChild;

                if (sibling != nullptr && sibling->colorOfTheNode == 0) {
                    sibling->colorOfTheNode = 1;
                    parent->colorOfTheNode = 0;
                    rightRotation(parent);
                    sibling = parent->leftChild;
                }

                if ((sibling->rightChild == nullptr || sibling->rightChild->colorOfTheNode == 1) &&
                    (sibling->leftChild == nullptr || sibling->leftChild->colorOfTheNode == 1)) {
                    sibling->colorOfTheNode = 0;
                    current = parent;
                    parent = current->parent;
                } else {
                    if (sibling->leftChild == nullptr || sibling->leftChild->colorOfTheNode == 1) {
                        sibling->rightChild->colorOfTheNode = 1;
                        sibling->colorOfTheNode = 0;
                        leftRotation(sibling);
                        sibling = parent->leftChild;
                    }

                    sibling->colorOfTheNode = parent->colorOfTheNode;
                    parent->colorOfTheNode = 1;
                    sibling->leftChild->colorOfTheNode = 1;
                    rightRotation(parent);
                    current = root;
                }
            }
        }

        if (current != nullptr) {
            current->colorOfTheNode = 1;
        }
    }

    TreeNode *findMin(TreeNode *node) {
        while (node->leftChild != nullptr) {
            node = node->leftChild;
        }
        return node;
    }

    void setConsoleColor(int colorCode) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
    }

    void resetConsoleColor() {
        setConsoleColor(7);
    }

    void printTree(TreeNode *node, int level = 0) {
        if (node == nullptr) {
            return;
        }
        printTree(node->rightChild, level + 1);

        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        if (node->colorOfTheNode == 0) {
            setConsoleColor(12);
            cout << node->data << " ";
        } else {
            setConsoleColor(8);
            cout << node->data << " ";
        }

        resetConsoleColor();
        cout << endl;

        printTree(node->leftChild, level + 1);
    }

private:
    TreeNode *root;

    TreeNode *leftRotation(TreeNode *node) {
        TreeNode *newRoot = node->rightChild;
        node->rightChild = newRoot->leftChild;
        if (newRoot->leftChild != nullptr) {
            newRoot->leftChild->parent = node;
        }
        newRoot->leftChild = node;
        newRoot->parent = node->parent;
        if (node->parent == nullptr) {
            root = newRoot;
        } else if (node == node->parent->leftChild) {
            node->parent->leftChild = newRoot;
        } else {
            node->parent->rightChild = newRoot;
        }
        node->parent = newRoot;
        return newRoot;
    }

    TreeNode *rightRotation(TreeNode *node) {
        TreeNode *newRoot = node->leftChild;
        node->leftChild = newRoot->rightChild;
        if (newRoot->rightChild != nullptr) {
            newRoot->rightChild->parent = node;
        }
        newRoot->rightChild = node;
        newRoot->parent = node->parent;
        if (node->parent == nullptr) {
            root = newRoot;
        } else if (node == node->parent->leftChild) {
            node->parent->leftChild = newRoot;
        } else {
            node->parent->rightChild = newRoot;
        }
        node->parent = newRoot;
        return newRoot;
    }
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

/*

 Input element to add:11

 Input element to add:7

 Input element to add:20

 Input element to add:15

 Tree:
  20
    15
11
  7


 Input element to add:25

 Input element to add:17

 Input element to add:55

 Tree:
      55
    25
  20
      17
    15
11
  7


 Input element to delete:7

 Tree:
    55
  25
20
    17
  15
    11

 * */

/*

 Input element to add:5

 Input element to add:2

 Input element to add:7

 Tree:
  7
5
  2


 Input element to add:6

 Input element to add:11

 Tree:
    11
  7
    6
5
  2


 Input element to add:66

      66
    11
  7
    6
5
  2


 Input element to delete:66

 Tree:
    11
  7
    6
5
  2


 Input element to delete:2

 Tree:
  11
7
    6
  5


 Input element to delete:7

 Tree:
  11
6
  5


 Input element to delete:11

 Tree:
6
  5


 Input element to add:4

 Tree:
  6
5
  4


 Input element to add:1

 Tree:
  6
5
  4
    1


 Input element to add:22

 Tree:
    22
  6
5
  4
    1


 Input element to add:7

 Tree:
    22
  7
    6
5
  4
    1

 * */
/*

 Input element to add:5

 Input element to add:1

 Input element to add:20

 Input element to add:11

 Input element to add:25

 Input element to add:7

 Input element to add:15

 Input element to add:55

 Tree:
      55
    25
  20
      15
    11
      7
5
  1


 Input element to add:17

 Tree:
      55
    25
  20
      17
    15
11
    7
  5
    1


 Input element to delete:25

 Tree:
    55
  20
      17
    15
11
    7
  5
    1


 Input element to delete:55

 Tree:
    20
  17
    15
11
    7
  5
    1

 * */