#include "Window.h"

//private functions
void window::init_variables()
{
	this->window_ = nullptr;
	this->particle_delay_max_ = 10.f;
	this->particle_delay_ = this->particle_delay_max_;
	this->max_particles_ = 100;
}

void window::init_window()
{
	this->video_mode_.height = 1080;
	this->video_mode_.width = 1920;
	this->window_ = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Pixel-Physics", sf::Style::Titlebar | sf::Style::Close);
	this->window_->setFramerateLimit(144);
}

//constructor
window::window()
{
	this->init_variables();
	this->init_window();
}

//destructor
window::~window()
{
	delete this->window_;
}

bool window::running() const
{
	return this->window_->isOpen();
}

void window::set_dist(const int min, const int max)
{
	this->dist_ = std::uniform_int_distribution<int>(min, max);
}

//public functions
void window::poll_events()
{
	while (this->window_->pollEvent(this->ev_))
		switch (this->ev_.type)
		{
		case sf::Event::Closed:
			this->window_->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev_.key.code == sf::Keyboard::Escape)
				this->window_->close();
			break;
	}
}

void window::check_particle_collision()
{
	for (size_t i = 0; i < this->particles_.size(); i++)
	{
		//set dist
		set_dist(-5, 5);

		//check for collision with mouse
		if (this->particles_[i].get_shape().getGlobalBounds().contains(this->mouse_pos_view_))
		{
			//add random vx and vy
			this->particles_[i].set_vx(static_cast<float>(this->dist_(this->mt_rand_)));
			this->particles_[i].set_vy(static_cast<float>(this->dist_(this->mt_rand_)));
		}
		//check for collision with other particles
		for (size_t k = 0; k < this->particles_.size(); k++)
			if (i != k && this->particles_[i].get_shape().getGlobalBounds().intersects(this->particles_[k].get_shape().getGlobalBounds()))
			{
				//add random vx and vy
				this->particles_[i].set_vx(static_cast<float>(this->dist_(this->mt_rand_)));
				this->particles_[i].set_vy(static_cast<float>(this->dist_(this->mt_rand_)));
			}
		//check for collision with window bounds
		
		//check left collision
		if (this->particles_[i].get_shape().getGlobalBounds().left <= 0.f)
			this->particles_[i].set_vx(static_cast<float>(this->dist_(this->mt_rand_)));
		
		//check right collision
		if (this->particles_[i].get_shape().getGlobalBounds().left + this->particles_[i].get_shape().getGlobalBounds().width >= static_cast<float>(this->window_->getSize().x))
			this->particles_[i].set_vx(static_cast<float>(this->dist_(this->mt_rand_)));
		
		//check top collision
		if (this->particles_[i].get_shape().getGlobalBounds().top <= 0.f)
			this->particles_[i].set_vy(static_cast<float>(this->dist_(this->mt_rand_)));

		//check bottom collision
		if (this->particles_[i].get_shape().getGlobalBounds().top + this->particles_[i].get_shape().getGlobalBounds().height >= static_cast<float>(this->window_->getSize().y))
			this->particles_[i].set_vy(static_cast<float>(this->dist_(this->mt_rand_)));
	}
}

void window::update_mouse_positions()
{
	//get mouse position relative to window
	this->mouse_pos_window_ = sf::Mouse::getPosition(*this->window_);
	this->mouse_pos_view_ = this->window_->mapPixelToCoords(this->mouse_pos_window_);
	
	//print mouse position
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void window::add_particles()
{

	if (this->particles_.size() < 101)
		for (int i = 0; i < 100; ++i)
			{
			particles_.emplace_back(*this->window_);

			//rand dist
			std::uniform_real_distribution<float> dist(0.0f, 1.0f); // local

			//set random starting pos
			this->particles_[i].set_x_pos(dist(this->mt_rand_) * static_cast<float>(this->window_->getSize().x));
			this->particles_[i].set_y_pos(dist(this->mt_rand_) * static_cast<float>(this->window_->getSize().y));
			//set starting pos
			this->particles_[i].set_pos();
			}
	
	//while mouse is held down
	//add particles
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//add delay between particles
		if (this->particle_delay_ >= this->particle_delay_max_)
		{
			//add particle
			this->particles_.emplace_back(*this->window_);

			//set random starting pos
			this->particles_[this->particles_.size() - 1].set_x_pos(this->mouse_pos_view_.x);
			this->particles_[this->particles_.size() - 1].set_y_pos(this->mouse_pos_view_.y);
			this->particles_[this->particles_.size() - 1].set_pos();

			//reset lifetime
			this->particle_delay_ = 0.f;
		}
		else
				//increment lifetime
				this->particle_delay_ += 3.5f;
	}
}

void window::update_particles()
{
	//update particles
	for (auto& particle : particles_)
		particle.update();
}

// TO DO
void window::delete_particles()
{
	//if particle lifetime is 0, remove particle
	/*for (auto i : particles)
	{
		if (i.getLifeTime() <= 0)
		{
			particles.pop_back();
		}*/
		
		//if particle is out of bounds, remove particle
		/*if (particles[i].getShape().getPosition().x < 0 || particles[i].getShape().getPosition().x > this->window->getSize().x ||
			particles[i].getShape().getPosition().y < 0 || particles[i].getShape().getPosition().y > this->window->getSize().y)
		{
			particles.erase(particles.begin() + i);
		}*/
	//}
}

void window::update()
{
	this->poll_events();
	
	this->update_mouse_positions();

	this->add_particles();

	this->check_particle_collision();

	this->update_particles();

	this->delete_particles();
}

void window::render() const
{
	this->window_->clear();

	//draw image to window
	for (auto &i : particles_)
		i.draw(*this->window_);
	
	this->window_->display();
}
