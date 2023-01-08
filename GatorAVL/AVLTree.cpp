#include "AVLTree.h"
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

AVLTree::AVLTree() {
    root = nullptr;
}

/*======= Rotations and Utility Functions =======*/

TreeNode* AVLTree::rotateLeft(TreeNode* node)
{
    TreeNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

TreeNode* AVLTree::rotateRight(TreeNode* node)
{
    TreeNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}

TreeNode* AVLTree::rotateLeftRight(TreeNode* node)
{
    node->left = rotateLeft(node->left);
    node = rotateRight(node);
    return node;
}

TreeNode* AVLTree::rotateRightLeft(TreeNode* node)
{
    node->right = rotateRight(node->right);
    node = rotateLeft(node);
    return node;
}

// Calculates the 1-based height of the node. A node's height is the height of it's tallest subtree.
int AVLTree::height(TreeNode* node) {
    if (node == nullptr) { return 0; }
    else { return std::max(height(node->left), height(node->right)) + 1; }
}

// Gets the minimum value in a tree by searching to the left until the left child is nullptr.
TreeNode* AVLTree::getMin(TreeNode* root) {
    if (root->left == nullptr) { return root; }
    else {
        return getMin(root->left);
    }
}

// Saves each node in the tree in a vector using an in order traversal. Supports removeInOrder(n).
vector<TreeNode*> AVLTree::vectorInOrder(TreeNode* root, vector<TreeNode*> vec) {
    if (root == nullptr) { return vec; }
    else {
        vec = vectorInOrder(root->left, vec);
        vec.push_back(root);
        vec = vectorInOrder(root->right, vec);
        return vec;
    }
}

/*====== Searching =======*/

// If ID is not found, searchHelp returns null node.
TreeNode* AVLTree::search(int ID) {
    return searchHelp(root, ID);
}

// If name is not found, searchHelp returns a vector of size 0.
vector<TreeNode*> AVLTree::search(string name) {
    vector<TreeNode*> matches;
    return searchHelp(root, matches, name);
}

// Helper function implementing a search by ID.
TreeNode* AVLTree::searchHelp(TreeNode* root, int ID) {
    if (root == nullptr) { return root; }
    else if (ID == root->studentID) { return root; }
    else {
        if (ID < root->studentID) { return searchHelp(root->left, ID); }
        else { return searchHelp(root->right, ID); }
    }
}

// Helper function implementing a search by name. Each match is placed in a vector of TreeNodes using a 
// pre order traversal.
vector<TreeNode*> AVLTree::searchHelp(TreeNode* root, vector<TreeNode*> vec, string name) {
    if (root == nullptr) { return vec; }
    else {
        if (root->name == name) { vec.push_back(root); }
        vec = searchHelp(root->left, vec, name);
        vec = searchHelp(root->right, vec, name);
        return vec;
    }
}

/*======= Insertion =======*/

// First calls search and returns false if ID already exists in the tree. If not, inserts a new node.
bool AVLTree::insert(int ID, string name) {
    if (search(ID) != nullptr) { return false; }
    else {
        root = insertHelp(this->root, ID, name);
        return true;
    }
}

/* Implements AVL balancing using rotations and balance factor calculations to insert a new node and then
   rebalance the tree, maintaining AVL properties post insert. */
TreeNode* AVLTree::insertHelp(TreeNode* root, int ID, string name) {
    if (root == nullptr) {
        TreeNode* newNode = new TreeNode(ID, name);
        return newNode;
    }
    else {
        if (ID > root->studentID) {
            // Saves the subtree edited in the recursie call to the appropriate pointer.
            root->right = insertHelp(root->right, ID, name);
            // Calculates the parent's and right child's balance factors using the height utility function.
            int balFactorP = height(root->left) - height(root->right);
            int balFactorC = 0;
            if (root->right != nullptr) { balFactorC = height(root->right->left) - height(root->right->right); }
            // Conducts rotations if the balance factors meet the conditions for rebalancing.
            if (balFactorP == 2 && balFactorC == 1) { root = rotateRight(root); }
            if (balFactorP == -2 && balFactorC == -1) { root = rotateLeft(root); }
            if (balFactorP == 2 && balFactorC == -1) { root = rotateLeftRight(root); }
            if (balFactorP == -2 && balFactorC == 1) { root = rotateRightLeft(root); }
        }
        else {
            // Saves the subtree edited in the recursie call to the appropriate pointer
            root->left = insertHelp(root->left, ID, name);
            // Calculates the parent's and left child's balance factors using the height utility function.
            int balFactorP = height(root->left) - height(root->right);
            int balFactorC = 0;
            if (root->left != nullptr) { balFactorC = height(root->left->left) - height(root->left->right); }
            // Conducts rotations if the balance factors meet the conditions for rebalancing.
            if (balFactorP == 2 && balFactorC == 1) { root = rotateRight(root); }
            if (balFactorP == -2 && balFactorC == -1) { root = rotateLeft(root); }
            if (balFactorP == 2 && balFactorC == -1) { root = rotateLeftRight(root); }
            if (balFactorP == -2 && balFactorC == 1) { root = rotateRightLeft(root); }
        }
        return root;
    }
}

/*======= Removal =========*/

// First calls search and returns false if ID does not exist in tree. If it does, removes via removeHelp.
bool AVLTree::remove(int ID) {
    if (search(ID) == nullptr) { return false; }
    else {
        root = removeHelp(root, ID);
        return true;
    }
}

/* Implements a BST removal only. After removal the tree is not rebalanced but, per instructions, is
   assumed to maintain AVL properties. */
TreeNode* AVLTree::removeHelp(TreeNode* root, int ID) {
    if (root == nullptr) { return root; }
    // When node to delete is found, implement removal for the cases of 0, 1, or 2 children.
    else {
        if (ID == root->studentID) {
            // Case 1: Deleted node (root) is a leaf. Set it to null and return to parent's pointer.
            if (root->left == nullptr && root->right == nullptr) { root = nullptr; }
            // Case 2: Deleted node (root) has one child. Set the root to be the existing child.
            else if (root->right == nullptr) { root = root->left; }
            else if (root->left == nullptr) { root = root->right; }
            /* Case 3: Deleted node (root) has two children. Replace the root with it's in order successor,
               or the minimum element in its right subtree. Then delete that node from the right subtree.*/
            else {
                TreeNode* minTemp = getMin(root->right);
                root->studentID = minTemp->studentID;
                root->name = minTemp->name;
                root->right = removeHelp(root->right, minTemp->studentID);
            }
        }
        // Recursive cases search until node to delete is found.
        else if (ID > root->studentID) { root->right = removeHelp(root->right, ID); }
        else { root->left = removeHelp(root->left, ID); }

        return root;
    }
}

/* Removes the nth node from the in order traversal, where n=0 is the first node. The node to delete is
   identified using the vectorInOrder utility function. The TreeNode at the nth location is then removed
   based on its ID using remove(int ID). Returns false if n is not within vector's range. */
bool AVLTree::removeInOrder(int n) {
    vector<TreeNode*> vec;
    vec = vectorInOrder(root, vec); // takes O(n) time
    if (n > vec.size() - 1) { return false; }
    else {
        bool success = remove(vec[n]->studentID); // takes O(logn) under constraints
        if (success) { return true; }
        else { return false; }
    }
}

/*====== Print Functions =======*/

void AVLTree::printLevelCount() {
    cout << height(root) << endl;
}

/* For each traversal, a print helper function returns a string with names associated with each node in the
   appropriate order, separated by commas. Due to the recursion, extra commas are places at the end of the
   string, which the public print functions remove. */

void AVLTree::printInOrder() {
    string names = printInOrderHelp(root);
    names.pop_back();
    names.pop_back();
    cout << names << endl;
}

string AVLTree::printInOrderHelp(TreeNode* root) {
    string names = "";
    if (root == nullptr) { return names; }
    else {
        names = printInOrderHelp(root->left) + root->name + ", " + printInOrderHelp(root->right);
        return names;
    }
}

void AVLTree::printPreOrder() {
    string names = printPreOrderHelp(root);
    names.pop_back();
    names.pop_back();
    cout << names << endl;
}

string AVLTree::printPreOrderHelp(TreeNode* root) {
    string names = "";
    if (root == nullptr) { return names; }
    else {
        names = root->name + ", " + printPreOrderHelp(root->left) + printPreOrderHelp(root->right);
        return names;
    }
}

void AVLTree::printPostOrder() {
    string names = printPostOrderHelp(root);
    names.pop_back();
    names.pop_back();
    cout << names << endl;
}

string AVLTree::printPostOrderHelp(TreeNode* root) {
    string names = "";
    if (root == nullptr) { return names; }
    else {
        names = printPostOrderHelp(root->left) + printPostOrderHelp(root->right) + root->name + ", ";
        return names;
    }
}