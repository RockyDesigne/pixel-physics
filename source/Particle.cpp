#include "Particle.h"

//private functions
void particle::init_shape(const sf::RenderWindow& window)
{
	this->shape_.setRadius(10.f);

	//set dist
	set_dist(0, 255);
	//set random color
	const sf::Color color(this->dist_(this->mt_rand_), // random nums in range[0, 255] so no precision loss
		this->dist_(this->mt_rand_), 
		this->dist_(this->mt_rand_));
	this->shape_.setFillColor(color);
}

void particle::init_variables()
{
	//set vx and vy initial values
	this->vx_ = 0;
	
	this->vy_ = 0;

	// x_dist random real nums in [0, 1920]
	std::uniform_real_distribution<float> x_dist(1.f, 1920.f);

	//set initial xpos
	this->x_pos_ = x_dist(this->mt_rand_);

	// y_dist random real nums in [0, 1080]
	std::uniform_real_distribution<float> y_dist(1.f, 1080.f);

	// set initial ypos
	this->y_pos_ = y_dist(this->mt_rand_);

	//set dist
	set_dist(1, 1000);
	//set random lifetime
	this->life_time_ = this->dist_(this->mt_rand_);
}

//constructor
particle::particle(const sf::RenderWindow& window)
{	
	this->init_shape(window);

	this->init_variables();
}

//Destructor
particle::~particle()
= default;

const sf::CircleShape& particle::get_shape() const
{
	return this->shape_;
}

void particle::set_dist(const int min, const int max)
{
	this->dist_ = std::uniform_int_distribution<int>(min, max);
}

void particle::set_x_pos(const float x)
{
	this->x_pos_ = x;
}

void particle::set_y_pos(const float y)
{
	this->y_pos_ = y;
}

void particle::set_vy(const float vy)
{
	this->vy_ = vy;
}

void particle::set_vx(const float vx)
{
	this->vx_ = vx;
}

void particle::set_pos()
{
	this->shape_.setPosition(this->x_pos_, this->y_pos_);
}

float particle::get_x_pos() const
{
	return this->x_pos_;
}

float particle::get_y_pos() const
{
	return this->y_pos_;
}

//public functions
int particle::get_life_time() const
{
	return this->life_time_;
}

void particle::update()
{
	//decrement particle lifetime
	this->life_time_--;

	//update particle position
	this->shape_.move(this->vx_, this->vy_);
}

void particle::draw(sf::RenderTarget& target) const
{
	target.draw(this->shape_);
}
