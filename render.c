#include "conway.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

void render_cell(SDL_Renderer *renderer, int x, int y, int state)
{
    SDL_Rect cell;
    cell.x = x;
    cell.y = y;
    cell.w = 10;
    cell.h = 10;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    if (state)
    {
        SDL_RenderFillRect(renderer, &cell);
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &cell);
}

void draw(SDL_Renderer *renderer, Matrix *board)
{
    SDL_RenderClear(renderer);
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            render_cell(renderer, i * 10, j * 10, MAT_AT(board, i, j));
        }
    }
    SDL_RenderPresent(renderer);
}

void event_loop(SDL_Renderer *renderer, Matrix *board)
{
    SDL_Event event;
    Uint32 lastUpdateTime = SDL_GetTicks();
    Uint32 deltaTime = 0;

    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return;
            }
        }

        deltaTime = SDL_GetTicks() - lastUpdateTime;

        if (deltaTime >= 50)
        {
            draw(renderer, board);
            next_generation(board);

            lastUpdateTime = SDL_GetTicks();
        }
    }
}

int main(int argc, char **argv)
{

    int INIT_WIDTH;
    int INIT_HEIGHT;
    if (argc != 3)
    {
        INIT_WIDTH = 1920;
        INIT_HEIGHT = 1080;
    }
    else
    {
        INIT_WIDTH = atoi(argv[1]);
        INIT_WIDTH = atoi(argv[2]);
    }
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Game of life", 0, 0, INIT_WIDTH, INIT_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Matrix *board = alloc_board(INIT_WIDTH / 10, INIT_HEIGHT / 10);
    init_board(board, 5000);

    event_loop(renderer, board);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
