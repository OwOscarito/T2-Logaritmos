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
        if (root == nullptr) {
            std::cout << "■──■" << std::endl;
        } else {
            print("    ", root->right, false);
            std::cout << "■──" << root->value << std::endl;
            print("    ", root->left, true);
        }
        std::cout << std::endl;
    }

    private:
    void print(const std::string& prefix, const TreeNode* node, bool isLeft) {
        if (node == nullptr) {
            std::cout << prefix;
            std::cout << (isLeft ? "└──" : "┌──" );
            std::cout << "■" << std::endl;
        } else{
            print(prefix + (isLeft ? "│   " : "    "), node->right, false);
            std::cout << prefix;
            std::cout << (isLeft ? "└──" : "┌──" );
            std::cout << node->value << std::endl;
            print(prefix + (isLeft ? "    " : "│   " ), node->left, true);
        }
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
        if (root == nullptr) {
            root = new TreeNode(x);
        } else {
            insert(x, root);
            root = splay(x, root);
        }
    }

    void print() {
        if (root == nullptr) {
            std::cout << "■──■" << std::endl;
        } else {
            print("    ", root->right, false);
            std::cout << "■──" << root->value << std::endl;
            print("    ", root->left, true);
        }
        std::cout << std::endl;
    }

    private:
    void print(const std::string& prefix, const TreeNode* node, bool isLeft) {
        if (node == nullptr) {
            std::cout << prefix;
            std::cout << (isLeft ? "└──" : "┌──" );
            std::cout << "■" << std::endl;
        } else{
            print(prefix + (isLeft ? "│   " : "    "), node->right, false);
            std::cout << prefix;
            std::cout << (isLeft ? "└──" : "┌──" );
            std::cout << node->value << std::endl;
            print(prefix + (isLeft ? "    " : "│   " ), node->left, true);
        }
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

    TreeNode* splay(uint x, TreeNode* node) {  
        if (node == nullptr|| node->value == x)  
            return node;  
    
        if (x < node->value) {  
            if (node->left == nullptr) {
                return node;
            }
            // Zig-Zig (Left Left)  
            if (x < node->left->value) {
                node->left->left = splay(x, node->left->left);  
                node = zig(node);  
            }  
            // Zig-Zag (Left Right)  
            else if (x > node->left->value) { 
                if (node->left->right != nullptr) {
                    node->left->right = splay(x, node->left->right);  
                    node->left = zag(node->left); 
                }
            }
            if (node->left == nullptr) { 
                return node;  
            } else {
                return zig(node);
            }
        }  
        else {
            if (node->right == nullptr)  
                return node;  
            // Zag-Zig (Right Left)  
            if (x > node->right->value) {  
                node->right->left = splay(x, node->right->left); 
                if (node->right->left != nullptr) {
                    node->right = zig(node->right);  
                }
            }  
            // Zag-Zag (Right Right)
            else if (x < node->right->value) {  
                node->right->right = splay(x, node->right->right);  
                node = zag(node);  
            } 
            if (node->left == nullptr) { 
                return node;  
            } else {
                return zig(node);
            }
        }  
        return node;
    }  

    // Zig: y(x(A, B), C) → x(A, y(B, C)) (sólo si y es raíz)
    TreeNode* zig(TreeNode *y) {
        TreeNode *x = y->left;
        TreeNode *B = x->right;

        y->left = B;
        x->right = y;
        
        return x;
    }
    // Zag: y(A, x(B, C)) → x(y(A, B), C) (sólo si y es raíz)
    TreeNode* zag(TreeNode *y) {
        TreeNode *x = y->right;
        TreeNode *B = x->left;

        y->right = B;
        x->left = y;
        
        return x;
    }
};





