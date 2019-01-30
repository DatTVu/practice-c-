#pragma once

struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;
};



class BSTree
{	//constructor
	BSTree(); 
	//destructor
	~BSTree();
	//insert value into a tree
	
	//get count of values stored
	int get_node_count();
	//print the values in the tree, from min to max
	void print_values();
	//delete_tree
	void delete_tree();
	//return true if give value exists in the tree
	bool is_in_tree();
	//return the height in nodes
	int get_height();
	//return min value stored in the tree
	int get_min();
	//return max value stored in the tree
	int get_max();
	//check if a tree is a valid binary tree
	bool is_binary_search_tree();
	//delete value
	void delete_node();
	//returns next highest value in the tree after given value, -1 if none
	int get_successor();	

private:
	TreeNode *root;
};

TreeNode* insert(TreeNode*node, int nodeValue);

