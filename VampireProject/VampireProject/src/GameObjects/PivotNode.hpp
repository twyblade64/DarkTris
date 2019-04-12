#ifndef HEX_PIVOTNODE_H_
#define HEX_PIVOTNODE_H_

#include "GameObject.hpp"

class PivotNode : public GameObject<PivotNode> {
public:
	PivotNode();
	~PivotNode();
public:
	void UpdateImplementation(float dt);
	void DrawImplementation(sf::RenderWindow& rw);
};


#endif // HEX_PIVOTNODE_H_