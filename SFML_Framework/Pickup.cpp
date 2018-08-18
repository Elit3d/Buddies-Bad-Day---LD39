#include "Pickup.h"


Pickup::Pickup(std::string imgpath, sf::Vector2f position)
{
	texture.loadFromFile(imgpath);
	sprite.setTexture(texture);
	sprite.setPosition(position);
}


Pickup::~Pickup()
{
}

void Pickup::SetPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

sf::Vector2f Pickup::GetPosition()
{
	return sprite.getPosition();
}