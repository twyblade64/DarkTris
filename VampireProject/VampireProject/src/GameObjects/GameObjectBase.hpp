#ifndef HEX_GAMEOBJECT_BASE_H_
#define HEX_GAMEOBJECT_BASE_H_

#include <SFML/Graphics.hpp>

class GameObjectBase {
public:
    virtual void FixedUpdate(float dt) = 0;
    virtual void VarUpdate(float dt) = 0;
    virtual void Render(sf::RenderWindow& rw) = 0;
	virtual ~GameObjectBase() {};
};

#endif // HEX_GAMEOBJECT_BASE_H_
