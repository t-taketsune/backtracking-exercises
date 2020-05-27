/* Algorithm developed using the ANSI Standard for the C language. */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

/* Utility function to print the board. */
void print_board(int **b, int size) {
    for (int i=0; i!=size; i++) {
        for (int j=0; j!=size; j++)
            printf(" %d", b[i][j]);
        printf("\n");
    }
}

/* Utility function to check if position is safe. */
int check(int **b, int size, int row, int col, int key) {
    int i, j;

    /* Checking the row and column of given position. */
    for (i=0; i!=size; i++)
        if (b[row][i] == key || b[i][col] == key)
            return 0;

    /* Checking the 3x3 box containing the position. */
    int box_row = row - (row%3), box_col = col - (col%3);
    for (i=0; i!=3; i++)
        for (j=0; j!=3; j++)
            if (b[i+box_row][j+box_col] == key)
                return 0;
    return 1;
}

/* Function to solve sudoku. */
int sudoku(int **b, int size, int row, int col) {

    /* Once we fill all 9 rows (0->8) with valid numbers, the puzzle is finished. */
    if (row >= size)
        return 1;

    /* Once we fill all columns in given row, jump to next row. */
    if (col >= size)
        return sudoku(b, size, row+1, 0);

    /* If given position already has a given digit, jump to next position. */
    if (b[row][col] != 0)
        return sudoku(b, size, row, col+1);

    /* Iterate through all possible digits trying to find the correct one. */
    for (int i=1; i<=size; i++) {

        /* If position is safe with given digit... */
        if (check(b, size, row, col, i)) {

            /* ...assign it and jump to next position. */
            b[row][col] = i;
            if (sudoku(b, size, row, col+1))
                return 1;
            else /* If digit fails to return finished puzzle, try another digit. */
                b[row][col] = 0;
        }
    }
    /* If no digits lead to a correct answer, backtrack to former position. */
    return 0;
}

int main() {
    /* Declaring board variable and aux variables.*/
    int board[SIZE][SIZE], i, j;

    /* Reading input. */
    for (i=0; i!=SIZE; i++) {
        for (j=0; j!=SIZE; j++)
            scanf("%d ", &board[i][j]);
    }

    /* If there is a solution, print it. Else, inform it's impossible. */
    if (sudoku(board, SIZE, 0, 0))
        print_board(board, SIZE);
    else
        printf("No solutions possible.");
}
