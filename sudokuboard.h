/* 
Sudoku board definition and utility functions.
*/

#ifndef SUDOKUBOARD_H_
#define SUDOKUBOARD_H_


#define NUM_VALUES 9 // possible values in a square are 1-9, similarly 9 rows and columns in the board

// sudoku board struct
typedef struct {
    int curr_val[NUM_VALUES][NUM_VALUES];
} board;

// creates a new board
extern board *create_board(void);

// prints the sudoku board
extern void print_board(board *board);

#endif /* SUDOKUBOARD_H_ */