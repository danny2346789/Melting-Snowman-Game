#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "text.hpp"
#include "entity.hpp"
#include "randomword.hpp"
#include "player.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

namespace Game 
{
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;

	static class GameClass
	{
	public:
		void InitializeSDL();
		void QuitSDL();
		void LoadEntities();
		void LoadTexts();
		void GameLoop();
		void HandleInput();
		void Render();
		void Win();
		void Lose();

		SDL_Color black = { 0,0,0 };
		SDL_Color green = { 0,255,0 };
		SDL_Color red = { 255,0,0 };
		SDL_Color white = { 255,255,255 };
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* windowTexture;

		const string word = FindLineInFile(GenerateRandomNumber(0, 100), "src/wordlist.txt");
		Player _player;
		vector<Entity> _entities;
		vector<Text> _texts;
		vector<SDL_Texture*> _textures;
		bool gameRunning = true;
		bool gameWin = false;
		const int FPS_CAP = 60;
		float deltaTime;
	};

};





