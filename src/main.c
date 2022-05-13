#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

bool is_game_running = false; 
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int last_frame_time = 0;

struct ball {
  float x;
  float y;
  float width;
  float height;
} ball;

bool initialize_window(void);
void setup(void);
void update(void);
void render(void);
void process_input(void);
void destroy_window(void);

int main()
{

  is_game_running = initialize_window();

  setup();

  while (is_game_running)
  {
    process_input();
    update();
    render();
  }

  return 0;
}

bool initialize_window(void)
{
  
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    fprintf(stderr, "Error initializing SDL\n");
    return false;
  }

  window = SDL_CreateWindow(
      NULL,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      SDL_WINDOW_BORDERLESS
  );

  if (!window)
  {
    fprintf(stderr, "Error creating window\n");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
  {
    fprintf(stderr, "Error creating renderer\n");
    return false;
  }

  return true;

}

void setup(void)
{
  ball.x = 20;
  ball.y = 20;
  ball.width = 15;
  ball.height = 15;
}

void update(void)
{
  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
  
  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
  {
    SDL_Delay(time_to_wait);
  }

  float delta_time =  (SDL_GetTicks() - last_frame_time) / 1000.0f;


  last_frame_time = SDL_GetTicks();

  ball.x += 70 * delta_time;
  ball.y += 50 * delta_time;
}

void render(void)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
 
  SDL_Rect ball_rect = {
    (int) ball.x,
    (int) ball.y,
    (int) ball.width,
    (int) ball.height
  };


  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &ball_rect);

  SDL_RenderPresent(renderer);
}

void process_input(void)
{
  SDL_Event event;
  SDL_PollEvent(&event);

  switch(event.type)
  {
    case SDL_QUIT:
      is_game_running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        is_game_running = false;
      }
      break;
  }
}

void destroy_window(void)
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

