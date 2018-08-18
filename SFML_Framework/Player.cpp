#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

Player::Player(std::string imgpath, int health, sf::Vector2f location, int _power)
	: Character(imgpath, health, location)
{
	power = _power;
}

void Player::Update()
{
	Character::Update();
}

void Player::Draw(sf::RenderWindow &window)
{
	Character::Draw(window);
}

void Player::setHealth(int health)
{
	Character::setHealth(health);
}

int Player::getHealth()
{
	return Character::getHealth();
}

void Player::setPower(int _power)
{
	power = _power;
}

int Player::getPower()
{
	return power;
}