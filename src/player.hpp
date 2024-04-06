#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "text.hpp"
#include "entity.hpp"
#include <vector>
#include <iostream>
using std::vector;
using std::string;

class Player
{
public:
	bool UpdateGuessedLetters(const char* scannedKey, vector<Text>& texts);
	bool CheckWordGuessed(vector<Text>& texts);
	const int GetGuessesLeft() { return _guessesLeft; };
	void UpdateTexts(const char* scanned, vector<Text>& texts);

	void SetRenderer(SDL_Renderer* newrenderer) { _renderer = newrenderer; };

	bool Input(SDL_Keysym key, vector<Text>& texts);

private:
	int _guessesLeft = 15;
	int currentXPos = 800;
	int currentYPos = 300;
	SDL_Renderer* _renderer;
	vector<string> _guessedLetters = {};


};