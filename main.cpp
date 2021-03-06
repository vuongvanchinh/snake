#include"COMMONFUNC.h"
#include"DOT.h"
#include"TEXT.h"

Mix_Chunk* eat = NULL;
Mix_Chunk* die = NULL;

SDL_Window* g_window = NULL;
SDL_Renderer* g_render = NULL;
SDL_Texture* g_texture = NULL;
TTF_Font* g_font = NULL;

vector<DOT*> SNAKE;
Text g_text;
DOT background ;
vector<DOT*> moi;

SDL_Rect sprite[9];

void khoi_tao_snake();

void khoi_tao_moi();

void khoi_tao_am_thanh(bool& succes);

void play();
 
bool init();

bool loadmedia();
// hàm giải phóng mọi thứ và quit SDL
void close();
/// hàm reset khi vào game cho về trạng thái s0
void reset();
// show ra màn hình menu 
void show_menu();
void show_moi();
void show_snake();
void show_score(int score);

void khoi_tao_sprite(bool& success);
void khoi_tao_font(bool& success);
void XU_LY_SU_KIEN(SDL_Event &e);

void XU_LY_DI_CHUYEN();

void XU_LY_ENDGAME(bool &quit);
bool isVaCham(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void XU_LY_AN();

int main(int agrv, char* agrs[])
{
	if (init() == true)
	{
		if (loadmedia() == true)
		{

			show_menu();
			
		}
		else
		{
			cout << "failed loadmedia";
		}
	}
	else {
		cout << "failed init";
	}
	close();
	return 0;
}
bool init()
{
	bool thanhcong = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Khoi tao that bai:" << SDL_GetError();
		thanhcong = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "Warning: Linear texture filtering not enabled!";
		}
		g_window = SDL_CreateWindow("SNAKE GAME", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == NULL) {
			cout << "Khoi tao cua so that bai:" << SDL_GetError();
			thanhcong = false;
		}
		else {
			g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if (g_render == NULL) {
				cout << "Khoi tao render that bai" << SDL_GetError();
				thanhcong = false;
			}
			else {

				SDL_SetRenderDrawColor(g_render, 0xff, 0xff, 0xff, 0xff);
				int IMGflag = IMG_INIT_PNG;
				if (!(IMG_Init(IMGflag) & IMGflag))
				{
					cout << "SDL_image khoi tao that bai" << SDL_GetError();
					thanhcong = false;
				}

				//khoi tao  SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError();
					thanhcong = false;
				}
				//khoi tao SDL_ttf
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError();
					thanhcong = false;
				}
			}
		}
	}
	return thanhcong;
}
bool loadmedia()
{
	bool success = true;
	if (background.loadimage("image/background_snake.png", g_render) == false)
	{
		success = false;
	}
	
	khoi_tao_sprite(success);
	khoi_tao_am_thanh(success);
	khoi_tao_font(success);

	return success;
}
void close()
{
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	SDL_DestroyRenderer(g_render);
	g_render = NULL;
	background.free();
	for (int i = 0; i < SNAKE.size(); i++)
	{
		SNAKE[i]->free();
	}
	for (int i = 0; i < moi.size(); i++)
	{
		moi[i]->free();
	}
}



void khoi_tao_sprite(bool& success)
{
	DOT TEST;
	if (TEST.loadimage("image/snake.png", g_render) == false)
	{
		success = false;
	}
	else
	{
		sprite[0].x =0 ;
		sprite[0].y = 0;
		sprite[0].w = 23;
		sprite[0].h =24;

		sprite[1].x = 23;
		sprite[1].y = 0;
		sprite[1].w = 23;
		sprite[1].h = 24;


		sprite[2].x = 46;
		sprite[2].y = 0;
		sprite[2].w =23;
		sprite[2].h = 24;
		
		sprite[3].x = 70;
		sprite[3].y = 0;
		sprite[3].w = 23;
		sprite[3].h = 24;

		sprite[4].x = 165;
		sprite[4].y = 0;
		sprite[4].w = 23;
		sprite[4].h = 34;
	}

}
void khoi_tao_am_thanh(bool& success)
{
	eat = Mix_LoadWAV("audio/am1.wav");
	if (eat == NULL)
	{
		success = false;
		cout << "failed to load audio";
	}
	die= Mix_LoadWAV("audio/am2.wav");
	eat = Mix_LoadWAV("audio/am1.wav");
	if (die == NULL)
	{
		success = false;
		cout << "failed to load audio";
	}
}
void khoi_tao_snake()
{
	DOT* HEAD=new DOT();

	HEAD ->loadimage("image/snake.png", g_render);
	
	HEAD->x = FIRST_POSSITION_X;
	HEAD->y = FIRST_POSSITION_Y;
	SNAKE.push_back(HEAD);
	
	DOT* TAIL = new DOT();

	TAIL->loadimage("image/snake.png", g_render);
	
	TAIL->x = FIRST_POSSITION_X-15;
	TAIL->y = FIRST_POSSITION_Y;
	SNAKE.push_back(TAIL);

}
void khoi_tao_moi()
{
	if (moi.size() < SOMOIMAX)
	{
		DOT* MOI_ = new DOT();
		MOI_->loadimage("image/moi.png", g_render);
		srand(time(NULL));
		MOI_->x = rand() % (SCREEN_WIDTH-24) + 0;
		MOI_->y = rand() % (SCREEN_HEIGHT-24) + 0;
		moi.push_back(MOI_);
	}
}
void khoi_tao_font(bool& success)
{
	g_font = TTF_OpenFont("font/font_chu.ttf", 15);

	if (g_font == NULL)
	{
		cout << "Failed to load lazy font! SDL_ttf Error: %s\n" << TTF_GetError();
		success= false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 255,0 };
		g_text.textColor =textColor ;
		if (!g_text.loadFromRenderedText(g_render, g_font))
		{
			cout << "Failed to render text texture!\n";
			success= false;
		}
	}
}

