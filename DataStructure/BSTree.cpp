#include "stdafx.h"
#include "BSTree.h"
#include <iostream>
#include <queue>
using namespace std;

BSTree::BSTree()
{	
	root = nullptr;
}

TreeNode* insert(TreeNode* node, int nodeValue) {	
	if(node== nullptr)
	{
		node = new TreeNode;
		node->value = nodeValue;
		node->left = nullptr;
		node->right = nullptr;
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

bool BSTree::is_value_in_tree(TreeNode* node, int value) {
	if (node == nullptr)
		return false;
	else if (node->value == value)
		return true;
	else if (node->value > value)
		is_value_in_tree(node->left, value);
	else if (node->value < value)
		is_value_in_tree(node->right, value);
}

TreeNode* BSTree::get_min_node_of_branch(TreeNode* node) {
	if (node != nullptr && node->left == nullptr)
		return node;
	else
		get_min_node_of_branch(node->left);	
}

int BSTree::get_min_value_of_tree() {
	return get_min_node_of_branch(root)->value;
}

TreeNode* BSTree::get_max_node_of_branch(TreeNode* node) {
	if (node != nullptr && node->right == nullptr)
		return node;
	else
		get_max_node_of_branch(node->right);
}

int BSTree::get_max_value_of_tree() {
	return get_max_node_of_branch(root)->value;
}

TreeNode* BSTree::delete_node(TreeNode*node, int value) {
	if (node == nullptr) return nullptr;		

	if (node->value > value) {
		delete_node(node->left, value);
	}
	else if (node->value < value)
	{
		delete_node(node->right, value);
	}
	else {
		if (node->left == nullptr && node->right == nullptr){
			delete(node);			
		}
		else if (node->right == nullptr) {
			TreeNode* temp = node; //pass by reference, why
			node = node->left;
			delete temp;
		}
		else if (node->left == nullptr) {
			TreeNode* temp = node; //pass by reference, why
			node = node->right;
			delete temp;
		}
		else {
			TreeNode*temp = get_min_node_of_branch(node->right); //pass by reference, why
			node->value = temp->value;
			node->right = delete_node(node->right, temp->value);
			delete(temp);
		}
	}
	return node;

}
int get_height(TreeNode* node) {
	if (node == nullptr)
		return 0;
	return 1 + std::max(get_height(node->left), get_height(node->right)); //will rewrite this
}
int BSTree::get_child_count(TreeNode* node) {
	if (node == nullptr)
	{
		cout << "Error: Node is null" << endl;
		return;
	}
	
	if (node->left == nullptr && node->right == nullptr) {
		return 0;
	}
	else if (node->left != nullptr && node->right != nullptr) {
		return 2;
	}
	else
		return 1;
}

BSTree::~BSTree()
{
}
