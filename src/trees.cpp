class TreeNode {
    private:
        int value;
        NodeBT *left;
        NodeBT *right;

    public:
    TreeNode(int x) {
        this->value = x;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BinaryTree {
    NodeST *root;

    public:
    BinaryTree() {
        root = nullptr;
    }

    bool find(int x, TreeNode *node = root) {
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
    }

    void insert(int x, TreeNode *node = root) {
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
};

class SplayTree {
    TreeNode *root;

    public:
    SplayTree() {
        root = nullptr;
    }

    bool find(int x, TreeNode *node = root) {
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
    }

    void insert(int x, TreeNode *node = root) {
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
};

    void splay(int x, TreeNode *node) {
        return;
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
};
