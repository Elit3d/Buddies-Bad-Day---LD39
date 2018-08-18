#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "TinyXML\tinyxml.h"
#include <SFML\Graphics.hpp>

struct Object
{
	int GetPropertyInt(std::string name);
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);

	std::string name;
	std::string type;
	std::string id;
	sf::Rect<float> rect;
	std::map<std::string, std::string> properties;
//	bool spawned = false;

	sf::Sprite sprite;
};

struct Layer
{
	int opacity;
	std::vector<sf::Sprite> tiles;
};

class Level
{
public:
	Level();
	~Level();

	bool LoadFromFile(std::string filename);
	std::vector<Object> GetAllObjects();
	Object GetObjectTest();
	void Draw(sf::RenderWindow &window);
	int getLevelID();
	void setLevelID(int lvl);
	void EraseMapObject();
	bool GetLevelComplete();
	void SetLevelComplete(bool _Complete);
	void SetSpawnExit(sf::Vector2f _Position);
	sf::Vector2f GetSpawnExit();

	void DisplayObjectBounds();

	int getItemCount();
private:
	int width, height, tileWidth, tileHeight;
	int firstTileID;
	int tileGID;
	sf::Rect<float> drawingBounds;
	sf::Texture tilesetImage;
	std::vector<Object>::const_iterator objectsVector;
	std::vector<Object> objects;
	std::vector<Layer> layers;
	int level_id;
	bool Complete;
	sf::Vector2f ExitPosition;

	int pickupCounter = 0;
	std::string hexColor;
};

#endif