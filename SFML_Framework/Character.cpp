#include "Character.h"


Character::Character()
{
	texture.loadFromFile("");
	sprite.setTexture(texture);
	_health = 0;
}


Character::~Character()
{
}


Character::Character(std::string imgpath, int health, sf::Vector2f location)
{
	texture.loadFromFile(imgpath); // load the texture
	sprite.setTexture(texture);  // set sprite to the texture
	sprite.setPosition(location); //initial sprite position
	_health = health;
}

void Character::Update()
{
}

void Character::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void Character::setHealth(int health)
{
	_health = health;
}

int Character::getHealth()
{
	return _health;
}