#include "conway.h"

void print_mat(Matrix *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            printf("%s ", MAT_AT(m, i, j) ? "\033[38;255;0;0;0m#\033[0m" : "\033[38;0;0;0;0m.\033[0m");
        }
        printf("\n");
    }
}

Matrix *alloc_board(int rows, int cols)
{
    Matrix *m = malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = calloc(sizeof(int), rows * cols);
    return m;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shuffle(int *arr, int size)
{
    int index;
    for (int i = size - 1; i >= 0; i--)
    {
        index = rand() % (i + 1);
        swap(&arr[i], &arr[index]);
    }
}

void init_board(Matrix *board, int cell_number)
{
    assert(cell_number <= board->rows * board->cols);
    for (int i = 0; i < cell_number; i++)
        board->data[i] = 1;
    shuffle(board->data, board->cols * board->rows);
}

int in_board(Matrix *board, int i, int j)
{
    return i >= 0 && i < board->rows && j >= 0 && j < board->cols;
}

int survive_state(int state, int nb_neighbours)
{
    return (nb_neighbours == 2 && state) || nb_neighbours == 3;
}

int count_neighbours(Matrix *board, int i, int j)
{
    int coordinates[8][2] = {{i - 1, j - 1}, {i, j - 1},     {i + 1, j - 1}, {i - 1, j},
                             {i + 1, j},     {i - 1, j + 1}, {i, j + 1},     {i + 1, j + 1}};
    int c = 0;
    for (int i = 0; i < 8; i++)
    {
        int x = coordinates[i][0], y = coordinates[i][1];
        if (in_board(board, x, y) && MAT_AT(board, x, y))
            c++;
    }
    return c;
}

void next_generation(Matrix *board)
{
    Matrix old_board = {.cols = board->cols, .rows = board->rows, .data = board->data};
    board->data = calloc(sizeof(int), board->rows * board->cols);

    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            MAT_AT(board, i, j) = survive_state(MAT_AT(&old_board, i, j), count_neighbours(&old_board, i, j));
        }
    }
    free(old_board.data);
}
