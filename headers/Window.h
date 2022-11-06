#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Particle.h"

class Window
{
private:
	
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//particles
	std::vector<Particle> particles;
	float particleDelay;
	float particleDelayMax;
	int maxParticles;

	//mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//mouse held
	bool mouseHeld;

	//Private functions
	void initVariables();
	void initWindow();
	
public:
	//constructor
	Window();
	
	//destructor
	virtual ~Window();
	
	//setters
	const bool running() const;

	//functions
	void pollEvents();
	
	void checkParticleCollision();

	void updateParticles();

	void updateMousePositions();

	void addParticles();

	void deleteParticles();

	void update();
	
	void render();
};

