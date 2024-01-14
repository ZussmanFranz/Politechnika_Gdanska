#include "TextureManager.hpp"

char text[128];

//SDL_Surface *screen = SDL_CreateRGBSurface(0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
//SDL_Surface *charset = SDL_LoadBMP("assets/cs8x8.bmp");
SDL_Texture* charset;

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
    SDL_Surface* tempSurface = SDL_LoadBMP(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

void TextureManager::InitWriting(const char* chset)
{
    charset = TextureManager::LoadTexture(chset);
    if (charset == NULL)
    {
        printf("There is a problem with a charset\n");
    }
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, int frame)
{
    src.x = src.w * (frame - 1);
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

void TextureManager::DrawBackground()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

    SDL_Rect rect;
    rect.x = 0; 
    rect.y = 0; 
    rect.w = Game::SCREEN_WIDTH; 
    rect.h = Game::SCREEN_HEIGHT; 

    SDL_RenderFillRect(Game::renderer, &rect);
}

void TextureManager::DrawString( int x, int y, const char *text, SDL_Texture *charset, float scale) {
    // if (screen == NULL)
    // {
    //     printf("There is a problem with a screen\n");
    // }
    
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = s.w * scale;
	d.h = s.w * scale;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
        SDL_RenderCopy(Game::renderer, charset, &s, &d);
		//SDL_BlitSurface(charset, &s, screen, &d);
		x += s.w * scale;
		text++;
		};
	};

void TextureManager::DrawInfo(Uint32 WorldTime)
{
    //sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s", WorldTime);
    sprintf(text, "Game time = %d s", (WorldTime / 1000));
    //printf("%s\n", text);
	DrawString(5, 5, text, charset, 2);
	sprintf(text, "Esc - exit  n - new game");
    //printf("%s\n", text);
	DrawString(300, 5, text, charset, 2);
}

void TextureManager::DrawOutro(Uint32 FinishTime)
{
    SDL_RenderClear(Game::renderer);

    int y_first = Game::SCREEN_HEIGHT / 2 - 200;

    sprintf(text, "Congratulations, you made it in ");
    DrawString(Game::SCREEN_WIDTH / 2 - (strlen(text) * 8 * 2) / 2, y_first, text, charset, 2);

    sprintf(text, "%d seconds!", FinishTime);
	DrawString(Game::SCREEN_WIDTH / 2 - (strlen(text) * 8 * 3) / 2, y_first + 200, text, charset, 3);

    sprintf(text, "Press ESC to exit the game", FinishTime);
	DrawString(Game::SCREEN_WIDTH / 2 - (strlen(text) * 8 * 2) / 2, y_first + 400, text, charset, 2);

    SDL_RenderPresent(Game::renderer);
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}