#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Particle.h"

class window final
{
private:
	
	//window
	sf::RenderWindow* window_{};
	sf::VideoMode video_mode_;
	sf::Event ev_{};

	//particles
	std::vector<particle> particles_;
	float particle_delay_{};
	float particle_delay_max_{};
	int max_particles_{};

	//mouse positions
	sf::Vector2i mouse_pos_window_;
	sf::Vector2f mouse_pos_view_;

	//random dist
	std::mt19937 mt_rand_{ std::random_device{}() };
	std::uniform_int_distribution<int> dist_;

	//mouse held
	//bool mouse_held_{};

	//Private functions
	void init_variables();
	void init_window();
	
public:
	//constructor
	window();
	
	//destructor
	~window();
	
	//setters
	bool running() const;

	//functions
	void set_dist(int min, int max);

	void poll_events();
	
	void check_particle_collision();

	void update_particles();

	void update_mouse_positions();

	void add_particles();

	static void delete_particles();

	void update();

	void render() const;
};

