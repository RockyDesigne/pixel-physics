#include "Window.h"

//private functions
void Window::initVariables()
{
	this->window = nullptr;
	this->particleDelayMax = 10.f;
	this->particleDelay = this->particleDelayMax;
	this->maxParticles = 100;
}

void Window::initWindow()
{
	this->videoMode.height = 1080;
	this->videoMode.width = 1920;
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Pixel-Physics", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
}

//constructor
Window::Window()
{
	this->initVariables();
	this->initWindow();
}

//destructor
Window::~Window()
{
	delete this->window;
}

const bool Window::running() const
{
	return this->window->isOpen();
}

//public functions
void Window::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

void Window::checkParticleCollision()
{
	for (size_t i = 0; i < this->particles.size(); i++)
	{
		//check for collison with mouse
		if (this->particles[i].getShape().getGlobalBounds().contains(this->mousePosView))
		{
			//add random vx and vy
			this->particles[i].setVx(static_cast<float>((rand() % 10) - 5));
			this->particles[i].setVy(static_cast<float>((rand() % 10) - 5));
		}
		//check for collision with other particles
		for (size_t k = 0; k < this->particles.size(); k++)
		{
			if (i != k && this->particles[i].getShape().getGlobalBounds().intersects(this->particles[k].getShape().getGlobalBounds()))
			{
				//add random vx and vy
				this->particles[i].setVx(static_cast<float>((rand() % 10) - 5));
				this->particles[i].setVy(static_cast<float>((rand() % 10) - 5));
			}
		}
		//check for collision with window bounds
		
		//check left collision
		if (this->particles[i].getShape().getGlobalBounds().left <= 0.f)
		{
			this->particles[i].setVx(static_cast<float>((rand() % 10) - 5));
		}
		
		//check right collision
		if (this->particles[i].getShape().getGlobalBounds().left + this->particles[i].getShape().getGlobalBounds().width >= this->window->getSize().x)
		{
			this->particles[i].setVx(static_cast<float>((rand() % 10) - 5));
		}
		
		//check top collision
		if (this->particles[i].getShape().getGlobalBounds().top <= 0.f)
		{
			this->particles[i].setVy(static_cast<float>((rand() % 10) - 5));
		}

		//check bottom collision
		if (this->particles[i].getShape().getGlobalBounds().top + this->particles[i].getShape().getGlobalBounds().height >= this->window->getSize().y)
		{
			this->particles[i].setVy(static_cast<float>((rand() % 10) - 5));
		}
	}
}

void Window::updateMousePositions()
{
	//get mouse position relative to window
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	
	//print mouse position
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void Window::addParticles()
{
	//add 10000 particles, each with random positions
	//check vector size
	if (this->particles.size() < 101)
		for (int i = 0; i < 100; ++i)
			{
			this->particles.push_back(Particle(*this->window));
			//set random starting pos
			this->particles[i].setXPos(static_cast<int>(rand() % static_cast<int>(this->window->getSize().x)));
			this->particles[i].setYPos(static_cast<int>(rand() % static_cast<int>(this->window->getSize().y)));
			//set starting pos
			this->particles[i].setPos();
			}
	
	//while mouse is held down
	//add particles
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//add delay between particles
		if (this->particleDelay >= this->particleDelayMax)
		{
			//add particle
			this->particles.push_back(Particle(*this->window));

			//set random starting pos
			this->particles[this->particles.size() - 1].setXPos(static_cast<int>(this->mousePosView.x));
			this->particles[this->particles.size() - 1].setYPos(static_cast<int>(this->mousePosView.y));
			this->particles[this->particles.size() - 1].setPos();

			//reset lifetime
			this->particleDelay = 0.f;
		}
		else
			{
				//increment lifetime
				this->particleDelay += 3.5f;
			}
	}
}

void Window::updateParticles()
{
	//update particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i].update();
	}
}

void Window::deleteParticles()
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

void Window::update()
{
	this->pollEvents();
	
	this->updateMousePositions();

	this->addParticles();

	this->checkParticleCollision();

	this->updateParticles();

	this->deleteParticles();
}

void Window::render()
{
	this->window->clear();

	//draw image to window
	for (auto i : particles)
		i.draw(*this->window);
	
	this->window->display();
}
