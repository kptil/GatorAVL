#include "TreeNode.h"

TreeNode::TreeNode(int studentID, string name, TreeNode* left, TreeNode* right, int height) {
	this->studentID = studentID;
	this->name = name;
	this->left = left;
	this->right = right;
	this->height = height;
}