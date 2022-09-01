#ifndef GAMEBAR_H
#define GAMEBAR_H

#include "Ship.h"
#include "GameBar.h"

class GameBar : public sf::RectangleShape, public sf::Text
{
private:
	sf::Vector2f relativePosition = sf::Vector2f(0, 0);
	float startXSize = 0;

public:
	//constructor and virtual destructor
	GameBar(sf::Vector2f size = sf::Vector2f(300, 80),
		sf::Vector2f position = sf::Vector2f(0, 0),
		sf::Color barColor = sf::Color::Red,
		std::string barText = "100",
		sf::Color barTextColor = sf::Color::White);
	virtual ~GameBar();

	//getters and setters
	const sf::Vector2f& getRelativePosition() const;
	void setRelativePosition(const sf::Vector2f& newRelativePosition);

	const float& getStartXSize() const;
	void setStartXSize(const float& newStartXSize);

	//functions
	void setPosition(const sf::Vector2f& position);
	void updateBar(const int& currentState, const int& maxState, const sf::RenderWindow* window, const sf::View& currentView);
	void drawBar(sf::RenderWindow* window);
};

#endif // !GAMEBAR_H

