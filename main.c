/*
gcc main.c -Isrc\include -Lsrc\lib -lmingw32 -lSDL2main -lSDL2 -o main.exe
*/
#include <SDL2/SDL.h> //Simple DirectMedia Layer (SDL) 
#include <stdio.h>
#include <math.h>
#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff

struct Circle{
    double x, y, radius;
};

void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color){
    double radius_squared = pow(circle.radius, 2);
    for (double x=circle.x-circle.radius; x<=circle.x+circle.radius; x++){
        for (double y=circle.y-circle.radius; y<=circle.y+circle.radius; y++){
            double distance_squared = pow(x - circle.x, 2) + pow(y-circle.y, 2);
            if (distance_squared < radius_squared){
                SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }

}
int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Raytracing", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN 
    );

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Rect rect = (SDL_Rect) {200, 200, 200, 200};
    SDL_FillRect(surface, &rect, COLOR_WHITE);
    
    // FillCircle(surface, COLOR_WHITE);


    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);

}