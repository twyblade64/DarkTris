#include <assert.h>

#include <vector>
#include "Game.hpp"
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
	srand(time(NULL));
	t = 0;
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
			mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
			break;
		}
	}
}

void Game::Update(sf::Time deltaTime) {

}

void Game::Render() {
	window.clear();

	float gridSize = 50;
	float yDelta = gridSize*0.866025f;
	sf::Vector2i gridDimensions(15,13);
	sf::Vector2f gridOrigin(-gridSize*.5,0);

	std::vector<sf::Vector2f> gridPos(gridDimensions.x*gridDimensions.y);
	for (int y = 0; y < gridDimensions.y; ++y) {
		for (int x = 0; x < gridDimensions.x; ++x ) {
			gridPos[x+y*gridDimensions.x] = sf::Vector2f(
				(gridOrigin.x) + (x * gridSize) + (y%2==1?gridSize*0.5f:0) ,
				(gridOrigin.y) + (y * yDelta)
			);
		}
	}

	for (int y = 0; y < gridDimensions.y; ++y) {
		for (int x = 0; x < gridDimensions.x; ++x ) {
			sf::CircleShape circle(2.f);
			circle.setOrigin(sf::Vector2f(2,2));
			circle.setFillColor(sf::Color(255,255,255));
			circle.setPosition(gridPos[x+y*gridDimensions.x].x, gridPos[x+y*gridDimensions.x].y);
			window.draw(circle);
		}
	}

	for (int y = 0; y < gridDimensions.y - 1; ++y) {
		for (int x = 0; x < gridDimensions.x; ++x ) {
			if (x+1<gridDimensions.x) {
				sf::ConvexShape tri;
				tri.setPointCount(3);
				tri.setPoint(0, gridPos[(y  )*gridDimensions.x+x]);
				tri.setPoint(1, gridPos[(y  )*gridDimensions.x+x+1]);
				tri.setPoint(2, gridPos[(y+1)*gridDimensions.x+x+y%2]);
				tri.setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
				// tri.setFillColor(sf::Color(0x80808080));
				window.draw(tri);
			}
			if (x > -y%2 && x < gridDimensions.x - y%2) {
				sf::ConvexShape tri;
				tri.setPointCount(3);
				tri.setPoint(0, gridPos[(y  )*gridDimensions.x+x]);
				tri.setPoint(1, gridPos[(y+1)*gridDimensions.x+x-1+y%2]);
				tri.setPoint(2, gridPos[(y+1)*gridDimensions.x+x-1+y%2+1]);
				tri.setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
				// tri.setFillColor(sf::Color(0x80808080));
				window.draw(tri);
			}
		}
	}

	// sf::ConvexShape convex;
	// convex.setPointCount(3);

	// sf::Vector3f pivot(320,240,0);
	// sf::Vector3f point(0, -100,0);
	// Quaternion rot = Quaternion::AngleAxis(360.f / 3, sf::Vector3f(0, 0, 1));

	// sf::Vector3f dist = sf::Vector3f(mousePos.x, mousePos.y, 0) - sf::Vector3f(320, 240, 0);
	// Quaternion dirQuat = Quaternion::LookRotation(sf::Vector3f(0, -1, 0), dist);
	// point = dirQuat * point;

	// convex.setPoint(0, Vector3fToVector2f(pivot + point));

	// point = rot * point;
	// convex.setPoint(1, Vector3fToVector2f(pivot + point));

	// point = rot * point;
	// convex.setPoint(2, Vector3fToVector2f(pivot + point));

	// convex.setFillColor(sf::Color(0, 255, 0));
	// window.draw(convex);

	// point = rot * point;
	// sf::CircleShape shape(10.f);
	// shape.setOrigin(sf::Vector2f(10, 10));
	// shape.setPosition(sf::Vector2f(point.x + pivot.x, point.y + pivot.y));
	// shape.setFillColor(sf::Color(255, 0, 0));
	// window.draw(shape);

	window.display();
}
