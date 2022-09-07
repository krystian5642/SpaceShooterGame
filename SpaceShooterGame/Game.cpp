#include "Game.h"

float xBackgroundSize;
float yBackgroundSize;

void GameWindow::initWindow()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    srand(time(NULL));
    std::ifstream ifs("Config\\window.ini");
    std::string window_title = "None";
    sf::VideoMode window_bounds(800, 600, 32);
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;
    if (ifs)
    {
        std::getline(ifs, window_title);
        ifs >> window_bounds.width >> window_bounds.height >> window_bounds.bitsPerPixel;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs.close();
    }
    else
    {
        throw std::logic_error("Coulnd not open ini file");
    }
    this->window = std::make_unique<sf::RenderWindow>(window_bounds, window_title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void GameWindow::initSounds()
{
    if (!soundBuffer["Explosion"].loadFromFile("Music\\explosion.wav"))
    {
        throw std::logic_error("Could not load explosion sound");
    }
    sounds["Explosion"].setBuffer(soundBuffer["Explosion"]);
}

void GameWindow::initBackground()
{
    backgroundTexture = std::make_unique<sf::Texture>();
    if (!(backgroundTexture->loadFromFile("Pictures\\Background\\mainBackground.jpg")))
    {
        throw std::logic_error("Could not load background texture");
    }
    background.setTexture(backgroundTexture.get());
    xBackgroundSize = backgroundTexture->getSize().x;
    yBackgroundSize = backgroundTexture->getSize().y;
    background.setSize(sf::Vector2f(xBackgroundSize, yBackgroundSize));
}

void GameWindow::initFonts()
{
    if (!arial.loadFromFile("Fonts\\arial.ttf") || !CHILLER.loadFromFile("Fonts\\CHILLER.ttf"))
    {
        throw std::logic_error("Could not load font");
    }
}

void GameWindow::initPlayer()
{
    player = std::make_unique<Player>("Executor", 0.25, 0.25);
}

void GameWindow::initEnemies()
{
    this->numberOfEnemyShips = rand() % 8 + 10;
    Enemy baseEnemy("Eshator", 0.1, 0.1);
    for (size_t i = 0; i < numberOfEnemyShips; i++)
    {
        enemyShips.push_back(baseEnemy);
    }
}

void GameWindow::initView()
{
    mainView.setCenter(player->getPosition());
    mainView.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    if (mainView.getCenter().x - window->getSize().x / 2 < 0)
    {
        mainView.setCenter(window->getSize().x / 2, mainView.getCenter().y);
    }
    else
    {
        if (mainView.getCenter().x + window->getSize().x / 2 > xBackgroundSize)
        {
            mainView.setCenter(xBackgroundSize - window->getSize().x / 2, mainView.getCenter().y);
        }
    }

    if (mainView.getCenter().y - window->getSize().y / 2 < 0)
    {
        mainView.setCenter(mainView.getCenter().x, window->getSize().y / 2);
    }
    else
    {
        if (mainView.getCenter().y + window->getSize().y / 2 > yBackgroundSize)
        {
            mainView.setCenter(mainView.getCenter().x, yBackgroundSize - window->getSize().y / 2);
        }
    }
}

void GameWindow::initBars()
{
    healthBar = std::make_unique<GameBar>(sf::Vector2f(250, 30), sf::Vector2f(30, 30));
    healthBar->setFont(arial);
    energyBar = std::make_unique<GameBar>(sf::Vector2f(250, 30), sf::Vector2f(30, 80), sf::Color::Blue);
    energyBar->setFont(arial);
}

void GameWindow::initScore()
{
    this->currentScore = 0;
    SCORE.setFont(arial);
    SCORE.setCharacterSize(40);
    SCORE.setFillColor(sf::Color::Yellow);
    SCORE.setString("SCORE : 0");
    sf::FloatRect scoreRect = SCORE.getLocalBounds();
    SCORE.setPosition(window->mapPixelToCoords(sf::Vector2i(window->getSize().x - scoreRect.width - 20, 5), mainView));
}

void GameWindow::initSummary()
{
    endGameText.setFont(CHILLER);
    endGameText.setCharacterSize(150);
    endGameText.setStyle(sf::Text::Bold | sf::Text::Italic);
    endGameText.setString("");
    sf::FloatRect defeatRect = endGameText.getLocalBounds();
    endGameText.setOrigin(defeatRect.width / 2, defeatRect.height / 2);
    endGameText.setPosition(window->mapPixelToCoords(sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2), mainView));

    endScore.setFont(CHILLER);
    endScore.setCharacterSize(40);
    endScore.setFillColor(endGameText.getFillColor());
    endScore.setString("YOUR SCORE : " + std::to_string(currentScore));
    sf::FloatRect endScoreRect = endScore.getLocalBounds();
    endScore.setOrigin(endScoreRect.width / 2, endScoreRect.height / 2);
    endScore.setPosition(window->mapPixelToCoords(sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2 + defeatRect.height + 10), mainView));
}

