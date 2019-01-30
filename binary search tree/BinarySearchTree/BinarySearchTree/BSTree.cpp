#include "stdafx.h"
#include "BSTree.h"


BSTree::BSTree()
{	
}

TreeNode* insert(TreeNode* node, int nodeValue) {	
	if(node==NULL)
	{
		node = new TreeNode;
		node->value = nodeValue;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
	}	
	else if (node->value > nodeValue) {
		(*node).value = nodeValue;
		
	}
	else if (node->value < nodeValue) {

	}
	else return false;

	return node;
};

BSTree::~BSTree()
{
}
