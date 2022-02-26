/*
 * Basic Sudoku Solving Engine in C
 * Copyright (c) 2022 Spandan Roy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Loads the board from the file
void load_sudoku(int sudoku[9][9], char *filename){
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("Error opening file\n");
		return;
	}
	int i, j;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			fscanf(fp, "%d", &sudoku[i][j]);
		}
	}
	fclose(fp);
	return;
}

//Checks if the guess is valid
int isValid(int sudoku[9][9], int row, int col, int num)
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		if (sudoku[row][i] == num)
			return 0;
	}
	for (i = 0; i < 9; i++)
	{
		if (sudoku[i][col] == num)
			return 0;
	}
	//grid rule
	for (i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++)
	{
		for (j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
		{
			if (sudoku[i][j] == num)
				return 0;
		}
	}
	return 1;
}

//Solves the sudoku
//Returns 1 if solved, 0 if not
//Recursive function
int solve(int sudoku[9][9], int row, int col)
{
	if (row == 9)
		return 1;
	if (col == 9)
		return solve(sudoku, row + 1, 0);
	if (sudoku[row][col] != 0)
		return solve(sudoku, row, col + 1);
	for (int i = 1; i <= 9; i++)
	{
		if (isValid(sudoku, row, col, i))
		{
			sudoku[row][col] = i;
			if (solve(sudoku, row, col + 1))
				return 1;
		}
	}
	sudoku[row][col] = 0;
	return 0;
}

//Prints the sudoku
void print_sudoku(int sudoku[9][9]){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			printf("%d ", sudoku[i][j]);
			if(j == 2 || j == 5){
				printf("| ");
			}
		}
		if (i == 2 || i == 5){
			printf("\n---------------------\n");
		}
		else{
			printf("\n");
		}
	}
}


int main(int argc, char** argv){
	
	//get filename from argv
	char *filename = argv[1];
	int sudoku[9][9];
	load_sudoku(sudoku, filename);
	
	printf("Given sudoku:\n");
	print_sudoku(sudoku);
	
	float start = clock();
	
	solve(sudoku, 0, 0);
	printf("\nSolved sudoku:\n");
	print_sudoku(sudoku);
	printf("\n");
	
	float end = clock();
	printf("Time taken: %f\n", (end - start) / CLOCKS_PER_SEC);
	return 0;
}
