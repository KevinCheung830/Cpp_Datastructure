/*
 * Instructions:
 *
 * 1. Only complete the functions specified below. Do not create any additional function.
 * 2. Use Visual Studio 2019 to build, test and run your code.
 * 3. Do not include any additional header or library.
 * 4. This is an exercise of linked list operations. Do not copy linked lists to arrays for manipulation.
 * 5. Implement the functions reverseList(), rotateList() and partitionList() as specified below.
 * 6. All linked lists in this exercise are singly-linked, non-circular and without header node.
 * 
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

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

/*
 * The function reverses the input list by re-linking the nodes in 
 * reverse order, and returns its new head. You should not create additional
 * nodes or copy the data in nodes.
 * 
 */
node* reverseList(node* head) {
    node* prev = NULL;
    node* current = head;
    node* next = NULL;
    while (current != NULL) {
        next = current->next;		// save the next node
        current->next = prev;		// flip the next pointer
        prev = current;				// move forward: prev jumps to cur
        current = next;				// move forward: cur jumps to next (i.e. cur->next)
    }
    return prev;
}

/*
 * This function rotates the input list clockwisely by a half of its length
 * (i.e. floor(length/2) nodes) and returns its new head. 
 * 
 * Clockwise rotation means moving the tail node to the front of the list.
 * 
 */
node* rotateList(node* head) {

    if (head == NULL)
        return NULL;

    node *slow, *fast;
    slow = fast = head;
    // fast pointer doubles the speed of slow pointer
    while (fast->next != NULL) {
        fast = fast->next;
        if (fast->next != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
    }

    // fast pointing at tail and slow pointing at the middle
    fast->next = head;
    head = slow->next;
    slow->next = NULL;

    return head;
}

/*
 * The function partition the input list by using the first node as pivot. Nodes 
 * smaller than pivot are moved before the pivot and nodes greater than the pivot
 * are moved after the pivot. The nodes on each side of the pivot should maintain 
 * the same relative order. For example, node 2 should remain in front of node 0
 * in the following output.
 * 
 * Input:      [4]-> [2]-> [0]-> [10]-> [8]-> [6]-> NULL
 * Output:     [2]-> [0]-> [4]-> [10]-> [8]-> [6]-> NULL
 * 
 * It returns the new head of the list, or return NULL if 
 * the list is empty.
 * 
 * Precondition: no duplicate keys (data) in the input list
 */
node* partitionList(node* head) {

    if (head == NULL)
        return NULL;

    node* ppivot = NULL;        // predecessor of pivot
    node* pivot = head;
    node* pcur = head;          // predecessor of cur
    node* cur = head->next;

    while (cur != NULL) {
        if (cur->data < pivot->data) {
            pcur->next = cur->next;		    // jump over the cur node				
            cur->next = pivot;              // insert cur at front of pivot
            if(ppivot == NULL) {
                head = cur;                 // update new head 
            } else {
                ppivot->next = cur;
            }
            ppivot = cur;            
            cur = pcur->next;			    // move forward
        } else {
            pcur = cur;
            cur = cur->next;
        }
    }

    return head;
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

    ifstream fin("tut05_input.txt");
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
        list = reverseList(list);
        ListHelper::printList(list);

        cout << "Rotated:\t";
        list = rotateList(list);
        ListHelper::printList(list);

        cout << "Partitioned:\t";
        list = partitionList(list);
        ListHelper::printList(list);
        cout << endl;

        ListHelper::deleteList(list);
        delete[] arr;
    }

    fin.close();
    return 0;
}

