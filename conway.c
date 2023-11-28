#include "conway.h"

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

int survive_state(int state, int nb_neighbours)
{
    return (nb_neighbours == 2 && state) || nb_neighbours == 3;
}

void extend_borders(Matrix *board, int tab[2])
{
    if (tab[0] < 0)
        tab[0] = board->rows - 1;
    if (tab[0] >= board->rows)
        tab[0] = 0;

    if (tab[1] < 0)
        tab[1] = board->cols - 1;
    if (tab[1] >= board->cols)
        tab[1] = 0;
}

int count_neighbours(Matrix *board, int i, int j)
{
    int coordinates[8][2] = {{i - 1, j - 1}, {i, j - 1},     {i + 1, j - 1}, {i - 1, j},
                             {i + 1, j},     {i - 1, j + 1}, {i, j + 1},     {i + 1, j + 1}};
    int x, y, c = 0;
    for (int i = 0; i < 8; i++)
    {
        extend_borders(board, coordinates[i]);
        x = coordinates[i][0], y = coordinates[i][1];
        if (MAT_AT(board, x, y))
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
