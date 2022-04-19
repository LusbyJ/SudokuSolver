/** 
 * Program to read and solve sudoku puzzles
 * */
#include<stdio.h>
#include<string.h>

int puzzle[9][9];                    //Array to store puzzle
void solvePuzzle(int row, int col); //Prototype function

/**
 * Reads in a new puzzle and prints it out.
 * If the puzzle is not 81 character, return 1(error)
 * If end of input file reached return 2
 */
int getPuzzle()
{
    int c, isError = 0, charCount = 0;
    while((c = getchar()) != '\n')
    {
        if(c == EOF)
        {
            return 2;
        }
        printf("%c", c);

        if(charCount <=81)
        {
            if(c == '.')
            {
                puzzle[charCount/9][charCount%9] = 0;
            }
            else if(c >= '1' && c <= '9')
            {
                puzzle[charCount/9][charCount%9] = c - '0';
            }
            else
            {
                isError = 1;
            }
        }
        charCount++; 
    }
    return isError || charCount != 81;
}

/**
 * Tests if the puzzle is valid before trying to solve.
 * Prints and error message if the puzzle is invlaid
 * Return 0 if valid
 * */
int checkValidity()
{
    int invalid = 0, row = 0, col = 0;
    int y, z;

    for(y = 1; y < 10; y++)
    {
        int row;
        for(row = 0; row < 9; row++)
        {
            if(puzzle[row][col] == y)
            {
                invalid++;
                if(invalid > 1)
                {
                    printf("\nError");
                    return 1;
                }
            }
        }
        invalid = 0;
    }

    for(z = 1; z < 10; z++)
    {
        int i, j;
        row = (row/3)*3;
        col = (col/3)*3;
        for(i = 0; i < 3; i++)
        {
            for(j = 0; j < 3; j++)
            {
                if(puzzle[row+i][col+i] == z)
                {
                    invalid++;
                    if(invalid > 1)
                    {
                        printf("\nError");
                        return 1;
                    }
                }
            }
        }
        invalid = 0;
    }
    return 0;
}

/**
 * Loop over each column of the row,
 * Check if any number in the row is the same as the current guess
 * If guessed number passes check and can be used, return 1, zero otherwise
 */
int checkRow(int row, int guess)
{
    int col;
    for(col = 0; col < 9; col++)
    {
        if(puzzle[row][col] == guess)
        {
            return 0;
        }
    }
    return 1;
}

/**
 * Loop through all rows of each column
 * Check if any number is the same as the current guess
 * If current guess works return 1, zero otherwise
 */
int checkCol(int col, int guess)
{
    int row;
    for(row = 0; row < 9; row++)
    {
       if(puzzle[row][col] == guess)
       {
           return 0;
       }  
    }
    return 1;
}

/**
 * Loop over each of the 9 different 3x3 grids
 * If the current guess works return 1, zero otherwise
 */
int checkGrid(int row, int col, int guess)
{
    int i, j;
    row = (row/3)*3;
    col = (col/3)*3;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(puzzle[row+i][col+j] == guess)
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Shifts the current column or row to the right by 1
 */
void shiftCell(int row, int col)
{
    if(col<8)
    {
        solvePuzzle(row, col+1);
    }
    else
    {
        solvePuzzle(row+1,0);
    }
}

/**
 * Prints the solution to the puzzle if it exists
 */
int printSolution(int row, int col)
{
    printf("\n");
    for(row = 0; row < 9; row++)
    {
        for(col = 0; col < 9; col++)
        {
            printf("%d", puzzle[row][col]);
        }
    }
    return 1;
}

/**
 * Solves the sudoku puzzle by looping through guesses and calling the check functions
 * for row, col, and 3x3 grid
 */
void solvePuzzle(int row, int col)
{
    int guess;
    if(row > 8 && col != 0)
    {
        printSolution(0,0);
    }
    if(puzzle[row][col] != 0)
    {
        shiftCell(row, col);
    }
    else
    {
        for(guess = 1; guess <= 9; guess++)
        {
            if((checkRow(row, guess) == 1) && (checkCol(col, guess) == 1) && (checkGrid(row, col, guess) == 1))
            {
                puzzle[row][col] = guess;
                shiftCell(row, col);
            }
        }
        puzzle[row][col] = 0;
    }
}

/**
 * Main function and entry point for program.
 * First calls get puzzle to get puzzle, then check
 * puzzle validity.  If no invalid data found, solve puzzle
 */
int main(void)
{
    int row = 0, col = 0, ret;
    while((ret = getPuzzle()) != 2)
    {
        if(ret == 1)
        {
            printf("\nError");
        }
        else if(checkValidity() != 1) 
        {
            solvePuzzle(row, col);
        }
        printf("\n\n");
    }
    return 0;
}