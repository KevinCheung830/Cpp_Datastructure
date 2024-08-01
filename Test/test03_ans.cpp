/*
 * Student Name:
 * Student ID:
 * 
 * =======================================================================================================
 * 
 * Question 1:
 * 
 * Given a binary tree, flip the tree as shown in the example below:
 * 
 * Before flipping:
 *      (3)
 * (1)
 *      (2)
 * 
 * After flipping:
 *      (2)
 * (1)
 *      (3)
 * 
 * For more examples, you can refer to the test cases in the input file.
 * 
 * =======================================================================================================
 * 
 * (a) Complete the function reflip(). This function must be implemented using a "recursive" approach.
 * Do not modify any other parts outside the functions such as adding additional classes, functions, 
 * variables and headers.
 * 
 * =======================================================================================================
 * 
 * (b) Complete the function flip(). This function must be implemented using a "non-recursive" approach.
 * Do not modify any other parts outside the functions such as adding additional classes, functions, 
 * variables and headers.
 * 
 * =======================================================================================================
 * 
 * (c) Analyse the time and space complexity of the recursive function reflip(). Write down the Big-O notations.
 * 
 * Your Answer:
 * (i)      Time Complexity of reflip(): O(n)                   // visit every node once
 * (ii)     Worse-case space complexity of reflip(): O(n)       // DFS: skewed/list-like tree
 * (iii)    Best-case space complexity of reflip(): O(log n)    // DFS: balanced/complete tree
 * 
 * =======================================================================================================
 * 
 * (d) Analyse the time and space complexity of the iterative function flip(). Write down the Big-O notations.
 * 
 * Your Answer:
 * (i)      Time Complexity of flip(): O(n)                     // visit every node once
 * (ii)     Worse-case space complexity of flip(): O(n)         // BFS: balanced/complete tree
 * (iii)    Best-case space complexity of flip(): O(1)          // BFS: skewed/list-like tree
 * 
 * =======================================================================================================
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

// ************************ DO NOT MODIFY THE CODE ABOVE *************************

//-------------------------- functions to be implemented by you --------------------------

/**
 * Given the root of a binary tree, flip the tree and return its root.
 * This function must be implemented using a recursive approach.
 * This function must not modify any nodes'key of the given tree or create any additional nodes.
 */
treeNode<int>* reflip(treeNode<int>* root) {

    // base case: empty tree
    if (root == NULL)
        return root;
    
    treeNode<int>* left = reflip(root->left);
    treeNode<int>* right = reflip(root->right);
    root->left = right;
    root->right = left;
    return root;
}

/*
 * Given the root of a binary tree, flip the tree and return its root.
 * This function must be implemented using a non-recursive approach.
 * This function must not modify any nodes'key of the given tree or create any additional nodes.
 * 
 * Hints: using queue to perform level-order traversal
 */
treeNode<int>* flip(treeNode<int>* root) {
    
    if (root == NULL)
        return root;
    
    queue<treeNode<int>*> mqueue;   
    mqueue.push(root);         

    while(!mqueue.empty()){    
        
        treeNode<int> *cur = mqueue.front();  
        mqueue.pop();                     
                 
        if(cur->left != NULL)       
            mqueue.push(cur->left);
        
        if(cur->right != NULL)       
            mqueue.push(cur->right);
        
        // exchange left and right subtrees
        treeNode<int>* tmp = cur->left;
        cur->left = cur->right;
        cur->right = tmp;
    }

    return root;
}

// ************************ DO NOT MODIFY THE CODE BELOW *************************

//-------------------------- functions prepared for you --------------------------

/*
 * Print a binary tree (with -90 degree rotation).
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
 * an empty tree cur.
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
 * your implementation.
 *
 */
int main(int argc, char** argv) {

    ifstream fin("test03_input.txt");
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

        cout << "Case " << i + 1 << endl;
        cout << "Before flipping:" << endl;
        treeNode<int> *tree = buildTree(arr, 0, n);
        printTree(tree, 0);

        cout << "After flipping (recursive):" << endl;
        tree = reflip(tree);
        printTree(tree, 0);

        cout << "After flipping (non-recursive):" << endl;
        tree = flip(buildTree(arr, 0, n));
        printTree(tree, 0);
        
        cout << endl;
        delete[] arr;
    }

    fin.close();
    return 0;
}

