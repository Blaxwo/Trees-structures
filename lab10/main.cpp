#include <iostream>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *parent;
    TreeNode *leftChild;
    TreeNode *rightChild;
    int balanceFactor;

    TreeNode(int value) : data(value), leftChild(nullptr), rightChild(nullptr), parent(nullptr), balanceFactor(0) {}
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
        // ------------------------------------------------------------------

        updateBalanceFactor(current);
        current = balanceTree(current);

        return current;
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
                delete element;
                while (parent != nullptr) {
                    updateBalanceFactor(parent);
                    root = balanceTree(parent);
                    parent = parent->parent;
                }
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
                delete element;
                while (parent != nullptr) {
                    updateBalanceFactor(parent);
                    root = balanceTree(parent);
                    parent = parent->parent;
                }
                break;
            }
            while (parent != nullptr) {
                updateBalanceFactor(parent);
                root = balanceTree(parent);
                parent = parent->parent;
            }
        }
        return root;
    }

    TreeNode *findMin(TreeNode *node) {
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

    int height(TreeNode *node) {
        if (node == nullptr) {
            return -1;
        }
        return max(height(node->leftChild), height(node->rightChild)) + 1;
    }

    void updateBalanceFactor(TreeNode *node) {
        if (node != nullptr) {
            node->balanceFactor = height(node->leftChild) - height(node->rightChild);
        }
    }

    TreeNode *balanceTree(TreeNode *node) {
        if (node != nullptr) {
            if (node->balanceFactor == 2) {
                // Left-Heavy Subtree
                if (height(node->leftChild->leftChild) >= height(node->leftChild->rightChild)) {
                    // Single Right Rotation
                    return rightRotation(node);
                } else {
                    // Double Rotation: Left-Right Rotation
                    node->leftChild = leftRotation(node->leftChild);
                    return rightRotation(node);
                }
            } else if (node->balanceFactor == -2) {
                // Right-Heavy Subtree
                if (height(node->rightChild->leftChild) <= height(node->rightChild->rightChild)) {
                    // Single Left Rotation
                    return leftRotation(node);
                } else {
                    // Double Rotation: Right-Left Rotation
                    node->rightChild = rightRotation(node->rightChild);
                    return leftRotation(node);
                }
            }
        }
        return node;
    }


    TreeNode *leftRotation(TreeNode *root) {
        TreeNode *newRoot = root->rightChild;
        root->rightChild = newRoot->leftChild;
        if (newRoot->leftChild != nullptr) {
            newRoot->leftChild->parent = root;
        }
        newRoot->leftChild = root;
        newRoot->parent = root->parent;
        root->parent = newRoot;
        updateBalanceFactor(root);
        updateBalanceFactor(newRoot);

        return newRoot;
    }

    TreeNode *rightRotation(TreeNode *root) {
        TreeNode *newRoot = root->leftChild;
        root->leftChild = newRoot->rightChild;
        if (newRoot->rightChild != nullptr) {
            newRoot->rightChild->parent = root;
        }
        newRoot->rightChild = root;
        newRoot->parent = root->parent;
        root->parent = newRoot;
        updateBalanceFactor(root);
        updateBalanceFactor(newRoot);

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
