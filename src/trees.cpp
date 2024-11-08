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

    }
    // Zig: y(x(A, B), C) → x(A, y(B, C)) (sólo si y es raíz)
    void zig(TreeNode *y) {
        TreeNode *x = y->left;
        TreeNode *B = x->right;

        y->left = B;
        x->right = y;
        
        std::swap(y, x);
    }
    // Zag: y(A, x(B, C)) → x(y(A, B), C) (sólo si y es raíz)
    void zag(TreeNode *y) {
        TreeNode *x = y->right;
        TreeNode *B = x->left;

        y->right = B;
        x->left = y;
        
        std::swap(y, x);
    }
    // Zig-zig: z(y(x(A, B), C), D) → x(A, y(B, z(C, D)))
    void zig_zig(TreeNode *z) {
        TreeNode *y = z->left;
        TreeNode *x = y->left;

        TreeNode *B = x->right;
        TreeNode *C = y->right;

        z->left = C;
        y->left = B;
        y->right = z;
        x->right = y;

        std::swap(z, x);
    }
    // Zig-zag: z(y(A, x(B, C)), D) → x(y(A, B), z(C, D))
    void zig_zag(TreeNode *z) {
        TreeNode *y = z->left;
        TreeNode *x = y->right;

        TreeNode *B = x->left;
        TreeNode *C = x->right;

        x->left = y;
        x->right = z;
        y->right = B;
        z->left = C;

        std::swap(z, x);
    }
    // Zag-zig: z(A, y(x(B, C), D)) → x(z(A, B), y(C, D))
    void zag_zig(TreeNode *z) {
        TreeNode *y = z->right;
        TreeNode *x = y->left;

        TreeNode *B = x->left;
        TreeNode *C = x->right;

        x->left = z;
        x->right = y;
        y->left = C;
        z->right = B;

        std::swap(z, x);
    }
    // Zag-zag: z(A, y(B, x(C, D))) → x(y(z(A, B), C), D)
    void zag_zag(TreeNode *z) {
        TreeNode *y = z->right;
        TreeNode *x = y->left;

        TreeNode *B = y->left;
        TreeNode *C = x->left;

        x->left = y;
        y->left = z;
        y->right = C;
        z->right = B;

        std::swap(z, x);
    }
};





