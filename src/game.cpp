#include "game.hpp"
using namespace Game;

void GameClass::InitializeSDL()
{
    if ((SDL_Init(SDL_INIT_EVERYTHING) < 0))
    {
        std::cerr << "SDL_Init: Could not initialize SDL! " << SDL_GetError() << "\n";
        exit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        std::cerr << "IMG_Init: Could not initialize SDL image! " << IMG_GetError() << "\n";
        exit(1);
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init: Could not initialize SDL ttf! " << TTF_GetError() << "\n";
        exit(1);
    }

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    

    if (window == nullptr || renderer == nullptr)
    {
        std::cerr << "Window and/or renderer could not initialize! " << SDL_GetError() << "\n";
        throw std::runtime_error("SDL_CreateWindowAndRenderer");
    }
}


void GameClass::QuitSDL()
{
    for (SDL_Texture* texture : _textures)
        SDL_DestroyTexture(texture);
    SDL_DestroyTexture(windowTexture);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
}


void GameClass::LoadEntities()
{
    SDL_Texture* snowmanTexture = IMG_LoadTexture(renderer, "src/images/snowman.png");
    _entities.emplace_back(snowmanTexture, "snowman");
    _entities.back().SetSize(1280, 720);
    _entities.back().SetPosition(-300, 250);

    SDL_Texture* blankLineTexture = IMG_LoadTexture(renderer, "src/images/blankline.png");

    for (int i=0; i < word.size(); i++)
    {
        string name = "blankline";
        _entities.emplace_back(blankLineTexture, name);
        _entities.back().SetSize(64,64);
        _entities.back().SetPosition(100 + (i * 96), 100);
    }

    _textures.push_back(snowmanTexture); _textures.push_back(blankLineTexture);
}

void GameClass::LoadTexts()
{
    string message = "Guesses left: " + std::to_string(_player.GetGuessesLeft());
    _texts.emplace_back("guesses_left_text", black);
    _texts.back().SetFont(40);
    _texts.back().SetTexture(renderer, message.c_str());
    _texts.back().SetPosition(210, 220);

    _texts.emplace_back("letters_guessed_text", black);
    _texts.back().SetFont(40);
    _texts.back().SetTexture(renderer, "Letters Guessed:");
    _texts.back().SetPosition(1000, 240);

    _texts.emplace_back("bottom_message_text", black);
    _texts.back().SetFont(65);
    _texts.back().SetTexture(renderer, "Guess the word before the snowman melts!");
    _texts.back().SetPosition(350, 940);
  
    for (int i = 0; i < word.size(); i++)
    {
        string name = "letter_" + std::string(1, word[i]);
        _texts.emplace_back(name, black);
        _texts.back().SetFont(64);
        _texts.back().SetTexture(renderer, std::string(1, word[i]).c_str());
        _texts.back().SetPosition(110 + (i * 96), 95);
        _texts.back().SetVisiblity(false);
    }
    
}


void GameClass::HandleInput()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            gameRunning = false;
            break;
        case SDL_KEYUP:
            if (_player.Input(e.key.keysym, _texts))
                gameWin = true;
            break;
        }            
    }
}

void GameClass::Render()
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, windowTexture, NULL, NULL);
    for (Entity& entity : _entities)
    {
        if (entity.GetVisbility() == true)
            entity.Draw(renderer);
    }
        
    for (Text& text : _texts)
    {
        if (text.GetVisbility() == true)
            text.Draw(renderer);
    }
    
    SDL_RenderPresent(renderer);
}

void GameClass::Win()
{
    windowTexture = IMG_LoadTexture(renderer, "src/images/background_win.png");

    for (int i=0; i < _texts.size(); i++)
    {
        if (_texts[i].GetName() == "bottom_message_text")
        {
            _texts.erase(_texts.begin() + i);
        }
    }

    _texts.emplace_back("win_message", green);
    _texts.back().SetFont(120);
    _texts.back().SetTexture(renderer, "You have won the game!");
    _texts.back().SetPosition(550, 680);

}

void GameClass::Lose()
{
    windowTexture = IMG_LoadTexture(renderer, "src/images/background_lose.png");

    for (int i = 0; i < _texts.size(); i++)
    {
        if (_texts[i].GetName() == "bottom_message_text")
            _texts.erase(_texts.begin() + i);
    }

    for (int i = 0; i < _entities.size(); i++)
    {
        if (_entities[i].GetName() == "snowman")
            _entities[i].SetTexture(IMG_LoadTexture(renderer, "src/images/snowman_dead.png"));
        
    }

    _texts.emplace_back("lose_message", red);
    _texts.back().SetFont(120);
    _texts.back().SetTexture(renderer, "You have lost the game!");
    _texts.back().SetPosition(550, 680);
}



void GameClass::GameLoop()
{
    InitializeSDL();
    LoadEntities();
    LoadTexts();

    windowTexture = IMG_LoadTexture(renderer, "src/images/background.png");
    _player.SetRenderer(renderer);

    std::cout << word << "\n";

    while (gameRunning)
    {
        if (!gameWin) { HandleInput(); }
        Render();

        if (gameWin)
            Win();
        else if (_player.GetGuessesLeft() == 0)
            Lose();
    }

    QuitSDL();

}