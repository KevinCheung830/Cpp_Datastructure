/* 
 * Instructions:
 *
 * 1. Only complete the functions specified below. Do not create any additional function.
 * 2. Use Visual Studio 2019 to build, test and run your code.
 * 3. Do not include any additional header or library.
 *
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>

#define N 5             // chessboard size is NxN
#define INIT_X 0        // initial x position of the knight
#define INIT_Y 0        // initial y position of the knight

using namespace std;

/* 
 * A knight's tour is a sequence of moves of a knight on a chessboard such that the knight visits every square only once. 
 *  
 * A knight can move in these 8 directions. The relative coordinates of the next move 
 * of a knight are defined in xMove[] and yMove[] based on the 8 positions marked below.
 * 
 * xMove[] is for the next value of x coordinate.
 * yMove[] is for the next value of y coordinate.
 * 
        . . . . . . . 
        . . M . M . . 
        . M . . . M . 
        . . . K . . .   where K is at (0,0)
        . M . . . M .   <--- M at (2,1) 
        . . M . M . .   <--- M at (1,2)
        . . . . . . . 
 * 
 */
const int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void printSolution(int sol[N][N]);

//-------------------------- functions to be implemented by you

/* 
 * 
 * This recursive function finds all knight tours that start at (0,0) 
 * and end at (N-1, N-1) using backtracking. It prints out all tours
 * found. 
 * 
 * - The argument (x,y) indicates the current position of knight. 
 * - The argument 'step' indicates the n-th move of the tour. 
 * - The argument chessboard[][] is the chessboard. 
 * - The argument 'count' is the number of solutions found. 
 * 
 */
void solve(int x, int y, int step, int chessboard[N][N], int& count) {

    int k, nx, ny;

    // based case - path closed
    if (step == N * N && chessboard[N-1][N-1] == (N*N-1)) {
        count++;
        cout << "Solution " << count << ":" << endl;
        printSolution(chessboard);
        cout << endl;
        return;
    }

    /* Try all next moves from the current coordinate x, y */
    for (k = 0; k < 8; k++) {
        nx = x + xMove[k];
        ny = y + yMove[k];

        // check if i,j are valid indexes for N*N chessboard 
        if (nx >= 0 && nx < N && ny >= 0 && ny < N && chessboard[ny][nx] == -1) {
            chessboard[ny][nx] = step;
            solve(nx, ny, step + 1, chessboard, count);
            chessboard[ny][nx] = -1; // backtracking
        }
    }
}

//-------------------------- functions prepared for you

/* 
 * A utility function to print solution matrix sol[N][N] 
 */
void printSolution(int sol[N][N]) {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++)
            cout << setw(3) << sol[x][y];
        cout << endl;
    }
}

/*
 * Driver program to test above functions.
 * 
 * The program should output 304 complete knight tours.
 * Please refer to the expected program output shown below.
 */
int main(int argc, char** argv) {

    // number of solutions (complete tour) found
    int count = 0;       
    
    // initialize chessboard
    int chessboard[N][N];
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            chessboard[x][y] = -1;

    // set the knight to its initial position
    chessboard[INIT_X][INIT_Y] = 0;
    
    // tour starts from (0,0)
    solve(INIT_X, INIT_Y, 1, chessboard, count);

    return 0;
}


