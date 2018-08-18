#include "Game.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::Setup()
{
	state = new GameStates(State::SPLASH); // Set the first game state
	player = new Player("images/robot.png", 100, sf::Vector2f(224.f, 256.f), 10);
	player->sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	//enemy = new Enemy("images/enemy.png", 100, sf::Vector2f(10.0f, 10.0f)); // Enemy setup
	level = new Level();

	level->LoadFromFile("maps/intro_level_1.tmx"); // load level tilemap from file

	//charVector.push_back(enemy);
	charVector.push_back(player);

	animationTexture.loadFromFile("images/animation.png");
	animationSprite.setTexture(animationTexture);
	animationSprite.setPosition(sf::Vector2f(32.f, 256.f)); //spawn location

	animation_enemyTexture.loadFromFile("images/animation.png");
	animation_enemySprite.setTexture(animation_enemyTexture);
	animation_enemySprite.setPosition(64, 64);


	testPickup.loadFromFile("images/icon-power.png");
	testSprite.setTexture(testPickup);
	testSprite.setScale(sf::Vector2f(-2, -2));

	//LevelFiles();
	energySprite.setScale(5, 5);
	energySprite.setPosition(5, 5);

	StartPosition(*level);

	splashTexture.loadFromFile("images/splash.png");
	splashSprite.setTexture(splashTexture);
	
	menuTexture.loadFromFile("images/menu.png");
	menuSprite.setTexture(menuTexture);

	winTexture.loadFromFile("images/win.png");
	winSprite.setTexture(winTexture);

	pickupSoundB.loadFromFile("sounds/coin1.wav");
	pickupSound.setBuffer(pickupSoundB);

	walkSoundB.loadFromFile("sounds/walk.ogg");
	walkSound.setBuffer(walkSoundB);

	completeSoundB.loadFromFile("sounds/complete.wav");
	completeSound.setBuffer(completeSoundB);

	deadSoundB.loadFromFile("sounds/dead.wav");
	deadSound.setBuffer(deadSoundB);
}

void Game::Update(sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		float dt = Clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (state->GetState() == State::GAME)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					switch (event.key.code)
					{
					case sf::Keyboard::W:
						player->sprite.setTextureRect(sf::IntRect(0, 96, 32, 32));
						player->sprite.move(0.0f, -32.0f);
						player->setPower(player->getPower() - 1); //decrease power
						walkSound.play();

						if (LevelCollider(*level))
						{
							player->sprite.move(0.0f, 32.0f);
							player->setPower(player->getPower() + 1); //increase power
						}
						break;
					case sf::Keyboard::S:
						player->sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
						player->sprite.move(0.0f, 32.0f);
						player->setPower(player->getPower() - 1); //decrease power
						walkSound.play();

						if (LevelCollider(*level))
						{
							player->sprite.move(0.0f, -32.0f);
							player->setPower(player->getPower() + 1); //increase power
						}
						break;
					case sf::Keyboard::A:
						player->sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
						player->sprite.move(-32.0f, 0.0f);
						player->setPower(player->getPower() - 1); //decrease power
						walkSound.play();

						if (LevelCollider(*level))
						{
							player->sprite.move(32.0f, 0.0f);
							player->setPower(player->getPower() + 1); //increase power
						}
						break;
					case sf::Keyboard::D:
						player->sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
						player->sprite.move(32.0f, 0.0f);
						player->setPower(player->getPower() - 1); //decrease power
						walkSound.play();

						if (LevelCollider(*level))
						{
							player->sprite.move(-32.0f, 0.0f);
							player->setPower(player->getPower() + 1); //increase power
						}

						break;
					}
				}
				else if (event.type == sf::Event::KeyReleased)
				{
					switch (event.key.code)
					{
					case sf::Keyboard::D:

						break;
					}
				}


				for (charIter = charVector.begin(); charIter != charVector.end(); charIter++)
				{
					(*charIter)->Update();
				}

				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (level->getLevelID() >= 7)
				state = new GameStates(State::WIN);

			if (player->getPower() > 10)
				player->setPower(10);
			if (player->getPower() <= 0)
			{
				level->setLevelID(level->getLevelID());
				state = new GameStates(State::LOADING);
				deadSound.play();
			}
		}

		UpdateGameStates();

		Draw(window);
	}
}

void Game::EnergySpawner(Level &lvl)
{
	///run this once on level load

	obj = lvl.GetAllObjects();

	for (int i = 0; i < obj.size(); i++)
	{
		if (obj[i].name == "item")
		{
			if (pickupVector.size() > i)
				bSpawnNoMore = true;

			pickups = new Pickup("images/icon-power.png", sf::Vector2f(obj[i].rect.left, obj[i].rect.top));

			if (bSpawnNoMore == false)
				pickupVector.push_back(pickups);
		}
	}
}

//DOT PRODUCT
float Game::DotProduct(const sf::Vector2f &a, const sf::Vector2f &b)
{
	return (a.x*b.x) + (a.y*b.y);
}


void Game::StartPosition(Level &lvl)
{
	obj = lvl.GetAllObjects();

	for (int i = 0; i < obj.size(); i++)
	{
		if (obj[i].name == "start")
		{
			player->sprite.setPosition(obj[i].rect.left - 1.f, obj[i].rect.top - 1.f);
			//std::cout << player->sprite.getPosition().x << " " << player->sprite.getPosition().y << std::endl;
		}
	}
}

