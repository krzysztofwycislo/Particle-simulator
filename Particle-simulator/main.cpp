#include <SFML/Graphics.hpp>
#include <SFML/OpenGl.hpp>

#include <vector>
#include <ctime>
#include <iostream>
#include "Particle.hpp"

#define PARTICLES_NUMBER 25000

int main()
{

	//variables time

	srand(unsigned int(time(NULL)));

	bool isMouseClicked = false;
	bool stop = false;
	bool wallsOn = true;

	int window_width = 1000;
	int window_height = 1000;

	double dt = 0.00000001;

	float zoom = 1;

	float tab[PARTICLES_NUMBER * 2];
	unsigned char colortab[PARTICLES_NUMBER * 3];


	sf::Window window(sf::VideoMode(window_width, window_height), "Particles");
	window.setFramerateLimit(30);

	sf::Clock deltaTime;

	sf::Vector2f mousePos;
	sf::Vector2f camPos(0, 0);

	std::vector<Particle> particles;



	//some openGL settings

	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, window_height, 0, -1, 1);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(2.0f);

	//particle creator

	for (int i = 0; i < PARTICLES_NUMBER; i++)
	{
		particles.push_back(
			Particle(
			sf::Vector2f(
						float((std::rand()) % int(window_width) - window_width / 2),
						float((std::rand()) % int(window_height) - window_height / 2)
						),

			sf::Vector2f(
						float(((std::rand()) % 8) - 4),
						float(((std::rand()) % 8) - 4)
						),

			float(std::rand() % 5) + 50)
			);
	}


	while (window.isOpen())
	{

		//some needed variables

		mousePos = sf::Vector2f(float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y));

		sf::Event event;


		//input handle

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta == 1)
					zoom *= 1.1f;

				else
					zoom *= 0.9f;
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					wallsOn = !wallsOn;
				}
			}

		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			isMouseClicked = true;

		else
			isMouseClicked = false;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			stop = true;

		else
			stop = false;




		//main particle loop

		for (int i(0); i < PARTICLES_NUMBER; i++)
		{
			//VBA's
			tab[2 * i] = particles[i].position.x;
			tab[2 * i + 1] = particles[i].position.y;

			colortab[3 * i] = unsigned char(particles[i].color.x);
			colortab[3 * i + 1] = unsigned char(particles[i].color.y);
			colortab[3 * i + 2] = unsigned char(particles[i].color.z);

			//particles position
			particles[i].update(isMouseClicked, mousePos, stop, zoom);

			//colision with walls
			if (wallsOn)
			{
				if (particles[i].position.x > window_width * 2 || particles[i].position.x < -window_width * 2)
				{
					particles[i].velocity.x = -0.9*particles[i].velocity.x;

					if (float(particles[i].position.x) > window_width * 2)
						particles[i].position.x = float(window_width) * 2;
					else
						particles[i].position.x = float(-window_width) * 2;
				}

				if (particles[i].position.y > window_height * 2 || particles[i].position.y < -window_height * 2)
				{
					particles[i].velocity.y = -0.9*particles[i].velocity.y;

					if (particles[i].position.y > window_height * 2)
						particles[i].position.y = window_height * 2;
					else
						particles[i].position.y = -window_height * 2;
				}
			}
		}




		//openGL handle

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();

		glTranslatef(window_width / 2.f, window_height / 2.f, 0);
		glScaled(zoom, zoom, zoom);

		glTranslated(camPos.x, camPos.y, 0);

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY); 


		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colortab);
		glVertexPointer(2, GL_FLOAT, 0, tab);
		glDrawArrays(GL_POINTS, 0, PARTICLES_NUMBER);
	
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);


		glPopMatrix();

		glFlush();
		window.display(); 

		dt = deltaTime.restart().asSeconds();
		std::cout << int(1/dt) << std::endl;
	}



	particles.clear();
	
	return 0;
}