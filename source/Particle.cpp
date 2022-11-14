#include "Particle.h"

//private functions
void Particle::initShape(const sf::RenderWindow& window)
{
	this->shape.setRadius(10.f);
	
	//set random color
	sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	this->shape.setFillColor(color);
}

void Particle::initVariables()
{
	//set vx and vy initial values
	this->vx = 0;
	
	this->vy = 0;

	//set initial pos
	this->xPos = 0;
	
	this->yPos = 0;

	//set random lifetime
	this->lifeTime = rand() % 1000 + 1;
}

//constructor
Particle::Particle(const sf::RenderWindow& window)
{	
	this->initShape(window);

	this->initVariables();
}

//Destructor
Particle::~Particle()
{
}

const sf::CircleShape& Particle::getShape() const
{
	return this->shape;
}

void Particle::setXPos(int x)
{
	this->xPos = x;
}

void Particle::setYPos(int y)
{
	this->yPos = y;
}

void Particle::setVy(float vy)
{
	this->vy = vy;
}

void Particle::setVx(float vx)
{
	this->vx = vx;
}

void Particle::setPos()
{
	this->shape.setPosition(this->xPos, this->yPos);
}

int Particle::getXPos() const
{
	return this->xPos;
}

int Particle::getYPos() const
{
	return this->yPos;
}

//public functions
int Particle::getLifeTime() const
{
	return this->lifeTime;
}

void Particle::update()
{
	//decrement particle lifetime
	--this->lifeTime;

	//update particle position
	this->shape.move(this->vx, this->vy);
}

void Particle::draw(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
