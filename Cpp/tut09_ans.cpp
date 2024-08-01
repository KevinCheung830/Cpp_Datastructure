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
#include <queue>


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
 * This function uses an iterative approach to check if the given 
 * tree is a complete tree. It returns true if the tree is complete; 
 * otherwise return false.
 */
bool isComplete(treeNode<int>* root) {

    // Please refer to lecture notes p.57 and p.78 for the example
    // of level order tree traversal. You can use queue to perform level 
    // order traversal in this exercise.

    // By observation of a complete tree, we can see that with a level order traversal 
    // starting from the root, once a node is found which is not degree 2, all the 
    // following nodes must be degree 0.

    // References:
    // Level order traversal p.78
	// Complete binary tree p.29
	
	// Rule 1: a node cannot have right child only (i.e. left child not exist but right child exist)
	
	// Rule 2: degree of nodes must decrease monotonically in level order
	// one-node-tree: 	d0
	// two-node-tree: 	d1 -> d0
	// three-node-tree: d2 -> d0 -> d0
	// four-node-tree: 	d2 -> d1 -> d0 -> d0

    // Rule 3: d1 must followed by d0

    queue<treeNode<int>*> mqueue;

    if (root == NULL)
		return true;
	else
        mqueue.push(root);

    int prevDeg = 2;		// degree of previous node, initialize to 2
    while (!mqueue.empty()) {
        treeNode<int>* cur = mqueue.front();
        mqueue.pop();
		
		int curDeg = 0;		// degree of current node

        if(cur->left != NULL) {
			mqueue.push(cur->left);
			curDeg++;
		}
		
        if(cur->right != NULL) {
			mqueue.push(cur->right);
			curDeg++;
		}
		
		if(cur->left == NULL && cur->right != NULL) 
			return false;   // rule 1
		
		if(curDeg > prevDeg)
			return false;   // rule 2
		
        if(prevDeg == 1 && curDeg == 1)
            return false;   // rule 3
        
        prevDeg = curDeg;	
    }

    return true;    // run through the tree and all nodes follow our observated pattern
}

//-------------------------- functions prepared for you

/*
 * Print a binary tree (rotated by -90 degree).
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
 * Build a binary tree based on the array representation, where -1 
 * in the input represents an empty tree node.
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

    ifstream fin("tut09_input.txt");
    if (!fin) {
        cout << "Input file not found.";
        exit(1);
    }

    int n, testcase = 0;
    fin >> testcase;
    for (int i = 1; i <= testcase; i++) {
        
        fin >> n;
        int* arr1 = new int[n];
        for (int j = 0; j < n; j++)
            fin >> arr1[j];

        cout << "Case " << i << endl;
        treeNode<int> *tree = buildTree(arr1, 0, n);
        printTree(tree, 0);
        cout << "Is complete? " << (isComplete(tree) ? "Yes" : "No") << endl << endl;
    }

    return 0;
}