/*****************************************************************************
    Expected Program Output
    Note that the output order of these 56 tours can be different.
 *****************************************************************************

 Solution 1:
  0 15 20  7  2
 11  6  1 14 19
 16 21 12  3  8
  5 10 23 18 13
 22 17  4  9 24

Solution 2:
  0 17 12  7  2
 11  6  1 20 13
 16 21 18  3  8
  5 10 23 14 19
 22 15  4  9 24

Solution 3:
  0 17 12  7  2
 11  6  1 16 13
 18 21 14  3  8
  5 10 23 20 15
 22 19  4  9 24

Solution 4:
  0 19 14  9  2
 13  8  1 20 15
 18 21  6  3 10
  7 12 23 16  5
 22 17  4 11 24

Solution 5:
  0  7 18 13  2
 17 12  1  6 19
  8 21 10  3 14
 11 16 23 20  5
 22  9  4 15 24

Solution 6:
  0  7 20 15  2
 19 14  1  6 11
  8 21 12  3 16
 13 18 23 10  5
 22  9  4 17 24

Solution 7:
  0 19 14  7  2
 13  8  1 20 15
 18 21 12  3  6
  9  4 23 16 11
 22 17 10  5 24

Solution 8:
  0 13 18  7  2
 17  8  1 12 19
 14 21 16  3  6
  9  4 23 20 11
 22 15 10  5 24

Solution 9:
  0 13 20  7  2
 19  8  1 12 17
 14 21 18  3  6
  9  4 23 16 11
 22 15 10  5 24

Solution 10:
  0 17 12  7  2
 11  8  1 18 13
 16 21 10  3  6
  9  4 23 14 19
 22 15 20  5 24

Solution 11:
  0 15 20  9  2
  5 10  1 14 19
 16 21  6  3  8
 11  4 23 18 13
 22 17 12  7 24

Solution 12:
  0 11  6 17  2
  5 18  1 12  7
 10 21 14  3 16
 19  4 23  8 13
 22  9 20 15 24

Solution 13:
  0 11  6 15  2
  5 16  1 20  7
 10 21 12  3 14
 17  4 23  8 19
 22  9 18 13 24

Solution 14:
  0 17  6 11  2
  5 12  1 16  7
 18 21  8  3 10
 13  4 23 20 15
 22 19 14  9 24

Solution 15:
  0 19 14  9  2
 13  4  1 20 15
 18 21  8  3 10
  5 12 23 16  7
 22 17  6 11 24

Solution 16:
  0  9 18 13  2
 17  4  1  8 19
 10 21 12  3 14
  5 16 23 20  7
 22 11  6 15 24

Solution 17:
  0  9 20 15  2
 19  4  1  8 13
 10 21 14  3 16
  5 18 23 12  7
 22 11  6 17 24

Solution 18:
  0 17 12  7  2
 11  4  1 18 13
 16 21  6  3  8
  5 10 23 14 19
 22 15 20  9 24

Solution 19:
  0 15 20  5  2
  9  4  1 14 19
 16 21 10  3  6
 11  8 23 18 13
 22 17 12  7 24

Solution 20:
  0 15 10  5  2
  9  4  1 16 11
 14 21 18  3  6
 19  8 23 12 17
 22 13 20  7 24

Solution 21:
  0 15 10  5  2
  9  4  1 20 11
 14 21 16  3  6
 17  8 23 12 19
 22 13 18  7 24

Solution 22:
  0 17 10  5  2
  9  4  1 16 11
 18 21 12  3  6
 13  8 23 20 15
 22 19 14  7 24

Solution 23:
  0  9  4 17  2
 13 18  1 10  5
  8 21 12  3 16
 19 14 23  6 11
 22  7 20 15 24

Solution 24:
  0  9  4 15  2
 11 16  1 20  5
  8 21 10  3 14
 17 12 23  6 19
 22  7 18 13 24

Solution 25:
  0 17  4 11  2
  7 12  1 16  5
 18 21  6  3 10
 13  8 23 20 15
 22 19 14  9 24

Solution 26:
  0 19  4  9  2
  5 10  1 20 15
 18 21 14  3  8
 11  6 23 16 13
 22 17 12  7 24

Solution 27:
  0 15  4  9  2
  5 10  1 14 19
 16 21 18  3  8
 11  6 23 20 13
 22 17 12  7 24

Solution 28:
  0 17  4  9  2
  5 10  1 18 13
 16 21 12  3  8
 11  6 23 14 19
 22 15 20  7 24

Solution 29:
  0  7 18 13 22
 17 12 21  8 19
  4  1  6 23 14
 11 16  3 20  9
  2  5 10 15 24

Solution 30:
  0 11  8 17 22
  9 16 21 12  7
  4  1 10 23 18
 15 20  3  6 13
  2  5 14 19 24

Solution 31:
  0 13  8 19 22
  9 18 21 14  7
  4  1 12 23 20
 17 10  3  6 15
  2  5 16 11 24

Solution 32:
  0  5 16 11 22
 15 10 21  6 17
  4  1 18 23 12
  9 14  3 20  7
  2 19  8 13 24

Solution 33:
  0  5 18 11 22
 19 10 21  6 17
  4  1 14 23 12
  9 20  3 16  7
  2 15  8 13 24

Solution 34:
  0  5 16 11 22
 17 10 21  6 15
  4  1 12 23 20
  9 18  3 14  7
  2 13  8 19 24

Solution 35:
  0  9 16 11 22
 15  4 21  8 17
 20  1 10 23 12
  5 14  3 18  7
  2 19  6 13 24

Solution 36:
  0  9 18 13 22
 17  4 21  8 19
 10  1 12 23 14
  5 16  3 20  7
  2 11  6 15 24

Solution 37:
  0  9 14 17 22
 15  4 21  8 13
 10  1 16 23 18
  5 20  3 12  7
  2 11  6 19 24

Solution 38:
  0  9 14 19 22
 15  4 21  8 13
 10  1 18 23 20
  5 16  3 12  7
  2 11  6 17 24

Solution 39:
  0 19 10  5 22
  9  4 21 18 11
 20  1 14 23  6
 15  8  3 12 17
  2 13 16  7 24

Solution 40:
  0 17 10  5 22
  9  4 21 16 11
 18  1 12 23  6
 13  8  3 20 15
  2 19 14  7 24

Solution 41:
  0 13 18  5 22
 19  4 21 12 17
 14  1  8 23  6
  9 20  3 16 11
  2 15 10  7 24

Solution 42:
  0 11 16  5 22
 17  4 21 10 15
 12  1  6 23 20
  7 18  3 14  9
  2 13  8 19 24

Solution 43:
  0 19 14  9 22
 13  8 21  4 15
 20  1 18 23 10
  7 12  3 16  5
  2 17  6 11 24

Solution 44:
  0 17 14  9 22
 13  8 21  4 15
 18  1 16 23 10
  7 12  3 20  5
  2 19  6 11 24

Solution 45:
  0 13 18  9 22
 19  8 21  4 17
 14  1 12 23 10
  7 20  3 16  5
  2 15  6 11 24

Solution 46:
  0 11 16  9 22
 17  8 21  4 15
 12  1 10 23 20
  7 18  3 14  5
  2 13  6 19 24

Solution 47:
  0  5 16 11 22
 15 10 21  4 17
 20  1  6 23 12
  9 14  3 18  7
  2 19  8 13 24

Solution 48:
  0  5 18 13 22
 17 12 21  4 19
  6  1  8 23 14
 11 16  3 20  9
  2  7 10 15 24

Solution 49:
  0  5 10 17 22
 11 16 21  4  9
  6  1 12 23 18
 15 20  3  8 13
  2  7 14 19 24

Solution 50:
  0  5 10 19 22
 11 18 21  4  9
  6  1 14 23 20
 17 12  3  8 15
  2  7 16 13 24

Solution 51:
  0 19  8 13 22
  7 14 21 18  9
 20  1 12 23  4
 15  6  3 10 17
  2 11 16  5 24

Solution 52:
  0 17  8 11 22
  7 12 21 16  9
 18  1 10 23  4
 13  6  3 20 15
  2 19 14  5 24

Solution 53:
  0 13 18  7 22
 19  8 21 12 17
 14  1  6 23  4
  9 20  3 16 11
  2 15 10  5 24

Solution 54:
  0 11 16  5 22
 15  6 21 10 17
 20  1 12 23  4
  7 14  3 18  9
  2 19  8 13 24

Solution 55:
  0 11 18  5 22
 17  6 21 10 19
 12  1 14 23  4
  7 16  3 20  9
  2 13  8 15 24

Solution 56:
  0 11 16  5 22
 17  6 21 10 15
 12  1 18 23  4
  7 20  3 14  9
  2 13  8 19 24

  
 */