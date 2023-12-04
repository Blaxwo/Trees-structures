#include <iostream>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *parent;
    TreeNode *children;
    TreeNode *nextSibling;

    TreeNode(int value, TreeNode* parentNode) : data(value), parent(parentNode), children(nullptr), nextSibling(nullptr) {}
};

class Tree{
public:
    Tree() : root(nullptr) {}

    TreeNode* findNode(TreeNode* current, int value) {
        if (current->data == value) {
            return current;
        }
        TreeNode* sibling = current->children;
        while (sibling != nullptr) {
            TreeNode* result = findNode(sibling, value);
            if (result) {
                return result;
            }
            sibling = sibling->nextSibling;
        }

        return nullptr;
    }

    void addNode(int parentValue, int value) {
        if (root == nullptr) {
            if (parentValue == -1) {
                root = new TreeNode(value, nullptr);
                return;
            } else {
                cout << "Parent not found." << endl;
                return;
            }
        }

        TreeNode* parent = findNode(root, parentValue);
        if (parent) {
            TreeNode* newNode = new TreeNode(value,parent);
            if (parent->children == nullptr) {
                parent->children = newNode;
            } else {
                TreeNode* sibling = parent->children;
                while (sibling->nextSibling != nullptr) {
                    sibling = sibling->nextSibling;
                }
                sibling->nextSibling = newNode;
            }
        } else {
            cout << "Parent not found." << endl;
        }
    }
    void deleteTree(TreeNode* current) {
        if (current == nullptr) {
            return;
        }

        TreeNode* sibling = current->children;
        while (sibling != nullptr) {
            TreeNode* nextSibling = sibling->nextSibling;
            deleteTree(sibling);
            sibling = nextSibling;
        }
        delete current;
    }

    TreeNode* getRoot() {
        return root;
    }

    void deleteNode(int value) {
        TreeNode* nodeToDelete = findNode(root, value);
        if (nodeToDelete) {
            if (nodeToDelete->parent) {
                TreeNode* parent = nodeToDelete->parent;
                if (parent->children == nodeToDelete) {
                    parent->children = nodeToDelete->nextSibling;
                } else {
                    TreeNode* sibling = parent->children;
                    while (sibling->nextSibling != nullptr) {
                        if (sibling->nextSibling == nodeToDelete) {
                            sibling->nextSibling = nodeToDelete->nextSibling;
                            break;
                        }
                        sibling = sibling->nextSibling;
                    }
                }
                deleteTree(nodeToDelete);
            } else {
                deleteTree(root);
                root = nullptr;
            }
        } else {
            cout << "Node not found." << endl;
        }
    }

    void printTree(TreeNode* node, int level = 0) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << node->data << endl;
        printTree(node->children, level + 1);
        printTree(node->nextSibling, level);
    }

    void PreOrder(TreeNode* current, int value) {

        if (current == nullptr || stopTraversal) {
            return;
        }

        result += to_string(current->data) + " ";

        if (current->data == value) {
            stopTraversal = true;
            return;
        }

        TreeNode *sibling = current->children;
        while (sibling != nullptr) {
            PreOrder(sibling, value);
            sibling = sibling->nextSibling;
            if (stopTraversal) {
                break;
            }
        }
    }

    void PostOrder(TreeNode *current, int value) {
        if (current == nullptr || stopTraversal) {
            return;
        }

        TreeNode *sibling = current->children;
        while (sibling != nullptr) {
            PostOrder(sibling, value);
            sibling = sibling->nextSibling;
            if (stopTraversal) {
                break;
            }
        }
        if (current->data == value) {
            stopTraversal = true;
            result += to_string(current->data) + " ";
            return;
        }

        if (stopTraversal) {
            return;
        }

        result += to_string(current->data) + " ";
    }

    void InOrder(TreeNode *current, int value) {
        if (current == nullptr || stopTraversal) {
            return;
        }
        TreeNode *sibling = current->children;
        TreeNode *fsibling = sibling;
        if(fsibling!= nullptr){
            InOrder(fsibling,value);
            if (stopTraversal) {
                return;
            }
        }
        result += to_string(current->data) + " ";
        if (current->data == value) {
            stopTraversal = true;
            return;
        }
        if (stopTraversal) {
            return;
        }
        while (sibling!= nullptr){
            if(sibling!=fsibling){
                InOrder(sibling, value);
            }
            sibling=sibling->nextSibling;
            if (stopTraversal) {
                break;
            }
        }
    }


    string getResult() const {
        return result;
    }

    void clearResult() {
        result.clear();
        stopTraversal = false;
    }

private:
    TreeNode* root;
    string result;
    bool stopTraversal;
};

int main() {
    int choice;
    Tree tree;
    tree.addNode(-1, 1);
    do {
        cout << "Menu:" << endl;
        cout << "1. Add" << endl;
        cout << "2. Remove" << endl;
        cout << "3. Print" << endl;
        cout << "4. Find" << endl;
        cout << "5. Find element forward (Pre-Order)" << endl;
        cout << "6. Find element reverse (Post-Order)" << endl;
        cout << "7. Find element symmetrical (In-Order)" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int parent, element;
                cout << "Input parent of element to add: ";
                cin >> parent;
                cout << "Input element to add: ";
                cin >> element;
                tree.addNode(parent, element);
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
                cout << "Tree: "<<endl;
                tree.printTree(tree.getRoot());
                cout << endl;
                break;
            }
            case 4: {
                int element;
                cout << "Input element to find: "<<endl;
                cin >> element;
                cout<<"Founded node: ";
                if(tree.findNode(tree.getRoot(), element) != nullptr){
                    cout<<tree.findNode(tree.getRoot(), element)->data<<endl;
                }
                else{
                    cout<<"There is no such element in tree"<<endl;
                }
                break;
            }
            case 5: {
                int element;
                cout << "Input element to find path during Pre-Order traversal: ";
                cin >> element;
                tree.clearResult();
                tree.PreOrder(tree.getRoot(), element);
                cout << "Elements visited during Pre-Order traversal: " << tree.getResult() << endl;

                break;
            }
            case 6: {
                int element;
                cout << "Input element to find path during Post-Order traversal: ";
                cin >> element;
                tree.clearResult();
                tree.PostOrder(tree.getRoot(), element);
                cout << "Elements visited during Post-Order traversal: " << tree.getResult() << endl;

                break;
            }
            case 7: {
                int element;
                cout << "Input element to find path during In-Order traversal: ";
                cin >> element;
                tree.clearResult();
                tree.InOrder(tree.getRoot(), element);
                cout << "Elements visited during In-Order traversal: " << tree.getResult() << endl;

                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);
}
