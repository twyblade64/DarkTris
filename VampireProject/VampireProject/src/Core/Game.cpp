#include <assert.h>
#include <memory>
#include <vector>
#include "Game.hpp"
#include "../GameObjects/TriangleTile.hpp"
#include "../GameObjects/Grid.hpp"
#include "../Math/Utils.hpp"
#include "../Managers/Input.hpp"
#include "../Math/Quaternion.hpp"

Game* Game::mInstance;

float t;
float dt;
sf::Vector2f mousePos;

Game::Game()
	: window(sf::VideoMode(640, 480), "HexProject") {

	Managers::Input::GetInstance();
	srand((int)time(NULL));
	t = 0;

	// objectList.push_back(std::move(std::unique_ptr<GameObjectBase>(new TriangleTile(sf::Vector2f(320, 240), 50.f, sf::Color(255,255,255), 0))));
	
	std::unique_ptr<Grid> p_grid = std::unique_ptr<Grid>(new Grid(sf::Vector2i(8,5), 50, sf::Vector2f(100,100)));
	p_grid->SetPivotNode(1,1);
	p_grid->SetPivotNode(4,2);
	p_grid->SetPivotNode(6,2);
	p_grid->SetPivotNode(3,3);
	p_grid->SetTriangleTile(1,0, sf::Color(0,255,255));
	p_grid->GenerateMissingTriangles(sf::Color(100,100,100));
	objectList.push_back(std::move(p_grid));
}

void Game::Run() {
	sf::Clock clock;
	while (window.isOpen()) {
		sf::Time deltaTime = clock.restart();

		dt = deltaTime.asSeconds();
		t += dt;

		ProcessEvents();

		Update(deltaTime);
		Managers::Input::GetInstance().KeyReset();

		Render();
	}
}

Game* Game::Get() {
	assert(mInstance);
	return mInstance;
}

void Game::ProcessEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			Managers::Input::GetInstance().KeyPress(event.key.code);
			break;
		case sf::Event::KeyReleased:
			Managers::Input::GetInstance().KeyRelease(event.key.code);
			break;
		case sf::Event::MouseMoved:
			mousePos = sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y);
			break;
		}
	}
}

void Game::Update(sf::Time deltaTime) {
	for (auto it = objectList.begin(); it != objectList.end(); ++it) {
		(*it)->Update(dt);
	}
}

void Game::Render() {
	window.clear();

	for (auto& obj : objectList)
		obj->Draw(window);

	// float gridSize = 50;
	// float yDelta = gridSize*0.866025f;
	// sf::Vector2i gridDimensions(15,13);
	// sf::Vector2f gridOrigin(-gridSize*.5,0);

	// std::vector<sf::Vector2f> gridPos(gridDimensions.x*gridDimensions.y);
	// for (int y = 0; y < gridDimensions.y; ++y) {
	// 	for (int x = 0; x < gridDimensions.x; ++x ) {
	// 		gridPos[x+y*gridDimensions.x] = sf::Vector2f(
	// 			(gridOrigin.x) + (x * gridSize) + (y%2==1?gridSize*0.5f:0) ,
	// 			(gridOrigin.y) + (y * yDelta)
	// 		);
	// 	}
	// }

	// for (int y = 0; y < gridDimensions.y; ++y) {
	// 	for (int x = 0; x < gridDimensions.x; ++x ) {
	// 		sf::CircleShape circle(2.f);
	// 		circle.setOrigin(sf::Vector2f(2,2));
	// 		circle.setFillColor(sf::Color(255,255,255));
	// 		circle.setPosition(gridPos[x+y*gridDimensions.x].x, gridPos[x+y*gridDimensions.x].y);
	// 		window.draw(circle);
	// 	}
	// }

	// for (int y = 0; y < gridDimensions.y - 1; ++y) {
	// 	for (int x = 0; x < gridDimensions.x; ++x ) {
	// 		if (x+1<gridDimensions.x) {
	// 			sf::ConvexShape tri;
	// 			tri.setPointCount(3);
	// 			tri.setPoint(0, gridPos[(y  )*gridDimensions.x+x]);
	// 			tri.setPoint(1, gridPos[(y  )*gridDimensions.x+x+1]);
	// 			tri.setPoint(2, gridPos[(y+1)*gridDimensions.x+x+y%2]);
	// 			tri.setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
	// 			// tri.setFillColor(sf::Color(0x80808080));
	// 			window.draw(tri);
	// 		}
	// 		if (x > -y%2 && x < gridDimensions.x - y%2) {
	// 			sf::ConvexShape tri;
	// 			tri.setPointCount(3);
	// 			tri.setPoint(0, gridPos[(y  )*gridDimensions.x+x]);
	// 			tri.setPoint(1, gridPos[(y+1)*gridDimensions.x+x-1+y%2]);
	// 			tri.setPoint(2, gridPos[(y+1)*gridDimensions.x+x-1+y%2+1]);
	// 			tri.setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
	// 			// tri.setFillColor(sf::Color(0x80808080));
	// 			window.draw(tri);
	// 		}
	// 	}
	// }

	window.display();
}
