#pragma once

#include <SFML/Graphics.hpp>
class Particle
{
public:

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f shift;
	sf::Vector3f color;

	float mass;

	float calculateDistance(sf::Vector2f forceOrgin);

	void move();
	void update(bool isMouseClicked, sf::Vector2f mouse, bool space, float zoom);
	void addForce(sf::Vector2f forceOrgin, float forceValue, float distance);
	void drag();
	void setColor();
	void stop();

	Particle(sf::Vector2f _position, sf::Vector2f _velocity, float _mass);

	Particle();
	~Particle();
};

