#ifndef COMMON_FUNCTION_H_

#define COMMON_FUNCTION_H_
#include <windows.h>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

const int FRAME_PER_SECOND=35;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
//static SDL_Window* gWindow = NULL;
const int COLOR_KEY_R =167;
const int COLOR_KEY_G =175;
const int COLOR_KEY_B =180;

const int RENDER_DRAW_COLOR= 0xFF;

static SDL_Window* gWindow = NULL;

//The window renderer
static SDL_Renderer* gscreen = NULL;
static SDL_Event e;
static SDL_Renderer* menu = NULL;

//const int WALKING_ANIMATION_FRAMES = 4;
static Mix_Chunk* g_sound[1];
static Mix_Chunk* menu_sound[1];

#define BLANK_TILE 0
#define TITLE_SIZE 64
#define MAX_MAP_X  400
#define MAX_MAP_Y 10
#define STATE_MONEY 4
typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};
typedef struct Map
{
  int start_x_;
  int start_y_;

  int max_x_;
  int max_y_;

  int title[MAX_MAP_Y][MAX_MAP_X];
  char* file_name_;
};
namespace Func
{
   bool checkCollision(const SDL_Rect & object1, const SDL_Rect & object2);
   void ApplySurface(SDL_Surface *screen, SDL_Surface *des, int x, int y);
 int MenuGame (SDL_Renderer* g_screen, TTF_Font* font,
                            const std::string& menu1,
                            const std::string& menu2,
                            const std::string& img_name);
//SDL_Surface* Loadanh(std::string path);
}

#endif
