#ifndef HEX_GAMEOBJECT_H_
#define HEX_GAMEOBJECT_H_

#include "GameObjectBase.hpp"
#include <SFML/Graphics.hpp>

template <class T>
class GameObject : public GameObjectBase {
public:
	void FixedUpdate() override {
		static_cast<T*>(this)->FixedUpdateImplementation();
	}

	void VarUpdate() override {
		static_cast<T*>(this)->VarUpdateImplementation();
	}

	void Render() override {
		static_cast<T*>(this)->RenderImplementation();
	}
};


#endif // HEX_GAMEOBJECT_H_