void GameWindow::initMiniMap()
{
    miniMapTexture = std::make_unique<sf::Texture>();
    if (!miniMapTexture->loadFromFile("Pictures\\MiniMap\\miniMap.jpg"))
    {
        throw std::logic_error("Could not load mini map texture");
    }

    playerCircle = std::make_unique<sf::CircleShape>(70);
    playerCircle->setFillColor(sf::Color::Blue);
    playerCircle->setPosition(player->getPosition());
    for (const auto& enemy : enemyShips)
    {
        sf::CircleShape enemyCircle(70);
        enemyCircle.setFillColor(sf::Color::Red);
        enemyCircle.setPosition(enemy.getPosition());
        enemyCircles.push_back(enemyCircle);
    }
    miniMapShape.setTexture(miniMapTexture.get());
    miniMapShape.setSize(sf::Vector2f(xBackgroundSize, yBackgroundSize));
    miniMap.setSize(sf::Vector2f(xBackgroundSize, yBackgroundSize));
    miniMap.setCenter(xBackgroundSize / 2, yBackgroundSize / 2);
    miniMap.setViewport(sf::FloatRect(0, 0.8, 0.2, 0.2));
}

GameWindow::GameWindow()
{
    updateDt();
    initWindow();
    initSounds();
    initBackground();
    initFonts();
    initPlayer();
    initView();
    initEnemies();
    initBars();
    initScore();
    initSummary();
    initMiniMap();
}

GameWindow::~GameWindow()
{
}

void GameWindow::update()
{
    updateDt();
    updateBullets();
    updateShips();
    updateView();
    updateCombat();
    updateExplosion();
    updateScore();
    updateBars();
    if (!player || enemyShips.size() == 0)
    {
        updateResult();
    }
    updateMiniMap();
}

void GameWindow::render()
{
    window->clear();
    drawBackground();
    drawBullets();
    drawShips();
    drawExplosion();
    drawScore();
    drawBars();
    if (!player || enemyShips.size() == 0)
    {
        drawResult();
    }
    drawOnMiniMap();
    window->display();
}

bool GameWindow::startGame()
{
    try
    {
        while (window->isOpen())
        {
            while (window->pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                {
                    window->close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                {
                    return true;
                }
            }
            update();
            render();
        }
    }
    catch (std::exception& error)
    {
        std::cerr << error.what() << std::endl;
    }
    return false;
}

void GameWindow::updateDt()
{
    dt = gameClock.restart().asSeconds();
}

void GameWindow::updateBullets()
{
    if (player)
    {
        while (player->bullets.size() > 0)
        {
            auto lastBullet = player->bullets.end() - 1;
            playerBullets.push_back(*lastBullet);
            player->bullets.pop_back();
        }
    }

    for (auto& enemy : enemyShips)
    {
        while (enemy.bullets.size() > 0)
        {
            auto lastBullet = enemy.bullets.end() - 1;
            enemyBullets.push_back(*lastBullet);
            enemy.bullets.pop_back();
        }
    }

    for (auto bullet = playerBullets.begin(); bullet != playerBullets.end(); bullet++)
    {
        bullet->updateBullet(dt);
        if (bullet->isEndBulletLife())
        {
            playerBullets.erase(bullet);
            bullet--;
        }
    }

    for (auto bullet = enemyBullets.begin(); bullet != enemyBullets.end(); bullet++)
    {
        bullet->updateBullet(dt);
        if (bullet->isEndBulletLife())
        {
            enemyBullets.erase(bullet);
            bullet--;
        }
    }
}

void GameWindow::updateShips()
{
    if (player)
    {
        player->updateEntity(dt);
        player->setSize(sf::Vector2f(player->getTexture()->getSize().x * player->getScale().x, player->getTexture()->getSize().y * player->getScale().y));
    }
    for (auto& ship : enemyShips)
    {
        ship.setSize(sf::Vector2f(ship.getTexture()->getSize().x * ship.getScale().x, ship.getTexture()->getSize().y * ship.getScale().y));
        ship.updateEntity(dt);
    }
}

void GameWindow::updateCombat()
{
    //if player bullets colides with enemy ship
    for (auto ship = enemyShips.begin(); ship != enemyShips.end(); ship++)
    {
        for (auto bullet = playerBullets.begin(); bullet != playerBullets.end(); bullet++)
        {
            if (ship->getGlobalBounds().intersects(bullet->getGlobalBounds()))
            {
                int damage = rand() % 10 + 10;
                playerBullets.erase(bullet);
                bullet--;
                if (ship->shipExplode(damage))
                {
                    sounds["Explosion"].play();
                    if (player)
                    {
                        player->setScore(player->getScore() + 100);
                    }
                    explosions.push_back(Explosion(sf::Vector2f(ship->getPosition()), ship->getSize(), "Explode", 48));
                    enemyShips.erase(ship);
                    enemyCircles.pop_back();
                    ship--;
                    break;
                }
            }
        }
    }

    if (player)
    {
        //if enemy bullets colides with player ship
        for (auto bullet = enemyBullets.begin(); bullet != enemyBullets.end(); bullet++)
        {
            if (player->getGlobalBounds().intersects(bullet->getGlobalBounds()))
            {
                int damage = rand() % 10 + 10;
                enemyBullets.erase(bullet);
                bullet--;
                if (player->shipExplode(damage))
                {
                    currentScore = player->getScore();
                    sounds["Explosion"].play();
                    explosions.push_back(Explosion(sf::Vector2f(player->getPosition()), player->getSize(), "Explode", 48));
                    player.reset();
                    playerCircle.reset();
                    break;
                }
            }
        }
    }
}

void GameWindow::updateExplosion()
{
    for (auto explode = explosions.begin(); explode != explosions.end(); explode++)
    {
        explode->updateEntity(dt);
        if (explode->getTextureIndex() == explode->getTextureNumber())
        {
            explosions.erase(explode);
            explode--;
        }
    }
}

void GameWindow::updateResult()
{
    if (endGameText.getString().getSize() != 0)
    {
        sf::FloatRect defeatRect = endGameText.getLocalBounds();
        endGameText.setPosition(window->mapPixelToCoords(sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2), mainView));
        endScore.setPosition(window->mapPixelToCoords(sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2 + defeatRect.height + 10), mainView));
    }
    else if (player)
    {
        currentScore = player->getScore();
        endGameText.setString("WIN");
        endGameText.setFillColor(sf::Color::Yellow);
    }
    else
    {
        endGameText.setString("DEFEAT");
        endGameText.setFillColor(sf::Color::Red);
    }
    sf::FloatRect defeatRect = endGameText.getLocalBounds();
    endGameText.setOrigin(defeatRect.width / 2, defeatRect.height / 2);
    endScore.setFillColor(endGameText.getFillColor());
    endScore.setString("YOUR SCORE : " + std::to_string(currentScore));
}

