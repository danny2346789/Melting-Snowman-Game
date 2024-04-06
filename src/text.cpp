#include "text.hpp"

void Text::SetFont(int size,const char* filepath)
{
	_font = TTF_OpenFont(filepath, size);

	if (_font == nullptr)
		std::cerr << "SetFont: Could not set the font! " << TTF_GetError() << "\n";
}

void Text::SetTexture(SDL_Renderer* renderer, const char* message)
{
	if (_font == nullptr)
		std::cerr << "SetTexture: Font is null! " << TTF_GetError() << "\n";
	

	SDL_Surface* textSurface = TTF_RenderUTF8_Blended(_font, message, _color);
	_messageRectangle.w = textSurface->w;
	_messageRectangle.h = textSurface->h;

	_texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (_texture == nullptr)
		std::cerr << "SetTexture: Could not set the texture! " << TTF_GetError() << "\n";
	SDL_FreeSurface(textSurface);
}

void Text::SetPosition(int x, int y)
{
	_messageRectangle.x = x;
	_messageRectangle.y = y;
}

void Text::Draw(SDL_Renderer* renderer)
{
	if (_messageRectangle.x != NULL)
	{
		if (SDL_RenderCopy(renderer, _texture, NULL, &_messageRectangle) != 0)
			std::cerr << "SDL_RenderCopy: Could not draw text!" << SDL_GetError() << "\n";
	}
}