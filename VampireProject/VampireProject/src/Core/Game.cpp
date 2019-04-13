#include <assert.h>
#include <memory>
#include <vector>
#include <string>
#include "Game.hpp"
#include "../GameObjects/TriangleTile.hpp"
#include "../GameObjects/Grid.hpp"
#include "../Math/Utils.hpp"
#include "../Managers/Input.hpp"
#include "../Math/Quaternion.hpp"

Game* Game::mInstance;

float fixedUpdateDeltaRate = 120.f;
float fixedUpdateDeltaTime = 1.f/fixedUpdateDeltaRate;
float fixedRenderRate = 60.f;
float fixedRenderTime = 1.f/fixedRenderRate;

float t;
float dt;
sf::Vector2f mousePos;
sf::Font font;

Game::Game()
	: window(sf::VideoMode(640, 480), "HexProject") {

	Managers::Input::GetInstance();
	srand((int)time(NULL));

	font.loadFromFile("Resources/Fonts/Xolonium-Regular.otf");
	
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
	
	t = 0;
	float updateAccumulator = 0.f;
	float renderAccumulator = 0.f;
	    
	while (window.isOpen()) {
		sf::Time deltaTime = clock.restart();

		dt = deltaTime.asSeconds();
		t += dt;

		ProcessEvents();

		updateAccumulator += dt;
		while (updateAccumulator > fixedUpdateDeltaTime) {
			FixedUpdate();
			updateAccumulator -= fixedUpdateDeltaTime;
		}

		VarUpdate();

		if (renderAccumulator == 0)
			Render();
		renderAccumulator += dt;
		if (renderAccumulator > fixedRenderTime) renderAccumulator = 0;

		Managers::Input::GetInstance().KeyReset();
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
		case sf::Event::Closed: {
			window.close();
			break;
			}
		case sf::Event::KeyPressed:{
			Managers::Input::GetInstance().KeyPress(event.key.code);
			break;
			}
		case sf::Event::KeyReleased: {
			Managers::Input::GetInstance().KeyRelease(event.key.code);
			break;
			}
		case sf::Event::MouseMoved: {
			sf::Vector2f mousePos = sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y);
			Grid& g  = static_cast<Grid&>(*objectList.front());
			g.OnMouseMove(mousePos);
			break;
			}
		case sf::Event::MouseButtonPressed: {
			sf::Vector2f mousePos = sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y);
			Grid& g  = static_cast<Grid&>(*objectList.front());
			g.OnMousePress(mousePos);
			break;
			}
		case sf::Event::MouseButtonReleased: {
			sf::Vector2f mousePos = sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y);
			Grid& g  = static_cast<Grid&>(*objectList.front());
			g.OnMouseRelease(mousePos);
			break;
			}
		}
	}
}

void Game::FixedUpdate() {
	for (auto it = objectList.begin(); it != objectList.end(); ++it) {
		(*it)->FixedUpdate(dt);
	}
}

void Game::VarUpdate() {
	for (auto it = objectList.begin(); it != objectList.end(); ++it) {
		(*it)->VarUpdate(dt);
	}
}

void Game::Render() {
	window.clear();

	for (auto& obj : objectList)
		obj->Render(window);

	std::string fpsString = "FPS: " + std::to_string(1.f/dt);
	sf::Text text(fpsString, font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);
	window.draw(text);

	window.display();
}
