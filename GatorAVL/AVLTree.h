#pragma once
#include "TreeNode.h"
#include <vector>
using namespace std;

// Dynamic Memory: may want to use a nodeCount and then iterate with remove(n) to delete all nodes?

class AVLTree
{
	TreeNode* root;
	int height(TreeNode* node);

	// Private helper functions implementing recursion.
	TreeNode* rotateLeft(TreeNode* node);
	TreeNode* rotateRight(TreeNode* node);
	TreeNode* rotateLeftRight(TreeNode* node);
	TreeNode* rotateRightLeft(TreeNode* node);
	TreeNode* insertHelp(TreeNode* root, int ID, string name);
	TreeNode* searchHelp(TreeNode* root, int ID);
	vector<TreeNode*> searchHelp(TreeNode* root, vector<TreeNode*> vec, string name);
	TreeNode* removeHelp(TreeNode* root, int ID);
	vector<TreeNode*> vectorInOrder(TreeNode* root, vector<TreeNode*> vec);
	TreeNode* getMin(TreeNode* root);
	string printInOrderHelp(TreeNode* root);
	string printPreOrderHelp(TreeNode* root);
	string printPostOrderHelp(TreeNode* root);

public:
	AVLTree();
	bool insert(int ID, string name);
	bool remove(int ID);
	bool removeInOrder(int n);
	TreeNode* search(int ID);
	vector<TreeNode*> search(string name);
	void printInOrder();
	void printPreOrder();
	void printPostOrder();
	void printLevelCount();
};