void show_moi()
{
	for (int i = 0; i < moi.size(); i++)
	{
		moi[i]->render(NULL, g_render);
	}
}
/// show rắn 
void show_snake()
{
	// show head
	
	SNAKE[0]->render(&sprite[SNAKE[0]->sprite], g_render);

	for (int i = 1; i <= SNAKE.size()-1; i++)
	{
		SNAKE[i]->render(&sprite[3], g_render);
		
	}	
}
/// show điểm ra màn hình 
void show_score(int score)
{
	SDL_Color textColor = { 255, 255,0 };
	g_text.textColor=textColor;
	string score_str = "Score : " + to_string(score);
	g_text.textureText=score_str;
	g_text.loadFromRenderedText(g_render, g_font);

	g_text.render(SCREEN_WIDTH-100, 10, NULL, g_render);
}
void XU_LY_DI_CHUYEN()
{
	// chỉ cần điều khiển đầu rắn các đốt sẽ theo sau bằng cách cho đốt sau bằng dốt trước của nó <!quan trọng> 
	for (int i = SNAKE.size() - 1; i > 0; i--)
	{
		
		SNAKE[i]->x =SNAKE[i-1]->x;
		
		SNAKE[i]->y = SNAKE[i - 1]->y;
		
		SNAKE[i]->trangthai = SNAKE[i - 1]->trangthai;
	}
	/// chỉ cần diieuf kiển đốt đầu tiên 
		switch (SNAKE[0]->trangthai)
		{
		case left: SNAKE[0]->x -= VANTOC;
			break;
		case right: SNAKE[0]->x += VANTOC;
			break;
		case up:  SNAKE[0]->y -= VANTOC;
			break;
		case down: SNAKE[0]->y += VANTOC;
			break;
			
		}
		//SDL_Delay(10);
		// xu ly cham bien
		if (SNAKE[0]->x > SCREEN_WIDTH-20)
		{
			SNAKE[0]->x = 0;
			
		}
		else
		{
			if (SNAKE[0]->x < 0)
			{
				SNAKE[0]->x = SCREEN_WIDTH-24;
				
			}
			else {
				if (SNAKE[0]->y < 0)
				{
					SNAKE[0]->y = SCREEN_HEIGHT-23;
					
				}
				else {
					if (SNAKE[0]->y > SCREEN_HEIGHT-20) SNAKE[0]->y = 0;
				}
			}
		}
	
}
void XU_LY_SU_KIEN(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (SNAKE[0]->trangthai != down )
			{
				SNAKE[0]->trangthai = up;
				SNAKE[0]->sprite = 1;// sset khung hình của nó 
			}
			break;

		case SDLK_DOWN:
			if (SNAKE[0]->trangthai != up )
			{
				SNAKE[0]->trangthai = down;
				SNAKE[0]->sprite = 1;
			}
			break;

		case SDLK_LEFT:
			if (SNAKE[0]->trangthai != right)
			{
				SNAKE[0]->trangthai = left;
				SNAKE[0]->sprite = 0;
			}
			break;

		case SDLK_RIGHT:
			if (SNAKE[0]->trangthai != left )
			{
				SNAKE[0]->trangthai = right;
				SNAKE[0]->sprite = 2;
			}
			break;

		default:
			break;
		}
	}
}
void XU_LY_AN()
{
	int i = 0;
	while (moi.size()>0)
	{
		if (isVaCham(SNAKE[0]->x, SNAKE[0]->y, 23, 24, moi[i]->x, moi[i]->y, 20, 20) == true)
			// nếu va chạm thì có nghĩa là ăn 
		{
			Mix_PlayChannel(-1, eat, 0);

			moi.erase(moi.begin() + i);// ăn thì mình sẽ xóa nó đi // nếu xóa rồi thì i không cần ++

			// và thêm đốt mớt cho rắn

			DOT* NEWDOT = new DOT();
			NEWDOT->loadimage("image/snake.png", g_render);
			switch (SNAKE[SNAKE.size() - 1]->trangthai)
			{
			case up:
				NEWDOT->x = SNAKE[SNAKE.size() - 1]->x;
				NEWDOT->y = SNAKE[SNAKE.size() - 1]->y +18;
				break;
			case down:
				NEWDOT->x = SNAKE[SNAKE.size() - 1]->x;
				NEWDOT->y = SNAKE[SNAKE.size() - 1]->y - 18;
				break;
			case left:
				NEWDOT->x = SNAKE[SNAKE.size() - 1]->x + 18;
				NEWDOT->y = SNAKE[SNAKE.size() - 1]->y ;
				break;
			case right:
				NEWDOT->x = SNAKE[SNAKE.size() - 1]->x-18;
				NEWDOT->y = SNAKE[SNAKE.size() - 1]->y;
				break;
			}
			SNAKE.push_back(NEWDOT);
		}else
		{
			i++;
		}
	}
	
}
void XU_LY_ENDGAME(bool &quit)
{
	bool endgame = false;
	// xem nó có tự cắn mình không nếu có thì break và game over 
	for (int i = 1; i < SNAKE.size(); i++)
	{
		if (isVaCham(SNAKE[0]->x, SNAKE[0]->y, 10, 10, SNAKE[i]->x, SNAKE[i]->y, 20, 20) == true)
		{
			endgame = true;
			break;
		}
	}
	if (endgame == true)
	{
		quit = true;
		
		//SNAKE[0] ->render(&sprite[SNAKE[0]->sprite], g_render);
		// am thanh 
		Mix_PlayChannel(-1, die, 0);
		//SDL_Delay(2000);
	}
}
bool isVaCham(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	// toa do 
	bool X = ((x1 + w1 >= x2 && x1 < x2 + w2));
	bool Y = ((y1 + h1 > y2&& y1< y2 + h2));

	return X && Y;
}
void play()
{
	reset();

	bool quit = false;
	SDL_Event e;


	while (quit == false)
	{
		// XU LY EVENT
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) { quit = true; }
			else
			{
				XU_LY_SU_KIEN(e);
			}

		}

		SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(g_render);

		khoi_tao_moi();
		background.render(NULL, g_render);
		
		show_snake();
		
		show_moi();

		show_score(SNAKE.size());
		
		XU_LY_DI_CHUYEN();
		XU_LY_AN();
		XU_LY_ENDGAME(quit);

		SDL_RenderPresent(g_render);

		SDL_Delay(delay);

		/// cho nhìn lại màn hình một tý 
		if (quit == true)
		{
			SDL_Delay(2000);
		}
		
	}
}

