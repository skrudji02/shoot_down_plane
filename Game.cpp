#include "Game.h"

void Game:: initVariables()
{
	window = nullptr;
    plane = nullptr;
    points = 0;
    planeSpawnTimerMax = 300.f;
    planeSpawnTimer = planeSpawnTimerMax;
    maxPlane=6;
    mouseHeld = false;
    health = 10;
}

void Game:: initWindow()
{
	window = new  sf::RenderWindow (sf::VideoMode(width, height), "Game", sf::Style::Titlebar | sf::Style::Close);
    plane = new sf::RectangleShape[maxPlane];
    window->setFramerateLimit(60);
}

Game::Game()
{
	initVariables();
	initWindow();
}

Game::~Game()
{
	delete window;
    delete[]plane;
}

bool Game::run()
{
	return window->isOpen();
}

void Game:: positionMouse()
{
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game:: updatePlane()
{
    float speed_planeX = 3.f;
    float speed_planeY = 0.f;

    
        if (planeSpawnTimer >= planeSpawnTimerMax)
        {
            spawnPlane();
            planeSpawnTimer = 0;
        }
        else
            planeSpawnTimer += 1.f;
    

    for(int i=0; i < maxPlane;i++)
        plane[i].move(speed_planeX, speed_planeY);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (mouseHeld == false)
            {
                for (int i = 0; i < maxPlane; i++)
                {
                    if (plane[i].getGlobalBounds().contains(mousePosView))
                    {
                        planeSpawnTimer = 0;
                        points++;
                        std::cout << "Score :" << points <<"\n";
                        RespawnPlane(i);
                    }
                }
                mouseHeld = true;
            }
        }
        else
            mouseHeld = false;

        for (int i = 0; i < maxPlane; i++)
        {
            if ( plane[i].getPosition().x >= 800) //window->getPosition().x
            {
                health -= 10;
                planeSpawnTimer = 0;
                std::cout << "Health :" << health <<"\n";
                RespawnPlane(i);
            }

        }
        
        //system("cls");
        //std::cout << planeSpawnTimer;
        
}

void Game:: renderPlane()
{
    for (int i = 0; i < maxPlane; i++)
    window->draw(plane[i]);
}

void Game::spawnPlane()
{
    for (int i=0; i < maxPlane; i++)
    {
        plane[i].setPosition(0.f,static_cast<float>(rand() % static_cast<int>(window->getSize().y - plane[i].getSize().y)));
        plane[i].setSize(sf::Vector2f(50.f, 50.f));
        plane[i].setFillColor(sf::Color::Blue);
        plane[i].setOutlineColor(sf::Color::Blue);
        plane[i].setOutlineThickness(1.f);
    }

    // чтобы позиции квадратов были разные
    for (int i = 0; i < maxPlane; i++)
    {
        for (int j = 1; j < maxPlane-1; j++)
        {
            if (plane[i].getPosition().y == plane[j].getPosition().y)
            {
                while (plane[i].getPosition().y != plane[j].getPosition().y)
                {
                    plane[i].setPosition(0.f, static_cast<float>(rand() % static_cast<int>(window->getSize().y - plane[i].getSize().y)));
                }
            }
        }
    }
}

void Game::RespawnPlane(int i)
{
    
        plane[i].setPosition(
            0.f,
            static_cast<float>(rand() % static_cast<int>(window->getSize().y - plane[i].getSize().y))
        );
        plane[i].setSize(sf::Vector2f(50.f, 50.f));
        plane[i].setFillColor(sf::Color::Blue);
        plane[i].setOutlineColor(sf::Color::Blue);
        plane[i].setOutlineThickness(1.f);
    
}

void Game:: pollEvents()
{
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        }
    }
}

void Game:: update()
{
    pollEvents();

    positionMouse();

    updatePlane();

    if (health <= 0)
        window->close();
}

void Game:: render()
{
    this->window->clear(sf::Color::Black);

    renderPlane();

    this->window->display();
}

