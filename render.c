#include "conway.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

void render_cell(SDL_Renderer *renderer, int x, int y, int state, int size)
{
    SDL_Rect cell = {.x = x, .y = y, .w = size, .h = size};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    if (state)
    {
        SDL_RenderFillRect(renderer, &cell);
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &cell);
}

void draw(SDL_Renderer *renderer, Matrix *board, int size)
{
    SDL_RenderClear(renderer);
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            render_cell(renderer, i * size, j * size, MAT_AT(board, i, j), size);
        }
    }
    SDL_RenderPresent(renderer);
}

void event_loop(SDL_Renderer *renderer, Matrix *board, int size)
{
    SDL_Event event;
    Uint32 lastUpdateTime = SDL_GetTicks();
    Uint32 deltaTime = 0;
    int x, y;

    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_QUIT:
                return;

            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                MAT_AT(board, x / size, y / size) = 1;
                break;
            }
        }

        deltaTime = SDL_GetTicks() - lastUpdateTime;

        if (deltaTime >= 50)
        {
            draw(renderer, board, size);
            next_generation(board);
            lastUpdateTime = SDL_GetTicks();
        }
    }
}

int main(int argc, char **argv)
{
    srand(time(0));
    int INIT_WIDTH;
    int INIT_HEIGHT;
    int CELL_SIZE;
    if (argc == 4)
    {
        INIT_WIDTH = atoi(argv[1]);
        INIT_HEIGHT = atoi(argv[2]);
        CELL_SIZE = atoi(argv[3]);
    }
    else
    {
        INIT_WIDTH = 1920;
        INIT_HEIGHT = 1080;
        CELL_SIZE = 5;
    }
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Game of life", 0, 0, INIT_WIDTH, INIT_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int board_size = INIT_WIDTH / CELL_SIZE * INIT_HEIGHT / CELL_SIZE;
    Matrix *board = alloc_board(INIT_WIDTH / CELL_SIZE, INIT_HEIGHT / CELL_SIZE);
    init_board(board, board_size / 5);

    event_loop(renderer, board, CELL_SIZE);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