void show_menu()
{
	bool quit = false;
	SDL_Event e;
	// hai dòng chữ 
	Text playnow;
	Text exit;
	// hai màu để tiện thay đổi khi rê chuột qua 
	SDL_Color color = { 0,0,0 }, color2 = { 255, 0, 255 };

	DOT background0;
	// set up các dòng chữ 
	background0.loadimage("image/background0.png", g_render);
	playnow.textureText = "Play Now";
	playnow.textColor = color;
	playnow.loadFromRenderedText(g_render, g_font);

	exit.textureText = "Exit";
	exit.textColor = color;
	exit.loadFromRenderedText(g_render, g_font);
	SDL_Event e_event;
	int toadox, toadoy;
	while (quit == false)
	{
		// XU LY EVENT
		while (SDL_PollEvent(&e_event) != 0)
		{
			if (e_event.type == SDL_QUIT)
			{
				quit = true;
			}
			else
			if (e_event.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&toadox, &toadoy);
					
					if (isVaCham(toadox, toadoy, 1, 1,200, 226,playnow.mwidth,playnow.mheight) == true)
					{
						playnow.textColor = color2;
					}
					else
					{
						playnow.textColor=color;
					}
					if (isVaCham(toadox, toadoy, 1, 1, 220, 240, exit.mwidth, exit.mheight) == true)
					{
						exit.textColor = color2;
					}
					else
					{
						exit.textColor = color;
					}
				
			}
			else
			{
				if (e_event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (e_event.button.button == SDL_BUTTON_LEFT)
					{
						SDL_GetMouseState(&toadox, &toadoy);
						bool is_click[2] = { false,false };

						if (isVaCham(toadox, toadoy, 1, 1, 200, 226, playnow.mwidth, playnow.mheight) == true)
						{
							play();
						}
						else
						{
							if (isVaCham(toadox, toadoy, 1, 1, 220, 240, exit.mwidth, exit.mheight) == true)
							{
								quit = true;
							}
						}

					}
				}
			}
		}
		SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(g_render);
		background0.render(NULL, g_render);

		playnow.loadFromRenderedText(g_render, g_font);
		playnow.render(200,226, NULL, g_render);

		exit.loadFromRenderedText(g_render, g_font);
		exit.render(220,240 , NULL, g_render);

		SDL_RenderPresent(g_render);
	}
}
void reset()
{
	// xóa hết các dốt của nó 
	while (SNAKE.size() > 0)
	{
		DOT* l_dot = SNAKE[0];
		SNAKE.erase(SNAKE.begin() + 0);
		l_dot->free();
		delete l_dot;
	}
	// xóa hết các mồi 
	while (moi.size() > 0)
	{
		DOT* l_moi = moi[0];

		moi.erase(moi.begin() + 0);
		l_moi->free();
		delete l_moi;
	}
	// khởi tạo lại 
	khoi_tao_snake();
	

}