void Game::ExitCollider(Level &lvl)
{
	obj = lvl.GetAllObjects();

	for (int i = 0; i < obj.size(); i++)
	{
		if (obj[i].name == "end")
		{
			if (pickupVector.size() <= 0)
			{
				if (player->sprite.getGlobalBounds().intersects(obj[i].rect))
				{
					//std::cout << "next level" << std::endl;
					completeSound.play();
					level->setLevelID(level->getLevelID() + 1);
					state = new GameStates(State::LOADING);
				}
			}
		}
	}
}

bool Game::LevelCollider(Level &lvl)
{
	obj = lvl.GetAllObjects();

	for (int i = 0; i < obj.size(); i++)
	{
		for (charIter = charVector.begin(); charIter != charVector.end(); charIter++)
		{
			if ((*charIter)->sprite.getGlobalBounds().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					return true;
					break;
				}
			}
		}
	}

	return false;
}

void Game::ErasePickups()
{
	counter = 0;
	for (pickupIter = pickupVector.begin(); pickupIter != pickupVector.end(); pickupIter++)
	{
		if (player->sprite.getGlobalBounds().intersects(pickupVector[counter]->sprite.getGlobalBounds()))
		{
			pickupSound.play();
			player->setPower(player->getPower() + 10 + 1); // +1 because the move takes up 1 points
			pickupVector.erase(pickupIter);
			break;
		}
		counter++;
	}
}

void Game::RestartLevel()
{
	//player->sprite.setPosition(32.f, 256.f);

	// Delete the pickup vector incase of failure
	for (pickupIter = pickupVector.begin(); pickupIter != pickupVector.end(); pickupIter++)
	{
		pickupVector.erase(pickupIter);
		break;
	}
}

void Game::EnergyUI()
{
	switch (player->getPower())
	{
	case 0:
		energyTexture.loadFromFile("images/energy/0.png");
		break;
	case 1:
		energyTexture.loadFromFile("images/energy/1.png");
		break;
	case 2:
		energyTexture.loadFromFile("images/energy/2.png");
		break;
	case 3:
		energyTexture.loadFromFile("images/energy/3.png");
		break;
	case 4:
		energyTexture.loadFromFile("images/energy/4.png");
		break;
	case 5:
		energyTexture.loadFromFile("images/energy/5.png");
		break;
	case 6:
		energyTexture.loadFromFile("images/energy/6.png");
		break;
	case 7:
		energyTexture.loadFromFile("images/energy/7.png");
		break;
	case 8:
		energyTexture.loadFromFile("images/energy/8.png");
		break;
	case 9:
		energyTexture.loadFromFile("images/energy/9.png");
		break;
	case 10:
		energyTexture.loadFromFile("images/energy/full.png");
		break;
	}

	energySprite.setTexture(energyTexture);
}

void Game::UpdateGameStates()
{
	switch (state->GetState())
	{
	case SPLASH:
//		std::cout << "In splash" << std::endl;
		splashCounter += 1.f;

		if (splashCounter >= 150.f)
		{
			state = new GameStates(State::MENU);
		}
		break;
	case MENU:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			state = new GameStates(State::GAME);
		break;
	case LOADING:
		level->EraseMapObject();

		// Delete the pickup vector incase of failure
		for (pickupIter = pickupVector.begin(); pickupIter != pickupVector.end(); pickupIter++)
		{
			pickupVector.erase(pickupIter);
			break;
		}

		loadCounter += 1.0f;

		if (level->GetAllObjects().size() <= 0)
		{
			level->LoadFromFile(levelFiles[level->getLevelID()]); // load level tilemap from file
			bSpawnNoMore = false;
			player->setPower(10); // reset the power

			StartPosition(*level);
			EnergySpawner(*level);
			state = new GameStates(State::GAME);
		}
		break;
	case GAME:
		loadCounter = 0.f;

		EnergyUI();

		ErasePickups();
		EnergySpawner(*level);
		ExitCollider(*level);
		break;
	case WIN:
		break;
	case PAUSE:
		
		break;
	case OPTIONS:

		break;
	}
}

void Game::Draw(sf::RenderWindow &window)
{
	window.clear();
	// Begin Draw
	sf::VertexArray teststrip(sf::LineStrip, 5);
	float vertX = 192;
	float vertY = 224;
	float vertW = 416;
	float vertH = 32;
	switch (state->GetState())
	{
	case SPLASH:
//		std::cout << "In splash" << std::endl;
		
		//splash image
		window.draw(splashSprite);
		break;
	case MENU:

		//credits and font saying click to play

		window.draw(menuSprite);
		break;
	case LOADING:
		break;
	case GAME:
		

		level->Draw(window); // draw the level tilemap

		//window.draw(animationSprite);

		teststrip[0].position = sf::Vector2f(vertX, vertY);
		teststrip[1].position = sf::Vector2f(vertX + vertW, vertY);
		teststrip[2].position = sf::Vector2f(vertX+vertW, vertY+vertH);
		teststrip[3].position = sf::Vector2f(vertX,vertY+vertH);
		teststrip[4].position = teststrip[0].position;

		for (int i = 0; i < 4; i++)
		{
			teststrip[i].color = sf::Color::Red;
		}

		window.draw(teststrip);

		for (charIter = charVector.begin(); charIter != charVector.end(); charIter++)
		{
			(*charIter)->Draw(window);
		}

		for (int i = 0; i < pickupVector.size(); i++)
			window.draw(pickupVector[i]->sprite);

		// UI View
		window.setView(window.getDefaultView());

		window.draw(energySprite);
		break;
	case WIN:
		window.draw(winSprite);
		break;
	case PAUSE:
		
		break;
	case OPTIONS:

		break;
	}

	// End Draw
	window.display();
}