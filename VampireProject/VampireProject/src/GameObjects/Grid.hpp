#ifndef HEX_GRID_H_
#define HEX_GRID_H_

#include <vector>>
#include "GameObject.hpp"

class Grid : GameObject<Grid> {
public:
	Grid(int width, int height);
	Grid();
private:
	void UpdateImplementation(float dt);
	void DrawImplementation();
private:
	std::vector<int> gridState;
	//std::vector<TriangleTile> triangles;
};

#endif // HEX_GRID_H_