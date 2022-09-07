#ifndef GAME_H
#define GAME_H

#include "Explosion.h"
#include "GameBar.h"

class GameWindow
{
private:
	//init functions
	void initWindow();
	void initSounds();
	void initBackground();
	void initFonts();
	void initPlayer();
	void initEnemies();
	void initView();
	void initBars();
	void initScore();
	void initSummary();
	void initMiniMap();

private:
	//variables
	std::unique_ptr<sf::RenderWindow> window;
	sf::Event e;
	std::unique_ptr<sf::Texture> backgroundTexture;
	sf::RectangleShape background;
	std::unique_ptr<sf::Texture> miniMapTexture;
	sf::RectangleShape miniMapShape;
	std::unique_ptr<Ship> player;
	std::map<std::string, sf::SoundBuffer> soundBuffer;
	std::map<std::string, sf::Sound> sounds;
	std::vector<Enemy> enemyShips;
	std::vector<Bullet> playerBullets;
	std::vector<Bullet> enemyBullets;
	std::vector<Explosion> explosions;
	sf::View mainView;
	sf::View miniMap;
	sf::Clock gameClock;
	long double dt;

	//fonts
	sf::Font arial;
	sf::Font CHILLER;

	//game bars
	std::unique_ptr<GameBar> healthBar;
	std::unique_ptr<GameBar> energyBar;

	//player score
	sf::Text SCORE;
	int currentScore;

	//numberOfEnemyShips
	int numberOfEnemyShips = 0;

	//DEFEAT will be displayed if you lose, otherwise WON will be displayed
	sf::Text endGameText;
	sf::Text endScore;

	//entities on the mini map
	std::unique_ptr<sf::CircleShape> playerCircle;
	std::vector<sf::CircleShape> enemyCircles;

	//private functions
	void update();
	void render();

	//update functions
	void updateDt();
	void updateBullets();
	void updateShips();
	void updateView();
	void updateCombat();
	void updateExplosion();
	void updateScore();
	void updateBars();
	void updateResult();
	void updateMiniMap();

	//draw functions
	void drawBackground();
	void drawBullets();
	void drawShips();
	void drawExplosion();
	void drawScore();
	void drawBars();
	void drawResult();
	void drawOnMiniMap();

public:
	//Constructor and destructor
	GameWindow();
	~GameWindow();

	//public functions
	bool startGame();
};

#endif // !GAME