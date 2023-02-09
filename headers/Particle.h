#pragma once

#include <random>

#include <SFML/Graphics.hpp>

class particle final
{

private:
	sf::CircleShape shape_;

	std::mt19937 mt_rand_{ std::random_device{}() };
	std::uniform_int_distribution<int> dist_;
	int life_time_{};
	float vx_{};
	float vy_{};
	float x_pos_{};
	float y_pos_{};

	//private functions
	void init_shape(const sf::RenderWindow& window);
	void init_variables();
public:
	//constructor
	explicit particle(const sf::RenderWindow& window);
	
	//Destructor
	~particle();

	//accessors
	const sf::CircleShape& get_shape() const;
	
	//setters

	//set dist
	void set_dist(int min, int max);
	
	//set xpos
	void set_x_pos(float x);

	//set ypos
	void set_y_pos(float y);
	
	//set vy
	void set_vy(float vy);
	//set vx
	void set_vx(float vx);

	//set x and y initial position
	void set_pos();

	//accessors

	//get xpos
	float get_x_pos() const;
	
	//get ypos
	float get_y_pos() const;

	int get_life_time() const;
	
	//functions

	void update();
	
	auto draw(sf::RenderTarget& target) const -> void;
};

