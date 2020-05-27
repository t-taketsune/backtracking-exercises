#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define QUEEN 1

/* Utility function to print the board. */
void print_matrix(int **m, int size) {
    for (int i=0; i!=size; i++) {
        for (int j=0; j!=size; j++)
            printf(" %d", m[i][j]);
        printf("\n");
    }
}

/* Utility function to start the board. */
void init_matrix(int **m, int size) {
    for (int i=0; i!=size; i++)
        for (int j=0; j!=size; j++)
            m[i][j]=0;
}

/* Free memory used by board */
void destroy_matrix(int **m, int size) {
    for (int i=0; i!=size; i++) {
        for (int j=0; j!=size; j++)
            free(&m[i][j]);
        free(&m[i]);
    }
}

/* Utility function to check if position is contained in the board. */
int valid_position(int row, int col, int size) {
    if (row < 0 || col < 0 || row > size || col > size)
        return 0;
    return 1;
}

/* Utility function to check if position can receive a queen. */
int check(int **m, int row, int col, int size) {
    int i, j;

    /* Checking row and column. */
    for (i=0; i!=size; i++)
        if (m[row][i] != EMPTY || m[i][col] != EMPTY)
            return 0;
    j = abs(row-col);
    i = 0;
    /* Checking first diagonal. */
    for (int index=0; index!=size; index++) {
        if (!valid_position(i, j, size))
            break;
        if (m[i][j] != EMPTY)
            return 0;
        i++;
        j++;
    }
    j = abs(row+col);
    i = 0;
    /* Checking second diagonal.*/
    for (int index=0; index!=size; index++) {
        if (!valid_position(i, j, size))
            break;
        if (m[i][j] != EMPTY)
            return 0;
        i++;
        j++;
    }
    return 1;
}

/* Function to solve the N-Queens problem. */
int queens(int **m, int row, int col, int size) {

    /* Once we've placed one queen on every row, it is finished */
    if (row >= size)
        return 1;

    /* If we reach the end of the row with no columns placed, backtrack. */
    if (col >= size)
        return 0;

    /* If it is possible to place a queen on given position, try it. */
    if (check(m, row, col, size)) {
        m[row][col]=QUEEN;

        /* If the puzzle is solvable with a queen on this position, return success. */
        if (queens(m, row+1, 0, size))
            return 1;
        else {
            /* If not, try the next column. */
            m[row][col]=EMPTY;
            return queens(m, row, col+1, size);
        }
    }
    else /* If not, try the next column. */
        return queens(m, row, col+1, size);
}

int main() {
    /* Declaring size variable, reading input for size and declaring board accordingly. */
    int size, **board;
    scanf("%d", &size);

    /* Allocating space for the board matrix. */
    board = malloc(sizeof(int*)*size);
    if (!board)
        return 0;
    for (int i=0; i!=size; i++) {
        board[i] = malloc(sizeof(int)*size);
        if (!board[i])
            return 0;
    }

    /* Initiating board matrix. */
    init_matrix(board, size);

    /* This algorithm will output one solution, or return 0 for no solutions possible. */
    if (queens(board, 0, 0, size))
        print_matrix(board, size);
    else
        printf("No solutions possible.");

    /* Free memory. */
    destroy_matrix(board, size);
    return 1;
}
