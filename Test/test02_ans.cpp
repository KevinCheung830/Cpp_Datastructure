/*
 * Student Name:
 * Student ID:
 * 
 * =======================================================================================================
 * 
 * Question 1:
 * 
 * You are given a singly linked-list which contains no header as follow:
 *
 *      Node(0) -> Node(1) -> ... -> Node(n-1) -> Node(n)
 *
 * You are asked to relink the nodes in the following form:
 * 
 *      Node(0) -> Node(n) -> Node(1) -> Node(n-1) -> Node(2) -> Node(n-2) -> ...
 * 
 * You must not replicate any nodes or nodes' data. You should only manipulate the links.
 * 
 * =======================================================================================================
 * 
 * (a) Design an algorithm to solve the problem above and optimize its time complexity. Explain
 * your algorithm with the aid of pseudo code.
 * 
 * Your Answer:
 *      1. push all nodes to a stack one by one
 *      2. pop out half of the nodes from the stack
 *      3. for each node popped from the stack:
 *      4.      insert it after head
 *      5.      move head forward twice
 *      6. end
 * 
 * =======================================================================================================
 * 
 * (b) Analyse the time complexity and space complexity of your algorithm. Write down the Big-O notations.
 * 
 * Your Answer:
 * (i) Time Complexity: O(n)
 * (ii) Space Complexity: O(n)
 * 
 * =======================================================================================================
 * 
 * (c) Complete the function relink(). Do not modify any other parts outside the
 * functions such as adding additional classes, functions, variables and headers.
 * 
 * =======================================================================================================
 * 
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

/* Linked list node */
struct node {
    int data;
    node* next;

    node(int data, node* next) {
		this->data = data;
		this->next = next;
	}
};

//-------------------------- functions to be implemented by you

void relink(node *head) {

    // empty, one node, two nodes
    if ((!head) || (!head->next) || (!head->next->next))
        return;

    // put all node addresses in stack
    stack<node *> myStack;
    node *cur = head;
    int size = 0;
    while (cur != NULL) {
        myStack.push(cur);
        size++;
        cur = cur->next;
    }

    // insert the top node of the stack between every two nodes
    cur = head;
    for (int j = 0; j < size / 2; j++) {
        node *top = myStack.top();
        myStack.pop();
        top->next = cur->next;
        cur->next = top;
        cur = cur->next->next;
    }

    cur->next = NULL; // reset the tail
}

//-------------------------- functions prepared for you

/*
 * Helper class for creating/printing a list from an array.
 */
class ListHelper {
public:
    // build a list based on array input
    static node* newList(int* arr, int n) {

        node dummy(n, NULL);
        node* cur = &dummy;
        for (int i = 0; i < n; i++) {
            cur->next = new node(arr[i], NULL);
            cur = cur->next;
        }
        return dummy.next;      // without dummy header
    }

    //print nodes in a given linked list
    static void printList(node* list) {
        while (list != NULL) {
            printf("[%d]-> ", list->data);
            list = list->next;
        }
        cout << "NULL" << endl;
    }

    //delete nodes in a given linked list
    static void deleteList(node* list) {
        node* temp;
        while (list != NULL) {
            temp = list;
            list = list->next;
            delete temp;
        }
    }
};

/*
 * Driver program
 *
 * Read the test cases from the input file and use them to test
 * your functions' implementation.
 *
 */
int main(int argc, char** argv) {

    ifstream fin("test02_input.txt");
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

        node* list = ListHelper::newList(arr, n);

        cout << "Case " << i + 1 << endl;    
        cout << "Input:\t\t";
        ListHelper::printList(list);

        cout << "Reversed:\t";
        relink(list);
        ListHelper::printList(list);

        ListHelper::deleteList(list);
        delete[] arr;
    }

    fin.close();
    return 0;
}

