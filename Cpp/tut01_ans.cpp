/*
 * A set of K numbers is selected from an given array of N non-negative integers. The score 
 * of a set is calculated as the the difference between the smallest and the greatest numbers 
 * in the set. Find the set that has the minimum score.
 *
 * You are asked to implement the functions main() and findMinScore() as specified below.
 *
 * Example:
 *
 * For N = 4 and K = 3,
 * and the array contains: {1, 8, 7, 4}
 *
 * All set combinations:
 * {1, 8, 7} => score is 7
 * {1, 8, 4} => score is 7
 * {1, 7, 4} => score is 6
 * {8, 7, 4} => score is 4
 *
 * Therefore, the min. score is 4.
 *
 */

#include <cstdlib>
//#include <algorithm> 
#include <iostream>
#include <fstream>

using namespace std;


/*
 * Find a set of k numbers in the arr[0..n-1] that has the minimum score, then return the
 * score.
 *
 * Precondition: n >= k >= 1
 *
 */
int findMinScore(int arr[], int n, int k) {

	//sort(arr, arr + n);

	// simple bubble sort
	int temp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	int min = INT_MAX;
	for (int i = 0; i + k - 1 < n; i++) {
		int score = arr[i + k - 1] - arr[i];
		if (score < min) {
			min = score;
		}
	}
	return min;
}


/*
 * Driver program
 *
 * Read the test cases from the given input file and use them to test
 * your implementation of findMinScore().
 *
 */
int main() {

	ifstream fin("tut01_input.txt");
	if (!fin) {
		cout << "Input file not found.";
		exit(1);
	}

	int testcase = 0;
	fin >> testcase;

	for (int i = 0; i < testcase; i++) {

		int n, k;
		fin >> n >> k;
		int* arr = new int[n];
		for (int j = 0; j < n; j++)
			fin >> arr[j];

		cout << "Case " << i + 1 << endl;
		cout << "The min. score is " << findMinScore(arr, n, k);
		cout << endl;	
		delete[] arr;
	}
	
	fin.close();
	return 0;
}

