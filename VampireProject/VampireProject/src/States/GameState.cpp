#include "GameState.hpp"
#include "../GameObjects/Grid.hpp"
#include "../Core/Game.hpp"

GameState::GameState(Game& game) : mGame(game) {

}

void GameState::Enter() {
    std::unique_ptr<Grid> p_grid = std::unique_ptr<Grid>(new Grid(sf::Vector2f(320 - 100 * 2, 240 - 100 * 1.5f * 0.86f), sf::Vector2i(4, 4), 100));
	GridControllerComponent& gcc = p_grid->GetGridController();

	gcc.SetPivotNode(1,1);
	gcc.SetPivotNode(1,2);
	gcc.SetPivotNode(2,2);

	gcc.SetTriangleTile(1,0, TileConfiguration(TILE_TYPE_RED  , TILE_DIR_RIGHT));
	gcc.SetTriangleTile(2,0, TileConfiguration(TILE_TYPE_RED  , TILE_DIR_NONE ));
	gcc.SetTriangleTile(3,0, TileConfiguration(TILE_TYPE_RED  , TILE_DIR_LEFT ));
	gcc.SetTriangleTile(3,1, TileConfiguration(TILE_TYPE_RED  , TILE_DIR_RIGHT));

	gcc.SetTriangleTile(0,1, TileConfiguration(TILE_TYPE_GREEN, TILE_DIR_RIGHT));
	gcc.SetTriangleTile(1,1, TileConfiguration(TILE_TYPE_GREEN, TILE_DIR_NONE ));
	gcc.SetTriangleTile(0,2, TileConfiguration(TILE_TYPE_GREEN, TILE_DIR_LEFT ));
	gcc.SetTriangleTile(1,2, TileConfiguration(TILE_TYPE_GREEN, TILE_DIR_NONE ));

	gcc.SetTriangleTile(2,2, TileConfiguration(TILE_TYPE_BLUE , TILE_DIR_LEFT ));
	gcc.SetTriangleTile(3,2, TileConfiguration(TILE_TYPE_BLUE , TILE_DIR_NONE ));
	gcc.SetTriangleTile(4,2, TileConfiguration(TILE_TYPE_BLUE , TILE_DIR_RIGHT));
	gcc.SetTriangleTile(4,1, TileConfiguration(TILE_TYPE_BLUE , TILE_DIR_LEFT ));

	gcc.GenerateTriangles();

	gcc.Scramble(100);

	mGame.objectList.push_back(std::move(p_grid));
}

State* GameState::Update() {
    return this;
}

void GameState::Exit() {
    mGame.objectList.clear();
}