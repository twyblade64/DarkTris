#ifndef HEX_GAMEOBJECT_BASE_H_
#define HEX_GAMEOBJECT_BASE_H_

#include <SFML/Graphics.hpp>

class GameObjectBase {
public:
    virtual void Update(float dt) = 0;
    virtual void Draw(sf::RenderWindow& rw) = 0;
	virtual ~GameObjectBase() {};
};

#endif // HEX_GAMEOBJECT_BASE_H_
