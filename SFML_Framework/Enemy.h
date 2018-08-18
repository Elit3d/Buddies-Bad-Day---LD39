#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Character.h"

enum EnemyStates
{
	IDLE,
	SEEK, // Find a location
	FLEE, // Run away from danger
	WANDER, // Walk aimless away from fixed points
	PURSUIT, // Track or hunt
	EVADE, // Avoid
	SOCIAL // Talk to other AI
};

class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();
	Enemy(std::string imgpath, int health, sf::Vector2f location);

	void Update();
	void Draw(sf::RenderWindow &window);

	void setHealth(int health);
	int getHealth();

protected:
	EnemyStates GetStates();
	void States();
private:
	EnemyStates *state;
};

#endif
