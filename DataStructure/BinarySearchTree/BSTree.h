#pragma once

struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;
};



class BSTree
{	//constructor
	BSTree();  //done
	//destructor
	~BSTree();	
	//return number of child of a node
	int get_child_count(TreeNode* node); //done
	//print the values in the tree, from min to max
	void print_values();
	//delete_tree
	void delete_tree();
	//return true if give value exists in the tree
	bool is_value_in_tree(TreeNode* node, int value); //done
	//return the height in nodes
	
	//return min value stored in the tree
	int get_min_value_of_tree(); //done
	//return min node in a branch 
	TreeNode* get_min_node_of_branch(TreeNode* node); //done
	//return max value stored in the tree
	int get_max_value_of_tree(); //done
	//return max node in a branch
	TreeNode* get_max_node_of_branch(TreeNode* node); //done
	//check if a tree is a valid binary tree
	bool is_binary_search_tree();	
	//returns next highest value in the tree after given value, -1 if none
	int get_successor();
	//delete a value
	TreeNode* delete_node(TreeNode*node, int value); //done
private:
	TreeNode *root;
};

int get_height(TreeNode* node);
TreeNode* insert(TreeNode*node, int nodeValue);


