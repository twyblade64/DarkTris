#ifndef HEX_GAMEOBJECT_H_
#define HEX_GAMEOBJECT_H_

#include "GameObjectBase.hpp"
#include <SFML/Graphics.hpp>

template <class T>
class GameObject : public GameObjectBase {
public:
	void Update(float dt) {
		static_cast<T*>(this)->UpdateImplementation(dt);
	}

	void Draw(sf::RenderWindow& rw) {
		static_cast<T*>(this)->DrawImplementation(rw);
	}

	virtual ~GameObject() {};
};


#endif // HEX_GAMEOBJECT_H_