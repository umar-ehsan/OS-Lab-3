/*
Implements the sudoku board with the utility functions
*/

#include <stdlib.h>
#include <stdio.h>
#include "sudokuboard.h"

#define GREEN "\33[1;32m"
#define FLUSH "\33[0m"

board *create_board(void){
    board *new_board = malloc(sizeof(board));
    for (int row = 0; row < NUM_VALUES; row++){
        for (int col = 0; col < NUM_VALUES; col++){
            for (int values = 0; values < NUM_VALUES + 1; values++){
                new_board->curr_val[row][col][values] = values;
            }
        }
    }
    return new_board;    
}

void set_value(int row, int col, int value, board *board){
    board->curr_val[row][col][0] = value;
}

int get_value(int row, int col, board *board){
    return board->curr_val[row][col][0];
}

void print_board(board *board){
    for (int i =0; i < NUM_VALUES; i++){
            printf(" ___");
    }
    printf("\n");
    for (int row = 0; row < NUM_VALUES; row++){
        printf("|");
        for (int col = 0; col < NUM_VALUES; col++){
            if (board->curr_val[row][col][0] == 0){
                printf(" - |");
            }
            else {
                printf( " %s%d%s |", GREEN, board->curr_val[row][col][0], FLUSH);
            }
        }
        printf("\n|");
        for (int i =0; i < NUM_VALUES; i++){
            printf("___|");
        }
        printf("\n");
    }
}
