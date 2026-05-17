/*
gcc main.c -Isrc\include -Lsrc\lib -lmingw32 -lSDL2main -lSDL2 -o main.exe
*/

#include <SDL2/SDL.h> //Simple DirectMedia Layer (SDL)
#include <math.h>
#include <stdio.h>

int WIDTH;
int HEIGHT;

#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_CIRCLE 0x00000000
#define COLOR_SHADOW_CIRCLE 0x00000000
#define COLOR_RAY 0xffeb77
#define COLOR_RED 0xff0000
#define RAYS_NUMBER 1000
#define RAYS_THICKNESS 1

struct Circle {
    double x, y, radius;
};

struct Ray {
    double x_start, y_start, angle;
};

struct Button {
    int x, y, width, height;
};

// - Function to fill a circle
void FillCircle(SDL_Surface *surface, struct Circle circle, Uint32 color) {
    double radius_squared = pow(circle.radius, 2);
    for (double x = circle.x - circle.radius; x <= circle.x + circle.radius;
         x++) {
        for (double y = circle.y - circle.radius; y <= circle.y + circle.radius;
             y++) {
            double distance_squared =
                pow(x - circle.x, 2) + pow(y - circle.y, 2);
            if (distance_squared < radius_squared) {
                SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

// Function to draw a close button
void DrawCloseButton(SDL_Surface *surface, struct Button button, Uint32 color) {
    // Draw the button background
    SDL_Rect rect = {button.x, button.y, button.width, button.height};
    SDL_FillRect(surface, &rect, color);

    // Draw X
    int padding = button.width / 4;

    // Draw first diagonal line of X
    for (int i = 0; i < button.width / 8; i++) {
        SDL_Rect line1 = {button.x + padding + i, button.y + padding, 1,
                          button.height - 2 * padding};
        SDL_FillRect(surface, &line1, COLOR_BLACK);
    }

    // Draw second diagonal line of X
    for (int i = 0; i < button.width / 8; i++) {
        SDL_Rect line2 = {button.x + button.width - padding - i,
                          button.y + padding, 1, button.height - 2 * padding};
        SDL_FillRect(surface, &line2, COLOR_BLACK);
    }
}

// Function to check if point is inside button
int IsPointInButton(int x, int y, struct Button button) {
    return (x >= button.x && x <= button.x + button.width && y >= button.y &&
            y <= button.y + button.height);
}

void generate_rays(struct Circle circle, struct Ray rays[RAYS_NUMBER]) {
    for (int i = 0; i < RAYS_NUMBER; i++) {
        double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
        struct Ray ray = {circle.x, circle.y, angle};
        rays[i] = ray;
    }
}

void FillRays(SDL_Surface *surface, struct Ray rays[RAYS_NUMBER], Uint32 color,
              struct Circle object) {
    double radius_squared = pow(object.radius, 2);
    for (int i = 0; i < RAYS_NUMBER; i++) {
        struct Ray ray = rays[i];
        int end_of_screen = 0, object_hit = 0;

        double step = 1;
        double x_draw = ray.x_start, y_draw = ray.y_start;

        while (end_of_screen != 1 && object_hit != 1) {
            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);

            SDL_Rect ray_point =
                (SDL_Rect){x_draw, y_draw, RAYS_THICKNESS, RAYS_THICKNESS};
            SDL_FillRect(surface, &ray_point, color);

            if (x_draw < 0 || x_draw > WIDTH) {
                end_of_screen = 1;
            }
            if (y_draw < 0 || y_draw > HEIGHT) {
                end_of_screen = 1;
            }
            double distance_squared =
                pow(x_draw - object.x, 2) + pow(y_draw - object.y, 2);
            if (distance_squared < radius_squared)
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Get native display resolution
    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
        printf("Failed to get display mode: %s\n", SDL_GetError());
        return -1;
    }

    // Set global variables to native resolution
    WIDTH = displayMode.w;
    HEIGHT = displayMode.h;

    printf("Native resolution: %d x %d\n", WIDTH, HEIGHT);

    // Create the window with fullscreen flag
    SDL_Window *window = SDL_CreateWindow(
        "Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
        HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    // Define a custom close button in the top-right corner
    struct Button closeButton = {WIDTH - 60, 10, 50, 50};

    // Adjust initial positions to be proportional to screen size
    struct Circle circle = {WIDTH / 7, HEIGHT / 3, 40};
    struct Circle shadow_circle = {WIDTH / 3, HEIGHT / 2, 100};

    SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};

    SDL_UpdateWindowSurface(window);

    struct Ray rays[RAYS_NUMBER];
    generate_rays(circle, rays);

    double obstacle_speed_y = 1;
    double obstacle_speed_x = 2;

    int simulation_running = 1;
    SDL_Event event;
    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                simulation_running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    simulation_running = 0;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Check if the close button was clicked
                if (IsPointInButton(event.button.x, event.button.y,
                                    closeButton)) {
                    simulation_running = 0;
                }
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                generate_rays(circle, rays);
            }
        }
        SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
        FillCircle(surface, circle, COLOR_RAY);
        FillCircle(surface, shadow_circle, COLOR_WHITE);
        FillRays(surface, rays, COLOR_RAY, shadow_circle);

        // Draw our custom close button
        DrawCloseButton(surface, closeButton, COLOR_RED);

        shadow_circle.x += obstacle_speed_x;
        if (shadow_circle.x - shadow_circle.radius < 0 ||
            shadow_circle.x + shadow_circle.radius > WIDTH)
            obstacle_speed_x = -obstacle_speed_x;

        shadow_circle.y += obstacle_speed_y;
        if (shadow_circle.y - shadow_circle.radius < 0 ||
            shadow_circle.y + shadow_circle.radius > HEIGHT)
            obstacle_speed_y = -obstacle_speed_y;

        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
