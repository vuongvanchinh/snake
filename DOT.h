#ifndef DOT_H
#define DOT_H
#include"COMMONFUNC.h"

struct DOT
{
	int x, y;
	int mwidth, mheight;
	SDL_Texture* mtexture;
	int trangthai;
	int sprite;
	DOT();
	
	bool loadimage(std::string path, SDL_Renderer*& g_render);

	void render(SDL_Rect* clip, SDL_Renderer*& g_render);
	
	void free();
	
};
#endif // !DOT_H

