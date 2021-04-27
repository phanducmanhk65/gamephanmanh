#include "baseobject.h"
#include "function.h"

BaseObject::BaseObject()
{
	//Khởi tạo
	p_object_=NULL;
	rect_.x=0;
	rect_.y=0;
	rect_.w=0;
	rect_.h=0;

}

BaseObject::~BaseObject()
{

	Free();
}

bool BaseObject::LoadImg( std::string path,SDL_Renderer* screen )//Hàm load ảnh
{
	//Giải phóng các vùng nhớ rác
	Free();


	SDL_Texture* newTexture = NULL;

	//Load ảnh nền
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );


        newTexture = SDL_CreateTextureFromSurface( screen, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{

		rect_.w = loadedSurface->w;
			rect_.h = loadedSurface->h;
		}

		//Giải phóng surface
		SDL_FreeSurface( loadedSurface );
	}

	//Trả về success
	p_object_ = newTexture;
	return p_object_ != NULL;
}

void BaseObject::Free()
{

	if( p_object_ != NULL )
	{
		SDL_DestroyTexture(p_object_ );
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}




void  BaseObject::Render( SDL_Renderer* des,const SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { rect_.x,rect_.y, rect_.w, rect_.h };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( des,p_object_, clip, &renderQuad );
}