void GameWindow::updateMiniMap()
{
    if (player)
    {
        playerCircle->setPosition(player->getPosition());
    }
    std::vector<sf::Vector2f> enemyPositions;
    for (const auto& enemy : enemyShips)
    {
        enemyPositions.push_back(enemy.getPosition());
    }
    size_t counter = 0;
    for (auto& enemyCircle : enemyCircles)
    {
        enemyCircle.setPosition(enemyPositions[counter]);
        counter++;
    }
}

void GameWindow::updateScore()
{
    if (player)
    {
        sf::FloatRect scoreRect = SCORE.getLocalBounds();
        std::string newScoreText = "SCORE : ";
        newScoreText += std::to_string(player->getScore());
        SCORE.setString(newScoreText);
        SCORE.setPosition(window->mapPixelToCoords(sf::Vector2i(window->getSize().x - scoreRect.width - 20, 5), mainView));
    }
}

void GameWindow::updateBars()
{
    if (player)
    {
        healthBar->updateBar(player->getCurrentHP(), player->getMaxHP(), window.get(), mainView);
        energyBar->updateBar(player->getCurrentEnergy(), player->getMaxEnergy(), window.get(), mainView);
    }
    else
    {
        healthBar->updateBar(0, 1, window.get(), mainView);
        energyBar->updateBar(0, 1, window.get(), mainView);
    }
}

void GameWindow::updateView()
{
    if (player)
    {
        mainView.setCenter(player->getPosition());
        if (mainView.getCenter().x - window->getSize().x / 2 < 0)
        {
            mainView.setCenter(window->getSize().x / 2, mainView.getCenter().y);
        }
        else
        {
            if (mainView.getCenter().x + window->getSize().x / 2 > xBackgroundSize)
            {
                mainView.setCenter(xBackgroundSize - window->getSize().x / 2, mainView.getCenter().y);
            }
        }

        if (mainView.getCenter().y - window->getSize().y / 2 < 0)
        {
            mainView.setCenter(mainView.getCenter().x, window->getSize().y / 2);
        }
        else
        {
            if (mainView.getCenter().y + window->getSize().y / 2 > yBackgroundSize)
            {
                mainView.setCenter(mainView.getCenter().x, yBackgroundSize - window->getSize().y / 2);
            }
        }
    }
    window->setView(mainView);
}

void GameWindow::drawBackground()
{
    window->draw(background);
}

void GameWindow::drawBullets()
{
    for (const auto& bullet : playerBullets)
    {
        window->draw(bullet);
    }
    for (const auto& bullet : enemyBullets)
    {
        window->draw(bullet);
    }
}

void GameWindow::drawShips()
{
    if (player)
    {
        window->draw(*player);
    }
    for (const auto& enemy : enemyShips)
    {
        window->draw(enemy);
    }
}

void GameWindow::drawExplosion()
{
    for (const auto& explosion : explosions)
    {
        window->draw(explosion);
    }
}

void GameWindow::drawResult()
{
    window->draw(endGameText);
    window->draw(endScore);
}

void GameWindow::drawScore()
{
    window->draw(SCORE);
}

void GameWindow::drawBars()
{
    healthBar->drawBar(window.get());
    energyBar->drawBar(window.get());
}

void GameWindow::drawOnMiniMap()
{
    window->setView(miniMap);
    window->draw(miniMapShape);
    if (player)
    {
        window->draw(*playerCircle);
    }
    for (const auto& enemyCircle : enemyCircles)
    {
        window->draw(enemyCircle);
    }
}
