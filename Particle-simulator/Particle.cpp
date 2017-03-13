#include "Particle.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

void Particle::update(bool isMouseClicked, sf::Vector2f mouse, bool space, float zoom)
{
	mouse = (mouse - sf::Vector2f(500, 500)) / zoom;


	if (isMouseClicked)
		addForce(mouse, 2, calculateDistance(mouse));

	if (space)
		stop();


	setColor();

	drag();

	move();


}

float Particle::calculateDistance(sf::Vector2f forceOrgin)
{
	float difX = forceOrgin.x - position.x;
	float difY = forceOrgin.y - position.y;
	return sqrt(pow(difX, 2)) + sqrt(pow(difY, 2));
}

void Particle::stop()
{
	velocity = sf::Vector2f(0, 0);
}

void Particle::setColor()
{
	if (velocity.x > 1000.f || velocity.y > 1000.f)
		color.y = 255.f;

	else
	{
		if (std::abs(velocity.x) > std::abs(velocity.y))
			color.y = std::abs(velocity.x) / 4.f;

		else
			color.y = std::abs(velocity.y) / 4.f;
	}
}

void Particle::move()
{
	position += 0.05f * velocity;
}

void Particle::drag()
{
	velocity *= 0.995f;
}


void Particle::addForce(sf::Vector2f forceOrgin, float forceValue, float distance)
{
	float fakemass = 500.f;

	shift = forceOrgin - position; 
	//velocity += (shift*mass*fakemass) / pow(distance, 2);	//standard
	velocity += (mass * shift) / distance;					//v1
	//velocity += shift / distance*mass;					//v2 preety nice
}




Particle::Particle(sf::Vector2f _position, sf::Vector2f _velocity, float _mass)
{
	mass = _mass;
	shift = _velocity;
	velocity = _velocity;
	position = _position;
	color = sf::Vector3f(255,0,0);
}

Particle::Particle()
{
}


Particle::~Particle()
{
}
