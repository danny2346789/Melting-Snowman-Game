#include "entity.hpp"

void Entity::SetTexture(SDL_Texture* texture)
{
	_texture = texture;

	if (_texture == nullptr)
		std::cerr << "SetTexture: Error loading texture!" << SDL_GetError() << "\n";
}

void Entity::SetPosition(int new_x, int new_y)
{
	_position.x = new_x;
	_position.y = new_y;
}

void Entity::SetSize(int new_w, int new_h)
{
	_size.w = new_w;
	_size.h = new_h;
}

void Entity::SetSourceRectangle(int x, int y, int w, int h)
{
	_sourceRectangle = { x,y,w,h };
}

void Entity::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rectangle = {_position.x, _position.y, _size.w, _size.h};

	if (_sourceRectangle.x == -1) // copies the entire texture
	{
		if (SDL_RenderCopy(renderer, _texture, NULL, &rectangle) != 0)
		{
			std::cout << "SDL_RenderCopy: " << SDL_GetError() << "\n";
		}	
	}
	else
	{
		if (SDL_RenderCopy(renderer, _texture, &_sourceRectangle, &rectangle) != 0)
		{
			std::cout << "SDL_RenderCopy: " << SDL_GetError() << "\n";
		}
	}
	
}

Entity::Entity(SDL_Texture* texture, string name, int w, int h, int x, int y) 
{
	SetTexture(texture); 
	_name = name;
	_size.w = w; _size.h = h; _position.y = y; _position.x = x;


}