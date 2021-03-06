#include"DOT.h"

DOT::DOT()
{
	x = 0;
	y = 0;
	mtexture = NULL;
	mwidth = 0;
	mheight = 0;
	trangthai = right;
	sprite = 2;
}
// hàm load ảnh 
bool DOT::loadimage(std::string path, SDL_Renderer* & g_render)
{
	SDL_Texture* newtexture = NULL;
	SDL_Surface* loadedimage = IMG_Load(path.c_str());
	if (loadedimage == NULL)
	{
		cout << "loadedimage= NULL" << IMG_GetError() << "\n";
	}
	else
	{

		SDL_SetColorKey(loadedimage, SDL_TRUE, SDL_MapRGB(loadedimage->format, 255, 255, 255));


		newtexture = SDL_CreateTextureFromSurface(g_render, loadedimage);
		if (newtexture == NULL)
		{
			cout << "newtexture= NULL" << SDL_GetError() << "\n";
		}
		else
		{
			mwidth = loadedimage->w;
			mheight = loadedimage->h;
		}
		SDL_FreeSurface(loadedimage);
	}
	mtexture = newtexture;
	return mtexture != NULL;
}
//hàm kết xuất ra màn hình 
void DOT:: render(SDL_Rect* clip, SDL_Renderer*& g_render)
{
	SDL_Rect pos = { x,y,mwidth, mheight };// vi tri va kick thuoc in ra
	//ham inra
	if (clip != NULL)
	{
		pos.w = clip->w;
		pos.h = clip->h;
	}
	SDL_RenderCopy(g_render, mtexture, clip, &pos);
}
// hàm giải phóng 
void DOT::free()
{
	if (mtexture != NULL)
	{
		SDL_DestroyTexture(mtexture);
		mtexture = NULL;
		x = 0;
		y = 0;
	}
}
