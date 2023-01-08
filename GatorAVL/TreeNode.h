#pragma once
#include <string>
using namespace std;

struct TreeNode
{
	int studentID;
	string name;
	TreeNode* left;
	TreeNode* right;
	int height;
	TreeNode(int studentID = 0, string name = "", TreeNode* left = nullptr, TreeNode* right = nullptr, int height = 1);
};

