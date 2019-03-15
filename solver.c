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

board *sudoku_board;

int main(int argc, char *argv[]){
    sudoku_board = create_board();
    char *filename;
    pthread_t row_thread, col_thread, sq_thread;
    int coords[2];
    
    if (argc > 2){
        printf("\nWrong invocation of the solver. Usage: ./solver <filename> where filename is optional\n\n");
        return EXIT_FAILURE;
    }
    else if (argc == 2){
        filename = argv[1];
    }
    else {
        filename = "puzzle.txt";
    }
    if(!read_input(filename, sudoku_board)){
            printf("\nError opening file: %s.\n\n", filename);
            return EXIT_FAILURE;
    }
    printf("\nThe initial board: \n\n");
    print_board(sudoku_board);
    printf("\n");

    for (int row = 0; row < NUM_VALUES; row++){
        for (int col = 0; col < NUM_VALUES; col++){
            if (sudoku_board->curr_val[row][col] == 0){
                coords[0] = row;
                coords[1] = col;
                if (pthread_create(&row_thread, NULL, row_solve, coords)){
                    printf("\nError creating thread...terminating.\n\n");
                    return EXIT_FAILURE;
                }   
                if (pthread_create(&col_thread, NULL, col_solve, coords)){
                    printf("\nError creating thread...terminating.\n\n");
                    return EXIT_FAILURE;
                }
                if (pthread_create(&sq_thread, NULL, sq_solve, coords)){
                    printf("\nError creating thread...terminating.\n\n");
                    return EXIT_FAILURE;
                } 
                
                if (pthread_join(row_thread, NULL)){
                    printf("\nError joining thread 1...terminating.\n\n");
                    return EXIT_FAILURE;
                }
                if (pthread_join(col_thread, NULL)){
                    printf("\nError joining thread 2...terminating.\n\n");
                    return EXIT_FAILURE;
                }
                if (pthread_join(sq_thread, NULL)){
                    printf("\nError joining thread 3...terminating.\n\n");
                    return EXIT_FAILURE;
                }
                
            }
        }
    }

    printf("\nThe solved board: \n\n");
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
            board->curr_val[row][col] = atoi(token);
            col++;
        
            for (int i = 0; i < NUM_VALUES - 1; i++){
                token = strtok(NULL, " ");
                board->curr_val[row][col] = atoi(token);
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

void *row_solve(void *c){
    int *coords = (int *)c;
    int row = coords[0];
    int col = coords[1];
    int curr_val = 1, found = 0;
    while (curr_val <= 9){
        for (int i = 0; i < NUM_VALUES; i++){
            if (sudoku_board->curr_val[row][i] == curr_val){
                curr_val++;
                found = 0;
                break;
            }
            found++;
        }
        if (found == 9){
            break;
        }
    }
    if (curr_val <= 9){
        sudoku_board->curr_val[row][col] = curr_val;
    }
    return NULL;
}

void *col_solve(void *c){
    int *coords = (int *)c;
    int row = coords[0];
    int col = coords[1];
    int curr_val = 1, found = 0;
    while (curr_val <= 9){
        for (int i = 0; i < NUM_VALUES; i++){
            if (sudoku_board->curr_val[i][col] == curr_val){
                curr_val++;
                found = 0;
                break;
            }
            found++;
        }
        if (found == 9){
            break;
        }
    }
    if (curr_val <= 9){
        sudoku_board->curr_val[row][col] = curr_val;
    }
    return NULL;
}

void *sq_solve(void *c){
    int *coords = (int *)c;
    int row = coords[0];
    int col = coords[1];
    int row_start = 3 * (row / 3);
    int col_start = 3 * (col / 3);
    int curr_val = 1, found = 0;
    while (curr_val <= 9){
        for (int i = row_start; i < row_start + 3; i++){
            for (int j = col_start; j < col_start + 3; j++){
                if (sudoku_board->curr_val[i][j] == curr_val){
                    curr_val++;
                    found = 0;
                    break;
                }
                found++;
            }
            if (found == 0){
                    break;
            }
        }
        if (found == 9){
            break;
        }
    }
    if (curr_val <= 9){
        sudoku_board->curr_val[row][col] = curr_val;
    }
    return NULL;
}