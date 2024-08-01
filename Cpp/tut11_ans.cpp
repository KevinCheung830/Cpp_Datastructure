/*
 * Instructions:
 *
 * 1. Only complete the functions specified below. Do not create any additional function.
 * 2. Use Visual Studio 2019 to build, test and run your code.
 * 3. Do not include any additional header or library.
 *
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>


using namespace std;

// tree structure

template<class T>
struct treeNode {
    T key;
    treeNode<T> *left;
    treeNode<T> *right;

	treeNode(T key, treeNode<T>* left, treeNode<T>* right) {
		this->key = key;
		this->left = left;
        this->right = right;
	}
};

//-------------------------- functions to be implemented by you

/**
* (1) Check if a given binary tree is a Binary Search Tree (BST). Return true if it
* is a BST. Otherwise return false. 
* 
* This function is designed with two extra parameters, min and max, which are used to 
* specify the minimum bound and maximum bound of the tree. They are initialized to NULL (in the main 
* function) as there is no bounds for the root tree. 
* 
* For a BST: left subtree < root < right subtree
* 
* Therefore, you can use the root as the min/max bound for the subtresses in the next level 
* and recursively validate the whole tree.
*
*/
bool isBST(treeNode<int>* root, treeNode<int>* min, treeNode<int>* max) {
	// base case
	if (root == NULL)
		return true;

	// check if greater than the minimum bound
	if (min != NULL && root->key <= min->key)
		return false;

	// check if smaller than the maximum bound
	if (max != NULL && root->key >= max->key)
		return false;

	// check recursively
	// root becomes the max bound on left subtree and min bound on right subtree
	return isBST(root->left, min, root) && isBST(root->right, root, max);
}


/**
 * (2) Check if a given binary tree is a Binary Search Tree (BST). Return true if it 
 * is a BST. Otherwise return false. 
 * 
 * This function is designed with one extra parameter, prev, which is used to track the 
 * predecessor of the current node in inorder traversal.
 * 
 * For a BST: inorder predecessor < root < inorder successor
 * 
 * Therefore, you can traverse the tree by inorder and validate if the root is greater 
 * than the previous node (i.e. the visited nodes should ascend straightly).
 */
bool isBST(treeNode<int>* root, treeNode<int>*& prev) {

	// base case
	if (root == NULL)		
		return true;

	// inorder traversal: left subtree
	// current prev is equal to the prev of left subtree
	if (!isBST(root->left, prev))
		return false;

	// inorder traversal: root
	// root should be greater than prev 
	if (prev != NULL && root->key <= prev->key)
		return false;

	// now root becomes the previous node of the right subtree
	prev = root;

	// inorder traversal: right subtree
	return isBST(root->right, prev);
}

//-------------------------- functions prepared for you

/*
 * Print a binary tree (rotated -90 degree).
 */
template<class T>
void printTree(treeNode<T> *p, int indent) {
    if (p != NULL) {
        printTree(p->right, indent + 6);
        cout << setw(indent) << '(' << p->key << ')' << endl;
        printTree(p->left, indent + 6);
    }
}

/*
 * Build a binary tree based on the array representation, where -1 represents 
 * an empty tree node.
 */
treeNode<int>* buildTree(int *array, int index, int size) {
    treeNode<int>* t = NULL;

    if (index < size && array[index] != -1) {
		t = new treeNode<int>(array[index], 
        buildTree(array, 2 * index + 1, size), 
        buildTree(array, 2 * index + 2, size));
    }
    return t;
}

/*
 * Driver program
 *
 * Read the test cases from the input file and use them to test
 * your functions' implementation.
 *
 */
int main(int argc, char** argv) {

    ifstream fin("tut11_input.txt");
    if (!fin) {
        cout << "Input file not found.";
        exit(1);
    }

    int testcase = 0;
    fin >> testcase;

    for (int i = 0; i < testcase; i++) {

        int n;
        fin >> n;
        int* arr = new int[n];
        for (int j = 0; j < n; j++)
            fin >> arr[j];

		treeNode<int> *tree = buildTree(arr, 0, n);
		treeNode<int> *prev = NULL;
		cout << "Case " << i + 1 << endl;
		printTree(tree, 0);
		cout << endl;
		cout << "Is a BST? ";
		cout << " (1)" << (isBST(tree, NULL, NULL) ? "YES" : "NO");
		cout << " (2)" << (isBST(tree, prev) ? "YES" : "NO") << endl;
		cout << endl;

		delete[] arr;
    }

	fin.close();
}

