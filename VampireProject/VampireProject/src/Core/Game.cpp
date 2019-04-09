#include <assert.h>

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

	sf::ConvexShape convex;
	convex.setPointCount(3);

	sf::Vector3f pivot(320,240,0);
	sf::Vector3f point(0, -100,0);
	Quaternion rot = Quaternion::AngleAxis(360.f / 3, sf::Vector3f(0, 0, 1));

	sf::Vector3f dist = sf::Vector3f(mousePos.x, mousePos.y, 0) - sf::Vector3f(320, 240, 0);
	Quaternion dirQuat = Quaternion::LookRotation(sf::Vector3f(0, -1, 0), dist);
	point = dirQuat * point;

	convex.setPoint(0, Vector3fToVector2f(pivot + point));

	point = rot * point;
	convex.setPoint(1, Vector3fToVector2f(pivot + point));

	point = rot * point;
	convex.setPoint(2, Vector3fToVector2f(pivot + point));

	convex.setFillColor(sf::Color(0, 255, 0));
	window.draw(convex);

	point = rot * point;
	sf::CircleShape shape(10.f);
	shape.setOrigin(sf::Vector2f(10, 10));
	shape.setPosition(sf::Vector2f(point.x + pivot.x, point.y + pivot.y));
	shape.setFillColor(sf::Color(255, 0, 0));
	window.draw(shape);

	window.display();
}
