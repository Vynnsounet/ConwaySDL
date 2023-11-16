#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAT_AT(m, i, j) (m)->data[(i) * (m)->cols + (j)]
#define CLEAR() printf("\e[1;1H\e[2J")

typedef struct
{
    int rows;
    int cols;
    int *data;

} Matrix;

Matrix *alloc_board(int rows, int cols);
void init_board(Matrix *board, int cell_number);
void next_generation(Matrix *board);
