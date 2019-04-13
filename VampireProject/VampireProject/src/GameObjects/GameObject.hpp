#ifndef HEX_GAMEOBJECT_H_
#define HEX_GAMEOBJECT_H_

#include "GameObjectBase.hpp"
#include <SFML/Graphics.hpp>

template <class T>
class GameObject : public GameObjectBase {
public:
	void FixedUpdate(float dt) {
		static_cast<T*>(this)->FixedUpdateImplementation(dt);
	}

	void VarUpdate(float dt) {
		static_cast<T*>(this)->VarUpdateImplementation(dt);
	}

	void Render(sf::RenderWindow& rw) {
		static_cast<T*>(this)->RenderImplementation(rw);
	}

	virtual ~GameObject() {};
};


#endif // HEX_GAMEOBJECT_H_