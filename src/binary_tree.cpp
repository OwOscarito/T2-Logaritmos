class NodeBT {
    private:
        int value;
        NodeBT *left;
        NodeBT *right;

    public:
    NodeBT(int x) {
        this->value = x;
        this->left = nullptr;
        this->right = nullptr;
    }

    bool find(int x) {
        if (value == x) {
            return true;
        } else if (value < x) {
            if (left != nullptr) {
                return left->find(x);
            }
        } else {
            if (right != nullptr) {
                return right->find(x);
            }
        }
        return false;
    }

    void insert(int x) {
        if (value == x) {
            return;
        } else if (value < x) {
            if (left != nullptr) {
                return left->insert(x);
            } else {
                left = new NodeBT(x);
            }
        } else {
            if (right != nullptr) {
                return right->insert(x);
            } else {
                right = new NodeBT(x);
            }
        }
    }
};