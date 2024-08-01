/* 
 *
 * Find the last occurrence of the longest substring without repeating characters.
 * You are asked to implement the function longestSubstring() as specified below.
 * 
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define MAX_LENGTH 1000      // the max allowed input string length


struct Substring {          // the structure used to store the function output
    int start;              // the start position of the longest substring
    int length;             // the length of the longest substring
};

//-------------------------- functions to be implemented by you

/*
 * Given a c-string str, find the last occurrence of the longest substring without repeating characters. 
 *  
 * Return a Substring object having the start position and the length of the longest substring.
 * 
 * Precondition: the input string str is non-empty and contains ASCII characters only.
 * 
 * Time Complexity Requirement: O(n)
 * 
 */
Substring longestSubstring(char *str) {

    int lastIndex[256];                  // for 8-bit ASCII char
    for (int i = 0; i < 256; i++)        // initilaize to -1
        lastIndex[i] = -1;              

    size_t n = strlen(str);
    int start = 0;                              // start pos of substr
    int length = 1;                             // length of substr
    lastIndex[str[start]] = 0;                  // mark pos of first letter
    Substring longest = {start, length};        // start = 0, length = 1

    for (int i = 1; i < n; i++) {

        // if found a repeating char in the current substring
        if (lastIndex[str[i]] >= start) {
            start = lastIndex[str[i]] + 1;
        } 

        lastIndex[str[i]] = i;
        length = i - start + 1;
        if (length >= longest.length) {
            longest.length = length;
            longest.start = start;
        }
    }

    return longest;
}


//-------------------------- functions prepared for you

/*
 * Driver program
 * 
 * Read the test cases from the input file and use them to test 
 * your implementation of longestSubstring().
 * 
 */
int main(int argc, char** argv) {

    char str[MAX_LENGTH]; // buffer

    ifstream fin("tut02_input.txt");
    if (!fin) {
        cout << "Input file not found.";
        exit(1);
    }

    int testcase = 0;
    fin >> testcase;

    for (int i = 0; i < testcase; i++) {
        fin >> str;
        Substring longest = longestSubstring(str);
        cout << "Case " << i + 1 << endl;
        printf("The substring (%d,%d) is %.*s\n", longest.start, longest.length, longest.length, str + longest.start);
        cout << endl;
    }

    fin.close();

    return 0;
}

