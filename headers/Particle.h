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
	int xPos;
	int yPos;

	//private functions
	void initShape(const sf::RenderWindow& window);
	void initVariables();
public:
	//constructor
	Particle(const sf::RenderWindow& window);
	
	//Destructor
	virtual ~Particle();

	//accessors
	const sf::CircleShape& getShape() const;
	
	//setters
	
	//set xpos
	void setXPos(int x);

	//set ypos
	void setYPos(int y);
	
	//set vy
	void setVy(float vy);
	//set vx
	void setVx(float vx);

	//set x and y initial position
	void setPos();

	//accesors
	// 
	//get xpos
	int getXPos() const;
	
	//get ypos
	int getYPos() const;

	int getLifeTime() const;
	
	//functions
	
	void update();
	
	void draw(sf::RenderTarget& target);
};

