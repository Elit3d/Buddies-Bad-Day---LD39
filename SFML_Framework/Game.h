#ifndef _GAME_H_
#define _GAME_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>

#include "GameStates.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Pickup.h"

const std::string levelFiles[7] = { "maps/intro_level_1.tmx", "maps/intro_level_2.tmx", "maps/intro_level_3.tmx", "maps/level_1.tmx", "maps/level_2.tmx", "maps/level_3.tmx", "maps/level_4.tmx" };

class Game
{
public:
	Game();
	~Game();

	// Begin Main functions
	void Setup();
	void Update(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	// End Main functions

	//void LevelFiles();
	void UpdateGameStates();
	bool LevelCollider(Level &lvl); // Handles level collision
	void ExitCollider(Level &lvl); // Next level
	void RestartLevel(); // Handles restarting the level
	void EnergySpawner(Level &lvl); // Handles spawning pickups
	void StartPosition(Level &lvl);
	void ErasePickups(); // Handles removing pickups
	void EnergyUI();

	float DotProduct(const sf::Vector2f &a, const sf::Vector2f &b);
private:
	GameStates *state;
	Player *player;
	Enemy *enemy;
	Level *level;
	Pickup *pickups;

	std::vector<Object> obj;
	std::vector<Character*> charVector;
	std::vector<Character*>::iterator charIter;
	std::vector<Pickup*> pickupVector;
	std::vector<Pickup*>::iterator pickupIter;
	
	//std::string levelFiles[NUM_OF_LVLS];

	sf::Texture animationTexture;
	sf::Sprite animationSprite;

	sf::Texture animation_enemyTexture;
	sf::Sprite animation_enemySprite;

	sf::Clock Clock;

	sf::Texture testPickup;
	sf::Sprite testSprite;

	sf::Texture energyTexture;
	sf::Sprite energySprite;

	float splashCounter = 0.f;
	float loadCounter = 0.f;
	int counter = 0;
	bool bSpawnNoMore = false;

	sf::Texture splashTexture;
	sf::Sprite splashSprite;

	sf::Texture menuTexture;
	sf::Sprite menuSprite;

	sf::Texture winTexture;
	sf::Sprite winSprite;

	sf::SoundBuffer pickupSoundB;
	sf::Sound pickupSound;

	sf::SoundBuffer walkSoundB;
	sf::Sound walkSound;

	sf::SoundBuffer completeSoundB;
	sf::Sound completeSound;

	sf::SoundBuffer deadSoundB;
	sf::Sound deadSound;

	float moveX;
	sf::Vector2f enemyMovement;
};


#endif // !_GAME_H_
