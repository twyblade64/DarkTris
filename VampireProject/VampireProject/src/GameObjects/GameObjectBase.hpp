#ifndef HEX_GAMEOBJECT_BASE_H_
#define HEX_GAMEOBJECT_BASE_H_

#include <SFML/Graphics.hpp>

class GameObjectBase {
public:
    sf::Vector2f position;
public:
    virtual void FixedUpdate() = 0;
    virtual void VarUpdate() = 0;
    virtual void Render() = 0;
	virtual ~GameObjectBase() {};
};

#endif // HEX_GAMEOBJECT_BASE_H_
