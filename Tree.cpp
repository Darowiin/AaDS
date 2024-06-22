#include <algorithm>
template<typename Type>
class BinarySearchTree {
	struct Node {
		Type value;
		Node* left;
		Node* right;
		Node(const Type& val) : value(val), left(nullptr), right(nullptr) {}
	};
	Node* _root;
    Node* copyTree(const Node* otherNode) {
        if (!otherNode) return nullptr;
        Node* newNode = new Node(otherNode->value);
        newNode->left = copyTree(otherNode->left);
        newNode->right = copyTree(otherNode->right);
        return newNode;
    }
    Node* insertRecursive(Node*& node, const Type key) {
        if (!node) return new Node(key);
        if (key < node->value) node->left = insertRecursive(node->left, key);
        else if (key > node->value) node->right = insertRecursive(node->right, key);
        return node;
    }
    Node* findMin(Node* node) const {
        if (!node->left) return node;
        return findMin(node->left);
    }
    Node* searchRecursive(Node* node, Type key) {
        if (!node || node->value == key) return node;
        if (key < node->value) return searchRecursive(node->left, key);
        else return searchRecursive(node->right, key);
    }
    void eraseRecursive(Node*& node, const Type key) {
        if (!node) return;
        if (key < node->value) eraseRecursive(node->left, key);
        else if (key > node->value) eraseRecursive(node->right, key);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                node = temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                node = temp;
            }
            else {
                node->value = findMin(node->right)->value;
                eraseRecursive(node->right, node->value);
            }
        }
    }
    void destroyRecursive(Node* node) {
        if (node) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }
    void printRecursive(Node* node, const std::string& prefix = "", bool isLeft = true) const {
        if (_root) {
            std::cout << prefix;

            std::cout << (isLeft ? "|--" : "\\--");

            std::cout << _root->value << std::endl;

            printRecursive(_root->left, prefix + (isLeft ? "|   " : "    "), true);
            printRecursive(_root->right, prefix + (isLeft ? "|   " : "    "), false);
        }
    }
    bool containsRecursive(Node* node, const Type key) const {
        if (node) {
            if (node->value == key) return true;
            else if (node->value < key) return containsRecursive(node->right, key);
            else return containsRecursive(node->left, key);
        }
        return false;
    }
    int countRecursive(Node* node) {
        if (!node) return 0;
        return 1 + countRecursive(node->left) + countRecursive(node->right);
    }


    Type sum_of_tree(Node* node) {
        if (!node) return 0;
        return node->value + sum_of_tree(node->left) + sum_of_tree(node->right);
    }
    Type avg_of_tree(Node* node) {
        if (!node) return 0;
        return sum_of_tree(node) / (double)countRecursive(node);
    }
    size_t get_height(Node* node) {
        if (!node) return 0;
        return 1 + std::max(get_height(node->left), get_height(node->right));
    }
    bool is_balanced(Node* node) { // O(n^2)
        if (!node) return true;
        size_t left_height = get_height(node->left);
        size_t right_height = get_height(node->right);
        if (std::abs(left_height - right_height) > 1) return false;
        return is_balanced(node->left) && is_balanced(node->right);
    }
    bool is_balanced(Node* node) { // O(n)
        return is_balanced_helper(node).second;
    }
    std::pair<int, bool> is_balanced_helper(Node* node) {
        if (!node) return { 0, true };

        auto left = is_balanced_helper(node->left);
        auto right = is_balanced_helper(node->right);

        int height = 1 + std::max(left.first, right.first);
        bool balanced = left.second && right.second && std::abs(left.first - right.first) <= 1;

        return { height, balanced };
    }
    Type find_min(Node* node) {
        if (!node) return -1;
        Type min_value = node->value;
        Type min_left = find_min(node->left);
        Type min_right = find_min(node->right);
        if (min_left < min_value) min_value = min_left;
        if (min_right < min_value) min_value = min_right;
        return min_value;
    }
    void print_leaves(Node* node) {
        if (!node) return;
        if (!node->left && !node->right) std::cout << node->value << " ";
        print_leaves(node->left);
        print_leaves(node->right);
    }
public:
    BinarySearchTree(): _root(nullptr) {}
    BinarySearchTree(const BinarySearchTree& other): _root(copyTree(other._root)) {}
    ~BinarySearchTree() {
        destroyRecursive(_root);
    }
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        BinarySearchTree copy(other);
        if (this != &copy) {
            std::swap(*this, copy);
        }
        return *this;
    }

    void print() const {
        std::cout << "Tree: " << std::endl;
        printRecursive(root);
    }
    bool insert(Type key) {
        return (insertRecursive(_root, key) != nullptr);
    }
    bool contains(Type key) const {
        return containsRecursive(_root, key);
    }
    bool erase(Type key) {
        if (contains(key)) {
            eraseRecursive(_root, key);
            return true;
        }
        return false;
    }
    int count() {
        return countRecursive(_root);
    }
    bool search(Type key) {
        return (searchRecursive(_root, key) != nullptr);
    }
};