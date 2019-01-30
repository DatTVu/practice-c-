#include "stdafx.h"
#include "BSTree.h"


BSTree::BSTree()
{	
	root = NULL;
}

TreeNode* insert(TreeNode* node, int nodeValue) {	
	if(node==NULL)
	{
		node = new TreeNode;
		node->value = nodeValue;
		node->left = NULL;
		node->right = NULL;	
		return node;
	}	
	else if (node->value > nodeValue) {
		node->left = insert(node->left, nodeValue);
	}
	else if (node->value < nodeValue) {
		node->right = insert(node->right, nodeValue);
	}
	else return false;

	return node;
};
bool BSTree::is_in_tree(TreeNode* node) {

}
BSTree::~BSTree()
{
}
