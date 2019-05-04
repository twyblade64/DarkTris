#ifndef HEX_PIVOTNODE_H_
#define HEX_PIVOTNODE_H_

#include "GameObject.hpp"

class PivotNode : public GameObject<PivotNode> {
public:
	PivotNode();
	~PivotNode();
public:
	void FixedUpdateImplementation();
	void VarUpdateImplementation();
	void RenderImplementation();
};


#endif // HEX_PIVOTNODE_H_