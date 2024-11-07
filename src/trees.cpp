#include <iostream>
#include <utility>


typedef unsigned int uint;

class TreeNode {
    public:
    uint value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(uint x) {
        this->value = x;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BinaryTree {
    TreeNode *root;

    public:
    BinaryTree() {
        root = nullptr;
    }
    
    bool find(uint x) {
        return find(x, root);
    }
    void insert(uint x) {
        if (root == nullptr) {
            root = new TreeNode(x);
        } else {
            insert(x, root);
        }
    }

    void print() {
        print(root);
    }
    private:
    void print(TreeNode *node) {
        std::cout << "(";
        if (node->left != nullptr) {
            print(node->left);
        } 
        std::cout << node->value;
        if (node->right != nullptr) {
            print(node->right);
        }
        std::cout << ")";
    }

    bool find(uint x, TreeNode *node) {
        if (node == nullptr){
            return false;
        } else if (node->value == x) {
            return true;
        } else if (node->value < x) {
            if (node->left != nullptr) {
                return find(x, node->left);
            }
        } else {
            if (node->right != nullptr) {
                return find(x, node->right);
            }
        }
        return false;
    }

    void insert(uint x, TreeNode *node) {
        if (node->value == x) {
            return;
        } else if (node->value > x) {
            if (node->left != nullptr) {
                insert(x, node->left);
            } else {
                node->left = new TreeNode(x);
            }
        } else {
            if (node->right != nullptr) {
                insert(x, node->right);
            } else {
                node->right = new TreeNode(x);
            }
        }
    }
};

class SplayTree {
    TreeNode *root;

    public:
    SplayTree() {
        root = nullptr;
    }
    bool find(uint x) {
        return find(x, root);
    }
    void insert(uint x) {
        insert(x, root);
        splay(x, root);
    }

    void print() {
        print(root);
    }
    private:
    void print(TreeNode *node) {
        std::cout << "(";
        if (node->left != nullptr) {
            print(node->left);
        } 
        std::cout << node->value;
        if (node->right != nullptr) {
            print(node->right);
        }
        std::cout << ")";
    }

    bool find(uint x, TreeNode *node) {
        if (node == nullptr){
            return false;
        } else if (node->value == x) {
            return true;
        } else if (node->value < x) {
            if (node->left != nullptr) {
                return find(x, node->left);
            }
        } else {
            if (node->right != nullptr) {
                return find(x, node->right);
            }
        }
        return false;
    }

    void insert(uint x, TreeNode *node) {
        if (node == nullptr){
            node = new TreeNode(x);
        } else if (node->value == x) {
            return;
        } else if (node->value < x) {
            if (node->left != nullptr) {
                insert(x, node->left);
            }
        } else {
            if (node->right != nullptr) {
                insert(x, node->right);
            }
        }
    }

    void splay(uint x, TreeNode *node) {
        if (node == nullptr || node->value == x)
        return;

        if (node->value > x and root->left != nullptr) {
            // zig zig
            if (node->left->value > x) {
                splay(x, node->left->left);
                // right rotate
                zig_zig(node->left);
            }
            // zig zag
            else if (node->left->value < x and node->left->right != nullptr) {
                splay(x, node->left->right);
                zig_zag(node->left);
            }
        } else if (node->right != nullptr){
            if (node->right->value > x) {
                splay(x, node->right->left);
                if (node->right->left != nullptr)
                    zig(node->right);
            }
            else if (node->right->value < x) {
                splay(x, node->right->right);
                zag(node);
            }
            return (node->right != nullptr) ? node : leftRotate(root);
        }
    }

    void zig(TreeNode *y) {
        TreeNode *x = y->left;
        y->left = x->right;
        x->right = y;
        std::swap(y, x);
    }

    void zag(TreeNode *y) {
        TreeNode *x = y->right;
        y->right = x->left;
        x->left = y;
        std::swap(y, x);
    }

    void zig_zig(TreeNode *z) {
        zig(z->left);
        if (z->left != nullptr) {
            zig(z);
        }
    }

    void zig_zag(TreeNode *z) {
        zag(z->right);
        if (z->right != nullptr) {
            zig(z);
        }
    }

    void zag_zig(TreeNode *z) {
        zig(z->left);
        if (z->left != nullptr) {
            zag(z);
        }
    }

    void zag_zag(TreeNode *z) {
        zig(z->left);
        if (z->left != nullptr) {
            zig(z);
        }
    }
};





