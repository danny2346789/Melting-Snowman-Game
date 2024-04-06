#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
using std::string;

class Entity 
{
public:
	Entity() {_position.x = NULL;_position.y = NULL;_size.w = NULL;_size.h = NULL;};
	Entity(SDL_Texture* texture, string name) { SetTexture(texture); _name = name;};
	Entity(SDL_Texture* texture, string name, int w, int h, int x, int y);
	~Entity() {};

	void SetTexture(SDL_Texture* texture);
	void SetPosition(int new_x_pos, int new_y_pos);
	void SetSize(int new_w, int new_h);
	void SetSourceRectangle(int x, int y, int w, int h);
	void SetVisiblity(bool visiblity) { _visible = visiblity; };

	SDL_Texture* GetTexture() { return _texture; };
	const string GetName() { return _name; };
	const int GetX() { return _position.x; };
	const int GetY() { return _position.y; };
	const int GetWidth() { return _size.w; };
	const int GetHeight() { return _size.h; };
	const SDL_Rect GetSourceRectangle() { return _sourceRectangle; };
	const bool GetVisbility() { return _visible; };

	virtual void Draw(SDL_Renderer* renderer);
private:
	SDL_Texture* _texture = nullptr;
	string _name;
	struct { int x; int y; } _position;
	struct { int w; int h; } _size;
	SDL_Rect _sourceRectangle = {-1,-1,-1,-1};
	bool _visible = true;
};

