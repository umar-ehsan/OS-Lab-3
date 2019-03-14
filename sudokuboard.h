/* 
Sudoku board definition and utility functions.
*/

#ifndef SUDOKUBOARD_H_
#define SUDOKUBOARD_H_


#define NUM_VALUES 9 // possible values in a square are 1-9, similarly 9 rows and columns in the board


typedef struct {
    int curr_val[NUM_VALUES][NUM_VALUES][NUM_VALUES + 1];
} board;

extern board *create_board(void);

extern void set_value(int row, int col, int value, board *board);

extern int get_value(int row, int col, board *board);

extern void print_board(board *board);

#endif /* SUDOKUBOARD_H_ */