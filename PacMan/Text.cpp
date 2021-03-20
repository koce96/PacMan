#include "Text.h"
#include <iostream>

using namespace std;


Text::Text(const string &font_path,int font_size,const string &message_text,const SDL_Color &color)
{
	_text_texture = loadFont(font_path, font_size, message_text, color);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

void Text::display(int x, int y) const
{
	_text_rect.x = x;
	_text_rect.y = y;
	SDL_RenderCopy(Game::renderer, _text_texture, nullptr, &_text_rect);
}

SDL_Texture *Text::loadFont(const string &font_path, int font_size, const string &message_text, const SDL_Color &color) {
	TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
	if (!font) {
		cout << "failed to load font" << endl;
	}
	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
	if (!text_surface) {
		cout << "failed to load surface" << endl;
	}
	auto text_texture = SDL_CreateTextureFromSurface(Game::renderer, text_surface);
	if (!text_texture) {
		cout << "failed to load texture" << endl;
	}
	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
	return text_texture;
}
