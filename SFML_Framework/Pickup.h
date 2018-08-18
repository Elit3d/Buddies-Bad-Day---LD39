#pragma once
#include "Entity.h"
class Pickup :
	public Entity
{
public:
	Pickup(std::string imgpath, sf::Vector2f position);
	~Pickup();

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();
};

