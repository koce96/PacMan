#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Game.h"
#include "Entities.h"

using namespace std;

class Text
{
public:
	Text(const string &font_path, int font_size, const string &message_text,const SDL_Color &color);

	void display(int x,int y) const;

	static SDL_Texture *loadFont(const string &font_path, int font_size, const string &message_text, const SDL_Color &color);
private:
	SDL_Texture  *_text_texture = nullptr;
	mutable SDL_Rect _text_rect;
};

