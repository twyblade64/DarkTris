#ifndef HEX_GAMEOBJECT_H_
#define HEX_GAMEOBJECT_H_

template <class T>
class GameObject {
public:
	void Update(float dt) {
		static_cast<T*>(this)->UpdateImplementation(float dt);
	}

	void Draw(sf::RenderWindow& rw) {
		static_cast<T*>(this)->DrawImplementation();
	}
};


#endif // HEX_GAMEOBJECT_H_