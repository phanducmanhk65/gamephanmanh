#include "text.h"
#include "function.h"
#include <iostream>

using namespace std;
TextObject::TextObject()
{

    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
    texture_= NULL;
}

TextObject::~TextObject()
{

}

bool TextObject::LoadFromRenderText(TTF_Font* font,SDL_Renderer* screen)
   {
       //Free();

   // SDL_Surface* text_sf=TTF_RenderText_Solid(font,"Phan Dưc Manh",text_color_);
    SDL_Surface* text_sf=NULL;
    text_sf = TTF_RenderText_Solid(font,str_val_.c_str(),text_color_);

  //  printf(" %d",text_sf==NULL);
   // printf("%d",font);
    //printf("%d",screen);
    if(!text_sf)
        printf("kh");
    if(text_sf)
    {
        texture_=SDL_CreateTextureFromSurface(screen,text_sf);
        if(texture_==NULL)
            printf("NO kd");
        else
        {
            width_=text_sf->w;
        height_=text_sf->h;
        }

        SDL_FreeSurface(text_sf);
    }



    return texture_!=NULL;
}

void TextObject::Free()

{

    if(texture_!=NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_=NULL;
    }
}
void TextObject::Setcolor(Uint8 red, Uint8 green,Uint8 blue)
{
    text_color_.r=red;
    text_color_.g=green;
    text_color_.b=blue;
}


void TextObject::Setcolorr(const int &type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0};
        text_color_ = color;
    }
    else if (type == WHITE_TEXT)
    {
   SDL_Color color = {255, 255, 255};
        text_color_ = color;
    }
    else if(type== BLACK_TEXT)
    {
        SDL_Color color = {0,0,0};
        text_color_=color;
    }
}
void TextObject::RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip, double angle,
                SDL_Point* center,SDL_RendererFlip flip )
                {
                    SDL_Rect renderQuad = {xp,yp,width_,height_};
                    if(clip!=NULL)
                    {
                        renderQuad.w=clip->w;
                        renderQuad.h=clip->h;
                    }
                    SDL_RenderCopyEx(screen,texture_,clip,&renderQuad,angle,center,flip);
                }


