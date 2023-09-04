#include "display.h"

// ===================================================================
// Variable Initializations
// ===================================================================
unsigned int window_width = 800;
unsigned int window_height = 600;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Texture *color_buffer_texture = NULL;
uint32_t *color_buffer = NULL;

// ===================================================================
// RENDERER FUNCTIONS
// ===================================================================
bool initialize_window(void)
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    // Query screen size via SDL
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    window_width = display_mode.w;
    window_height = display_mode.h;

    // Create SDL window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        fprintf(stderr, "There was an error creating SDL window.\n");
        return false;
    }

    // Create a SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }

    // set SDL to full screen
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void render_color_buffer(void)
{
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(sizeof(uint32_t) * window_width));

    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color)
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void destroy_window(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// ===================================================================
// DRAWING FUNCTIONS
// ===================================================================
void draw_pixel(uint x_pos, uint y_pos, uint32_t color)
{
    if (x_pos >= 0 && x_pos < window_width && y_pos >= 0 && y_pos < window_height)
    {
        color_buffer[(window_width * y_pos) + x_pos] = color;
    }
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color)
{
    int delta_x = (x1 - x0);
    int delta_y = (y1 - y0);

    // obtain the longest side length
    int side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

    // Find how much we should increment in both x and y
    float x_inc = delta_x / (float)side_length;
    float y_inc = delta_y / (float)side_length;

    float current_x = x0;
    float current_y = y0;

    // loop each step and draw the pixel
    for (int i = 0; i < side_length; i++)
    {
        draw_pixel(round(current_x), round(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}

void draw_rect(uint x_pos, uint y_pos, uint width, uint height, uint32_t color)
{
    for (uint x = x_pos; x < x_pos + width && x < window_width; x++)
    {
        for (uint y = y_pos; y < y_pos + height && y < window_height; y++)
        {
            draw_pixel(x, y, color);
        }
    }
}

void draw_grid(uint32_t color)
{
    for (int x = 5; x < window_width; x += 10)
    {
        for (int y = 5; y < window_height; y += 10)
        {
            color_buffer[(y * window_width) + x] = color;
        }
    }
}
