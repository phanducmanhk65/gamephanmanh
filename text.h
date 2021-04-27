#ifndef Text_H_
#define Text_H_
#include"function.h"


class TextObject
{
public:
    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };
    TextObject();
    ~TextObject();

bool LoadFromRenderText(TTF_Font* font,SDL_Renderer *screen);
void Free();

void Setcolor(Uint8 red, Uint8 green, Uint8 blue);
void Setcolorr(const int& type);

void RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip = NULL, double angle= 0.0,
                SDL_Point* center= NULL,SDL_RendererFlip flip = SDL_FLIP_NONE);

int getWidth()const {return width_;}
int getHeight()const{return height_;}
void SetText( std::string text){str_val_=text;}
std::string GetText()const{return str_val_;}

private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;

};

#endif // TEXT_OBJEC*/
