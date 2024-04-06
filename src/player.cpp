#include "player.hpp"

bool Player::UpdateGuessedLetters(const char* scanned, vector<Text>& texts)
{
	bool guessed = false;

	for (string letter : _guessedLetters)
	{
		if (scanned == letter)
			guessed = true;
	}

	if (_guessedLetters.size() == 0 || guessed == false)
	{
		if (_guessesLeft > 0)
		{
			SDL_Color black = { 0,0,0 };
			_guessedLetters.push_back(scanned);

			string name = "guessed_" + _guessedLetters.back();
			texts.emplace_back(name, black);
			texts.back().SetFont(48);
			texts.back().SetTexture(_renderer, _guessedLetters.back().c_str());
			texts.back().SetPosition(currentXPos, currentYPos);

			if (currentXPos < 800 + (64 * 12))
			{
				currentXPos += 64;
			}
			else
			{
				currentXPos = 800; 
				currentYPos += 100;
			}		
		}
	}
		
	return guessed;
}

bool Player::CheckWordGuessed(vector<Text>& texts)
{
	for (Text& text : texts)
	{
		if (text.GetVisbility() == false)
			return false;
	}
	return true;
}

void Player::UpdateTexts(const char* scanned, vector<Text>& texts)
{
	for (Text& text : texts)
	{
		if (text.GetName().back() == *scanned)
			text.SetVisiblity(true);

		if (text.GetName() == "guesses_left_text")
		{
			if (_guessesLeft <= 3)
			{
				SDL_Color red = { 255,0,0 };
				text.SetColor(red);
			}

			string message = "Guesses left: " + std::to_string(_guessesLeft);
			text.SetTexture(_renderer, message.c_str());
		}
	}
}

bool Player::Input(SDL_Keysym key, vector<Text>& texts)
{
	if (_renderer != NULL)
	{
		if (4 <= key.scancode && key.scancode <= 29)
		{
			const char* scannedLetter = SDL_GetScancodeName(key.scancode);
			bool letterGuessed = UpdateGuessedLetters(scannedLetter, texts);

			if (letterGuessed == false)
			{
				if (_guessesLeft > 0)
				{
					_guessesLeft--;	

					UpdateTexts(scannedLetter, texts);
					if (CheckWordGuessed(texts) == true)
						return true;
				}
			}

		}
	}


	return false;
}