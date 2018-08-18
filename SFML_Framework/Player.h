#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Character.h"
class Player :
	public Character
{
public:
	Player();
	~Player();
	Player(std::string imgpath, int health, sf::Vector2f location, int _power);

	void Update();
	void Draw(sf::RenderWindow &window);

	void setHealth(int health);
	int getHealth();

	void setPower(int _power);
	int getPower();
private:
	int power;
};


#endif // !_PLAYER_H_
