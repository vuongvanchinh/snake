#include"TEXT.h"
// hàm kết xuất 
void Text :: render(int x, int y, SDL_Rect* clip, SDL_Renderer* & g_render)
{
	SDL_Rect pos = { x,y, mwidth, mheight };
	if (clip != NULL)
	{
		pos.w = clip->w;
		pos.h = clip->h;
	}
	SDL_RenderCopyEx(g_render, mtexture, clip, &pos, 0.0, NULL, SDL_FLIP_NONE);
}

Text::Text()
{
	mwidth = 0;
	mheight = 0;
	mtexture = NULL;
	textColor = { 0,0,0 };

	textureText = "NULL";
}
// hàm này để set màu  và font chữ 
bool Text::loadFromRenderedText(SDL_Renderer*& g_render, TTF_Font* & g_font)
{

	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mtexture = SDL_CreateTextureFromSurface(g_render, textSurface);
		if (mtexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{

			mwidth = textSurface->w;
			mheight = textSurface->h;
		}


		SDL_FreeSurface(textSurface);
	}


	return mtexture != NULL;
}

//giai phong
void Text:: free()
{
	if (mtexture != NULL)
	{
		SDL_DestroyTexture(mtexture);
		mtexture = NULL;
	}
}
