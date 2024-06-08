#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int screen(int width, int height, int fullscreen, const char *title,
           SDL_Window **window, SDL_Renderer **renderer) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

  *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, width, height, flags);
  if (*window == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  *renderer = SDL_CreateRenderer(
      *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (*renderer == NULL) {
    SDL_DestroyWindow(*window);
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  return 0;
}

int done() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return 1;
    }
  }
  return 0;
}

void verLine(SDL_Renderer *renderer, int x, int y1, int y2, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(renderer, x, y1, x, y2);
}

int main(int argc, char *argv[]) {
  double posX = 22, posY = 12;      // x and y start position
  double dirX = -1, dirY = 0;       // initial direction vector
  double planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane

  double time = 0;    // time of current frame
  double oldTime = 0; // time of previous frame

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  if (screen(screenWidth, screenHeight, 0, "Raycaster", &window, &renderer) !=
      0) {
    return 1;
  }
  while (!done()) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set draw color to black
    SDL_RenderClear(renderer);                      // Clear the screen
    for (int x = 0; x < screenWidth; x++) {
      // calculate ray position and direction
      double cameraX =
          2 * x / (double)screenWidth - 1; // x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
      // which box of the map we're in
      int mapX = (int)posX;
      int mapY = (int)posY;

      // length of ray from current position to next x or y side
      double sideDistX;
      double sideDistY;

      // length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

      double perpWallDist;

      // what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; // was there a wall hit?
      int side;    // was there a NS or a EW wall hit?
      // calculate step and initial sideDist
      if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      // perform DDa
      while (hit == 0) {
        // jump to next map square, either in the x-direction, or in the
        // y-direction
        if (sideDistX < sideDistY) {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        } else {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        // check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0)
          hit = 1;
      }
      // Calculate distance projected on camera direction. This is the shortest
      // distance from the point where the wall is hit to the camera plane.
      // Euclidean to center camera point would give fisheye effect! This can be
      // computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or
      // same formula with Y for size == 1, but can be simplified to the code
      // below thanks to how sideDist and deltaDist are computed: because they
      // were left scaled to |rayDir|. sideDist is the entire length of the ray
      // above after the multiple steps, but we subtract deltaDist once because
      // one step more into the wall was taken above.
      if (argc == 2) {
        if (strcmp(argv[1], "fisheye") == 0) {
          double deltaX =
              ((double)mapX - posX + (double)(1 - stepX) / 2) * (double)rayDirX;
          double deltaY =
              ((double)mapY - posY + (double)(1 - stepY) / 2) * (double)rayDirY;
          perpWallDist = sqrt(deltaX * deltaX + deltaY * deltaY);
        } else {
          if (side == 0) {
            perpWallDist = (sideDistX - deltaDistX);
          } else {
            perpWallDist = (sideDistY - deltaDistY);
          }
        }
      } else {
        if (side == 0) {
          perpWallDist = (sideDistX - deltaDistX);
        } else {
          perpWallDist = (sideDistY - deltaDistY);
        }
      }
      //  calculate height of line to draw on screen
      int lineHeight = (int)(screenHeight / perpWallDist);

      // calculate lowest and hightest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + screenHeight / 2;
      if (drawStart < 0) {
        drawStart = 0;
      }
      int drawEnd = lineHeight / 2 + screenHeight / 2;
      if (drawEnd >= screenHeight) {
        drawEnd = screenHeight - 1;
      }

      SDL_Color color;
      switch (worldMap[mapX][mapY]) {
      case 1:
        color = (SDL_Color){255, 0, 0, 255};
        break; // Red
      case 2:
        color = (SDL_Color){0, 255, 0, 255};
        break; // Green
      case 3:
        color = (SDL_Color){0, 0, 255, 255};
        break; // Blue
      case 4:
        color = (SDL_Color){255, 255, 255, 255};
        break; // White
      default:
        color = (SDL_Color){255, 255, 0, 255};
        break; // Yellow
      }

      // Give x and y sides different brightness
      if (side == 1) {
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
      }

      // Draw the pixels of the stripe as a vertical line
      verLine(renderer, x, drawStart, drawEnd, color);
    }
    // timing for input and FPS counter
    oldTime = time;
    time = SDL_GetTicks();
    double frameTime =
        (time - oldTime) /
        1000.0; // frameTime is the time this frame has taken, in seconds
    char fpsText[64];
    snprintf(fpsText, sizeof(fpsText), "FPS: %.2f", 1.0 / frameTime);
    SDL_SetWindowTitle(window, fpsText);

    SDL_RenderPresent(renderer); // update the screen
    double moveSpeed =
        frameTime * 5.0; // the constant value is in squares/second
    double rotSpeed =
        frameTime * 3.0; // the constant value is in radians/second

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    // move forward if no wall in front of you
    if (state[SDL_SCANCODE_UP]) {
      if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0)
        posX += dirX * moveSpeed;
      if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0)
        posY += dirY * moveSpeed;
    }
    // move backwards if no wall behind you
    if (state[SDL_SCANCODE_DOWN]) {
      if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0)
        posX -= dirX * moveSpeed;
      if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0)
        posY -= dirY * moveSpeed;
    }
    // rotate to the right
    if (state[SDL_SCANCODE_RIGHT]) {
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    // rotate to the left
    if (state[SDL_SCANCODE_LEFT]) {
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
  }
}
