#include "GameState.hpp"
#include "../GameObjects/Grid.hpp"
#include "../Core/Game.hpp"

GameState::GameState(Game& game) : mGame(game) {

}

void GameState::Enter() {
    std::unique_ptr<Grid> p_grid = std::unique_ptr<Grid>(new Grid(sf::Vector2i(4, 4), 100, sf::Vector2f(320 - 100 * 2, 240 - 100 * 1.5f * 0.86f)));
	GridControllerComponent& gcc = p_grid->GetGridController();

	gcc.SetPivotNode(1,1);
	gcc.SetPivotNode(1,2);
	gcc.SetPivotNode(2,2);

	gcc.SetTriangleTile(1,0, sf::Color(255,100,50), 1);
	gcc.SetTriangleTile(2,0, sf::Color(255,100,50), 0);
	gcc.SetTriangleTile(3,0, sf::Color(255,100,50),-1);
	gcc.SetTriangleTile(3,1, sf::Color(255,100,50), 1);

	gcc.SetTriangleTile(0,1, sf::Color(50,255,50),  1);
	gcc.SetTriangleTile(1,1, sf::Color(50,255,50),  0);
	gcc.SetTriangleTile(0,2, sf::Color(50,255,50), -1);
	gcc.SetTriangleTile(1,2, sf::Color(50,255,50),  0);

	gcc.SetTriangleTile(2,2, sf::Color(50,50,255), -1);
	gcc.SetTriangleTile(3,2, sf::Color(50,50,255),  0);
	gcc.SetTriangleTile(4,2, sf::Color(50,50,255),  1);
	gcc.SetTriangleTile(4,1, sf::Color(50,50,255), -1);

	gcc.GenerateMissingTriangles(sf::Color(50,50,50));
	mGame.objectList.push_back(std::move(p_grid));
}

State* GameState::Update() {
    return this;
}

void GameState::Exit() {
    mGame.objectList.clear();
}