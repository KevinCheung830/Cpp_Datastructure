/*
 * Instructions:
 * 
 * 1. Only complete the functions specified below. Do not create any additional function.
 * 2. Use Visual Studio 2019 to build, test and run your code.
 * 3. Do not include any additional header or library.
 * 4. This is an exercise of linked list operations. Do not copy linked lists to arrays for manipulation.
 *
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#define MAX_LENGTH 1000      // the max allowed input length

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
 * Given a non-negative integer as a numerical c-string, build a linked list that stores each digit in 
 * a node. The first node is the least significant digit (LSD). You need to convert the numerical character 
 * to the corresponding int value.
 * 
 * The function returns a pointer to the first node (LSD) of the list.
 *  
 * Precondition: number of digits > 0
 * 
 * Example:
 * Given number:	123 in c-string format: {'1','2','3','\0'}
 * Output list:		[3]-> [2]-> [1]-> NULL
 * 
 */
node* buildReverseList(char* number) {
	
	// inserting at the front
	node *head = NULL, *cur = NULL;
	int i = 0;
	while (number[i] != '\0') {
		cur = new node(number[i++] - '0', head);
		head = cur;
	}
		
	return head;
}

/*
 * Given two linked lists representing two non-negative integers in the LSD-first order, calculate their sum
 * and return a new linked list to represent the sum in the same format. 
 * 
 * You should traverse the linked-lists to perform addition digit by digit. Do not copy the numbers to arrays.
 * 
 * Precondition: num1 and num2 are non-empty.
 * 
 * Post-condition: num1 and num2 are unaltered.
 * 
 * Space and Time Complexity Requirement: O(n)
 * 
 * Example:
 * Given number 1:	123
 * Given number 2:	456
 * Output list:		[9]-> [7]-> [5]-> NULL
 * 
 */
node* addNumbers(node* num1, node* num2) {

	node dummy(0, NULL);		// use a dummy header to make it easier to append nodes
	node* cur = &dummy;			// this dummy header will be removed automatically when this function returns

	int carry = 0;
	while (num1 != NULL || num2 != NULL) {

		int x = (num1 != NULL) ? num1->data : 0;
		int y = (num2 != NULL) ? num2->data : 0;
		int sum = carry + x + y;
		carry = sum / 10;
		cur->next = new node(sum % 10, NULL);

		cur = cur->next;

		if (num1 != NULL)
			num1 = num1->next;

		if (num2 != NULL)
			num2 = num2->next;
	}

	if (carry > 0) {
		cur->next = new node(carry, NULL);
	}

	return dummy.next;		// skip the dummy header
}


//-------------------------- functions prepared for you

/*
 * Helper functions for linked list.
 */
class ListHelper {
public:

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
int main() {

	char number[MAX_LENGTH];	// buffer

	ifstream fin("tut04_input.txt");
	if (!fin) {
		cout << "Input file not found.";
		exit(1);
	}

	int testcase;
	fin >> testcase;

	for (int i = 0; i < testcase; i++) {

		cout << "Case " << i + 1 << endl;

		fin >> number;
		node* num1 = buildReverseList(number);
		fin >> number;
		node* num2 = buildReverseList(number);

		node* sum = addNumbers(num1, num2);

		cout << "Num 1:\t";
		ListHelper::printList(num1);
		ListHelper::deleteList(num1);

		cout << "Num 2:\t";
		ListHelper::printList(num2);
		ListHelper::deleteList(num2);

		cout << "Sum:\t";
		ListHelper::printList(sum);
		ListHelper::deleteList(sum);
		cout << endl;
		
	}

	fin.close();
	return 0;
}

