//basic sudoku solver
//
//sample input file:
//_23___81_
//_____15_3
//5__6_____
//34_7_2___
//_____3_8_
//_651____7
//____46_2_
//296_173_4
//13__59768

#include <stdio.h>
#include <time.h>
void print_sudoku(int sudoku[9][9]);

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

	return;
}


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
	//print_sudoku(sudoku);
	//getchar();
	return 0;
}

void print_sudoku(int sudoku[9][9]){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
}
int main(){
	/*int sudoku[9][9] = {
		{2,0,0,3,0,0,0,0,0},
		{8,0,4,0,6,2,0,0,3},
		{0,1,3,8,0,0,2,0,0},
		{0,0,0,0,2,0,3,9,0},
		{5,0,7,0,0,0,6,2,1},
		{0,3,2,0,0,6,0,0,0},
		{0,2,0,0,0,9,1,4,0},
		{6,0,1,2,5,0,8,0,9},
		{0,0,0,0,0,1,0,0,2}
	};*/
	int sudoku[9][9];
	load_sudoku(sudoku, "./tes.sud");
	printf("Given sudoku:\n");
	print_sudoku(sudoku);
	float start = clock();
	solve(sudoku, 0, 0);
	printf("\nSolved sudoku:\n");
	print_sudoku(sudoku);
	printf("\n");
	float end = clock();
	printf("Time taken: %f\n", (end - start) / CLOCKS_PER_SEC);
}
