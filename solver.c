/* 
Program to solve a sudoku board using multi-threading
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include "solver.h"
#include "sudokuboard.h"



int main(int argc, char *argv[]){
    board *sudoku_board = create_board();
    char *filename;
    if (argc > 2){
        printf("\nWrong invocation of the solver. Usage: ./solver <filename> where filename is optional\n\n");
        return EXIT_FAILURE;
    }
    else if (argc == 2){
        filename = argv[1];
        if(!read_input(filename, sudoku_board)){
            printf("\nError opening specified file.\n\n");
            return EXIT_FAILURE;
        }
    }
    else {
        if(!read_input("puzzle.txt", sudoku_board)){
            printf("\nError opening puzzle.txt\n\n");
            return EXIT_FAILURE;
        }
    }
    printf("\nThe initial board: \n\n");
    print_board(sudoku_board);
    printf("\n");


    return EXIT_SUCCESS;
}

bool read_input(char *filename, board * board){
    FILE *file;
    int row = 0, col = 0;
    char input[BUFFER_SIZE], *token;

    if ((file = fopen(filename, "r"))){
        while (fgets(input, BUFFER_SIZE, file) != NULL){
            token = strtok(input, "\n");
            token = strtok(token, " ");
            board->curr_val[row][col][0] = atoi(token);
            col++;
            for (int i = 0; i < NUM_VALUES - 1; i++){
                token = strtok(NULL, " ");
                board->curr_val[row][col][0] = atoi(token);
                col++;
            }
            row++;
            col = 0;
        }
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}