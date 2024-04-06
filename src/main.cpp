#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "game.hpp"

int main(int argc, char* argv[])
{
	using namespace Game;
	GameClass GameInstance = GameClass();
	GameInstance.GameLoop();

	return 0;
}