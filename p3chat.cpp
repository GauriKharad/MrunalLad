#include <iostream>
#include <queue>   // For BFS
using namespace std;

class node {
public:
    int info;
    node *left;
    node *right;
};

class BST {
public:
    node *root;
    BST() { root = NULL; }

    void insert(node *, node *);
    void display(node *, int);
    int min(node *);
    int height(node *);
    void mirror(node *);
    void preorder(node *);
    void inorder(node *);
    void postorder(node *);
    void search(node *, int);
    node* deleteNode(node *, int);
    void BFS(node *);
    node* getRoot() { return root; }
};

// Insert node into BST
void BST::insert(node *tree, node *newnode) {
    if (root == NULL) {
        root = new node;
        root->info = newnode->info;
        root->left = root->right = NULL;
        cout << "Root Node is Added" << endl;
        return;
    }
    if (tree->info == newnode->info) {
        cout << "Element already in the tree" << endl;
        return;
    }
    if (tree->info > newnode->info) {
        if (tree->left != NULL)
            insert(tree->left, newnode);
        else {
            tree->left = newnode;
            newnode->left = newnode->right = NULL;
            cout << "Node Added To Left" << endl;
        }
    } else {
        if (tree->right != NULL)
            insert(tree->right, newnode);
        else {
            tree->right = newnode;
            newnode->left = newnode->right = NULL;
            cout << "Node Added To Right" << endl;
        }
    }
}

// Display tree
void BST::display(node *ptr, int level) {
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        cout << endl;
        for (int i = 0; i < level; i++)
            cout << "       ";
        cout << ptr->info;
        display(ptr->left, level + 1);
    }
}

// Find minimum value in tree
int BST::min(node *root) {
    node *temp = root;
    while (temp && temp->left != NULL)
        temp = temp->left;
    return temp->info;
}

// Height of tree (longest path)
int BST::height(node *root) {
    if (root == NULL) return 0;
    int lheight = height(root->left);
    int rheight = height(root->right);
    return max(lheight, rheight) + 1;
}

// Mirror the tree
void BST::mirror(node *root) {
    if (root != NULL) {
        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }
}

// Traversals
void BST::preorder(node *ptr) {
    if (ptr != NULL) {
        cout << ptr->info << " ";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void BST::inorder(node *ptr) {
    if (ptr != NULL) {
        inorder(ptr->left);
        cout << ptr->info << " ";
        inorder(ptr->right);
    }
}

void BST::postorder(node *ptr) {
    if (ptr != NULL) {
        postorder(ptr->left);
        postorder(ptr->right);
        cout << ptr->info << " ";
    }
}

// Search
void BST::search(node *ptr, int key) {
    if (!ptr) {
        cout << "Element not found..." << endl;
        return;
    }
    if (ptr->info == key) cout << "Element Found..." << endl;
    else if (key < ptr->info) search(ptr->left, key);
    else search(ptr->right, key);
}

// Delete node
node* BST::deleteNode(node *root, int key) {
    if (!root) return root;
    if (key < root->info) root->left = deleteNode(root->left, key);
    else if (key > root->info) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) return root->right;
        else if (!root->right) return root->left;
        root->info = min(root->right);
        root->right = deleteNode(root->right, root->info);
    }
    return root;
}

// Breadth First Search (Level Order)
void BST::BFS(node *root) {
    if (!root) return;
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        node *temp = q.front();
        q.pop();
        cout << temp->info << " ";
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
}

int main() {
    BST bst;
    int choice, val;
    node *temp;
    while (true) {
        cout << "\n\nBinary Search Tree Operations" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Display Tree" << endl;
        cout << "3. Find Minimum" << endl;
        cout << "4. Height (Longest Path)" << endl;
        cout << "5. Mirror Tree" << endl;
        cout << "6. Preorder Traversal" << endl;
        cout << "7. Inorder Traversal" << endl;
        cout << "8. Postorder Traversal" << endl;
        cout << "9. Breadth-First Search (BFS)" << endl;
        cout << "10. Search an Element" << endl;
        cout << "11. Delete a Node" << endl;
        cout << "12. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                temp = new node();
                cout << "Enter value to insert: ";
                cin >> val;
                temp->info = val;
                temp->left = temp->right = NULL;
                bst.insert(bst.getRoot(), temp);
                break;
            case 2:
                cout << "\nBST Structure:\n";
                bst.display(bst.getRoot(), 1);
                break;
            case 3:
                cout << "\nMinimum value in tree: " << bst.min(bst.getRoot()) << endl;
                break;
            case 4:
                cout << "\nHeight of tree: " << bst.height(bst.getRoot()) << endl;
                break;
            case 5:
                bst.mirror(bst.getRoot());
                cout << "\nTree Mirrored." << endl;
                break;
            case 6:
                cout << "\nPreorder: ";
                bst.preorder(bst.getRoot());
                break;
            case 7:
                cout << "\nInorder: ";
                bst.inorder(bst.getRoot());
                break;
            case 8:
                cout << "\nPostorder: ";
                bst.postorder(bst.getRoot());
                break;
            case 9:
                cout << "\nBFS: ";
                bst.BFS(bst.getRoot());
                break;
            case 10:
                cout << "Enter value to search: ";
                cin >> val;
                bst.search(bst.getRoot(), val);
                break;
            case 11:
                cout << "Enter value to delete: ";
                cin >> val;
                bst.root = bst.deleteNode(bst.getRoot(), val);
                cout << "\nNode Deleted." << endl;
                break;
            case 12:
                exit(0);
            default:
                cout << "\nInvalid choice." << endl;
        }
    }
    return 0;
}