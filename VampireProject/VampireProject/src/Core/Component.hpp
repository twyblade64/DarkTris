#ifndef HEX_COMPONENT_H_
#define HEX_COMPONENT_H_

template <class T>
class Component {
public:
    void FixedUpdate() {
		static_cast<T*>(this)->FixedUpdateImplementation();
	}

	void VarUpdate() {
		static_cast<T*>(this)->VarUpdateImplementation();
	}

	void Render() {
		static_cast<T*>(this)->RenderImplementation();
	}

	virtual ~Component() {};

};

#endif // HEX_COMPONENT_H_

