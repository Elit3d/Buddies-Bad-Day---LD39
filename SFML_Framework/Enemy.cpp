#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(std::string imgpath, int health, sf::Vector2f location)
	: Character(imgpath, health, location)
{
	state = new EnemyStates(IDLE);
}

void Enemy::Update()
{
	Character::Update();

	States();
}

void Enemy::Draw(sf::RenderWindow &window)
{
	Character::Draw(window);
}

EnemyStates Enemy::GetStates()
{
	return *state;
}

void Enemy::States()
{
	switch (GetStates())
	{
	case IDLE:
		break;
	case SEEK:
		break;
	case FLEE:
		break;
	case WANDER:
		break;
	case PURSUIT:
		break;
	case EVADE:
		break;
	case SOCIAL:
		break;
	}
}

void Enemy::setHealth(int health)
{
	Character::setHealth(health);
}

int Enemy::getHealth()
{
	return Character::getHealth();
}