#pragma once

#include <iostream>
#include <ctime>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"


class Game
{
private:

	//Window
	int width = 800;
	int height = 600;
	sf::RenderWindow* window;
	sf::Event ev;

	//Enemy
	sf::RectangleShape *plane;

	//Mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Aim
	sf::RectangleShape aim;

	//Game logic
	int points;
	float planeSpawnTimer;
	float planeSpawnTimerMax;
	int maxPlane;
	bool mouseHeld;
	int health;

private:
	void initVariables();
	void initWindow();
	void pollEvents();
	void spawnPlane();
	void RespawnPlane(int i);
public:
	 Game();
	~Game();
	bool run();
	void positionMouse();
	void updatePlane();
	void renderPlane();
	void update();
	void render();
};

