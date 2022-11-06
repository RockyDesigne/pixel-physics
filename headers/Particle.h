#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>

class Particle
{

private:
	sf::CircleShape shape;
	
	float lifeTime;
	float vx;
	float vy;

	//private functions
	void initShape(const sf::RenderWindow& window);
	void initVariables();
public:
	//constructor
	Particle(const sf::RenderWindow& window, int x = 0, int y = 0);
	
	//Destructor
	virtual ~Particle();

	//accessors
	const sf::CircleShape& getShape() const;
	
	//setters
	
	//set vy
	void setVy(float vy);
	//set vx
	void setVx(float vx);

	int getLifeTime() const;
	
	//functions
	
	void update();
	
	void draw(sf::RenderTarget& target);
};

