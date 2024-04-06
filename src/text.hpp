#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
using std::string;

class Text
{
public:
	Text(string name, SDL_Color color = { 255,255,255 }) { _name = name; _color = color; };

	void SetFont(int size, const char* filepath="src/images/better_comic_sans.ttf");
	void SetTexture(SDL_Renderer* renderer, const char* message="empty text");
	void SetPosition(int x, int y);
	void SetVisiblity(bool newVisibility) { _visible = newVisibility; };
	void SetName(string newName) { _name = newName; };
	void SetColor(SDL_Color newColor) { _color = newColor; };

	void Draw(SDL_Renderer* renderer);
	const string GetName() { return _name; };
	const bool GetVisbility() { return _visible; };
private:
	string _name;
	TTF_Font* _font = nullptr;
	SDL_Texture* _texture = nullptr;
	SDL_Color _color;
	SDL_Rect _messageRectangle = {NULL,NULL,NULL,NULL};
	bool _visible = true;
};