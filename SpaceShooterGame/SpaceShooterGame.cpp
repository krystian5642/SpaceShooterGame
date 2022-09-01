#include "Game.h"

int main()
{
	std::unique_ptr<GameWindow> Game;
	Game = std::make_unique<GameWindow>();
	while (Game->startGame())
	{
		Game = std::make_unique<GameWindow>();
	}
	return 0;
}