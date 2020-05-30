#ifndef TEXT_H
#define TEXT_H
#include"COMMONFUNC.h"
struct Text
{
	Text();
	
	bool loadFromRenderedText(SDL_Renderer*& g_render, TTF_Font*& g_font);
	
	//giai phong
	void free();

	void render(int x, int y, SDL_Rect* clip, SDL_Renderer*& g_render);
	
	SDL_Texture* mtexture;
	string textureText;
	SDL_Color textColor;
	int mwidth;
	int mheight;

};

#endif // !TEXT_H

