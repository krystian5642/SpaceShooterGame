#include "GameBar.h"

GameBar::GameBar(sf::Vector2f size, sf::Vector2f position, sf::Color barColor,
	std::string barText, sf::Color barTextColor) : sf::RectangleShape(size)
{
	setStartXSize(size.x);
	setPosition(position);
	setCharacterSize(size.y / 1.3);
	sf::RectangleShape::setFillColor(barColor);
	sf::Text::setFillColor(barTextColor);
	setString(barText);
	setRelativePosition(position);
}

GameBar::~GameBar()
{
}

const sf::Vector2f& GameBar::getRelativePosition() const
{
	return relativePosition;
}

void GameBar::setRelativePosition(const sf::Vector2f& newRelativePosition)
{
	relativePosition = newRelativePosition;
}

float GameBar::getStartXSize() const
{
	return startXSize;
}

void GameBar::setStartXSize(float newStartXSize)
{
	if (newStartXSize <= 0)
	{
		throw std::logic_error("startXSize cannot be less or equal zero");
	}
	startXSize = newStartXSize;
}

void GameBar::setPosition(const sf::Vector2f& position)
{
	sf::RectangleShape::setPosition(position);
	sf::Text::setPosition(position);
}

void GameBar::updateBar(int currentState, int maxState, const sf::RenderWindow* window, const sf::View& currentView)
{
	std::string previousState = getString();
	if (currentState != std::stod(previousState))
	{
		setString(std::to_string(currentState));
	}
	setPosition(window->mapPixelToCoords(sf::Vector2i(relativePosition.x, relativePosition.y), currentView));
	double ratio = (float)currentState / maxState;
	if (startXSize * ratio != getSize().x)
	{
		setSize(sf::Vector2f(startXSize * ratio, getSize().y));
	}
}

void GameBar::drawBar(sf::RenderWindow* window)
{
	window->draw((sf::RectangleShape)*this);
	window->draw((sf::Text)*this);
}
