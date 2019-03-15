/* 
Function definitions for the solver program
*/

#ifndef SOLVER_H_
#define SOLVER_H_
#include "sudokuboard.h"
#include <stdbool.h>

#define BUFFER_SIZE 50 // buffer length for reading the text lines 

// read input from a file and populate the sudoku board
extern bool read_input(char *filename, board *board);

// solve the rows
extern void *row_solve(void *coords);

// solve the columns
extern void *col_solve(void *coords);

// solve the sub-square
extern void *sq_solve(void *coords);

#endif /* SOLVER_H_ */