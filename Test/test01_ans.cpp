/* 
 * Student Name:
 * Student ID:
 *
 * Question 1: 
 * Complete the three functions specified below. Do not modify any other parts outside the
 * functions such as adding additional classes, functions, variables and headers.
 * 
 * Question 2:
 * Write down the Big-O time complexity of the three functions implemented by you.
 * a) String::String
 * b) String::append
 * c) String::indexOf 
 * 
 * Your Answers:
 * a)
 * 
 * b)
 * 
 * c)
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

/*
 * Linked list node.
 * Each node represents one character in the String class.
 */
struct node {
	char data;
	node* next;

	node(int data, node* next) {
		this->data = data;
		this->next = next;
	}
};

/*
 * String class.
 * This class uses a linked list to store a sequence of characters of 
 * the string. The internal linked list always has a dummy header node.
 */
class String {

	private:
	node* list;							// internal linked list of characters

	public:
	String() {
		list = new node(0, NULL);		// dummy header stores a zero
	}

	~String() {							// free all nodes in the linked list
		node* temp;
        while (list != NULL) {
            temp = list;
            list = list->next;
            delete temp;
        }
	}

	// A friend function to print String object to stream
	friend std::ostream& operator<<(std::ostream& os, String& str);

	// These three member functions are to be implemented by you.
	// See the description below.
	String(const char* str);		
	String& append(const String& other);
	int indexOf(const String& other);

};

ostream& operator<<(ostream& os, String& str) {
	node* cur = str.list->next;
	while (cur != NULL) {
		os << cur->data;
		cur = cur->next;
	}
	return os;
}


// *************************** DO NOT MODIFY THE CODE ABOVE ******************************

//-------------------------- functions to be implemented by you --------------------------

/*
 * String constructor.
 * Construct a String object based on the c-string input.
 * 
 * For example:
 * Input str: ['a','b','c','\0']
 * Output String's internal list:	list->[0]->['a']->['b']->['c']->NULL 
 */
String::String(const char* str){
	list = new node(0, NULL);		// dummy header
	node* cur = list;
	int i=0;
	while(str[i] != '\0') {
		cur->next = new node(str[i++], NULL);
		cur = cur->next;
	}
}

/*
 * Append the String 'other' to the String 'this'.
 * The operation should copy the nodes from 'other' to 'this'. The input 'other'
 * should not be modified. It returns a reference of the String object itself.
 * 
 * Precondition: 'this' and 'other' are not the same String object
 * 
 * For example: (the examples showing the internal list of the String objects)
 * Before:
 * 		this: 	list->[0]->['a']->['p']->['p']->NULL 
 * 		other: 	list->[0]->['l']->['e']->['s']->NULL 
 * After:
 * 		this: 	list->[0]->['a']->['p']->['p']->['l']->['e']->['s']->NULL 
 * 		other: 	list->[0]->['l']->['e']->['s']->NULL 
 */
String& String::append(const String& other) {

	node* cur = list;
	while(cur->next != NULL) {
		cur = cur->next;			// move to last node
	}

	node* that = other.list->next;
	while(that != NULL) {
		cur->next = new node(that->data, NULL);
		cur = cur->next;
		that = that->next;
	}
	return *this;
}

/*
 * Search the String 'other' from the String 'this'. If the string is found, it
 * returns the index (the n-th character) of the first occurance of the string. 
 * Otherwise, it returns -1.
 * 
 * For example: (the examples showing the internal list of the String objects)
 * Case 1:
 * 		this: 	list->[0]->['a']->['p']->['p']->['l']->['e']->['s']->NULL 
 * 		other: 	list->[0]->['a']->['p']->['p']->NULL 
 * 		Output index:  	0
 * Case 2:
 * 		this: 	list->[0]->['a']->['p']->['p']->['l']->['e']->['s']->NULL 
 * 		other: 	list->[0]->['l']->['e']->['s']->NULL 
 * 		Output index:  	3
 * 
 * For empty strings, please refer to the test cases in the main function.
 * 
 */
int String::indexOf(const String& other) {

	node* start = list->next;
	node* that = other.list->next;
	int index = 0;

	if(start == NULL && that == NULL)		// both are empty strings
		return 0;

	if(start == NULL && that != NULL)		// one of them is empty
		return -1;
	
	if(start != NULL && that == NULL)
		return -1;

	while(start != NULL) {					// start comparing

		node* cur = start;
		
		while(that != NULL && cur != NULL && cur->data == that->data) {
			cur = cur->next;
			that = that->next;
		}
		
		if(that == NULL)					// find 'other'
			return index;
		else if(cur == NULL)				// cannot find 'other'
			return -1;
		else {								// the pair of comparing chars are different
			index++;						// move to start->next
			start = start->next;
			that = other.list->next; 		// reset to the beginning
		}
	}

	return -1;								// cannot find 'other'
}

// ************************ DO NOT MODIFY THE CODE BELOW *************************

//-------------------------- functions prepared for you --------------------------

/*
 * Driver program
 *
 * Run to test your String implementation. 
 * Expected outputs are written in the comments.
 * 
 * Outputs:
 * Hello
 * World!
 * Hello World!
 * Hello World!
 * World!World!
 * 0
 * -1
 * -1
 * 2
 * -1
 */
int main() {

	String s1("Hello");
	String s2("World!");
	cout << s1 << endl;													// Hello
	cout << s2 << endl;													// World!

	String &s3 = s1.append(String(" ")).append(s2);		// use reference as operator= is not overloaded
	cout << s1 << endl;													// Hello World!
	cout << s3 << endl;													// Hello World!
	cout << String("").append(s2).append(String()).append(s2) << endl;	// World!World!

	cout << String("").indexOf(String("")) << endl;						// 0
	cout << String("").indexOf(String("abc")) << endl;					// -1
	cout << String("abc").indexOf(String("")) << endl;					// -1
	cout << String("ababcabcab").indexOf(String("abc")) << endl;		// 2
	cout << String("ababababab").indexOf(String("abc")) << endl;		// -1

	return 0;
}

