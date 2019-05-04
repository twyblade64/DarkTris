#include <assert.h>
#include <memory>
#include <vector>
#include <string>
#include "../Core/Game.hpp"
#include "../Core/Locator.hpp"
#include "../Services/Window.hpp"
#include "../Services/Time.hpp"
#include "../Services/Input.hpp"
#include "../GameObjects/TriangleTile.hpp"
#include "../GameObjects/Grid.hpp"
#include "../Math/Utils.hpp"
#include "../Math/Quaternion.hpp"

sf::Vector2f mousePos;
sf::Font font;

Game::Game() {
	// Init Systems
	std::unique_ptr<Window> windowService = std::unique_ptr<Window>(new Window(640, 480, "Hex Project"));
	std::unique_ptr<Time> timeService = std::unique_ptr<Time>(new Time(120.f, 60.f));
	std::unique_ptr<Input> inputService = std::unique_ptr<Input>(new Input());

	Locator::InitWindowService(std::move(windowService));
	Locator::InitTimeService(std::move(timeService));
	Locator::InitInputService(std::move(inputService));

	srand((int)time(NULL));

	// Setup initial state
	font.loadFromFile("Resources/Fonts/Xolonium-Regular.otf");

	std::unique_ptr<Grid> p_grid = std::unique_ptr<Grid>(new Grid(sf::Vector2i(4, 4), 100, sf::Vector2f(320 - 100 * 2, 240 - 100 * 1.5f * 0.86f)));
	p_grid->SetPivotNode(1,1);
	p_grid->SetPivotNode(1,2);
	p_grid->SetPivotNode(2,2);

	p_grid->SetTriangleTile(1,0, sf::Color(255,100,50), 1);
	p_grid->SetTriangleTile(2,0, sf::Color(255,100,50), 0);
	p_grid->SetTriangleTile(3,0, sf::Color(255,100,50),-1);
	p_grid->SetTriangleTile(3,1, sf::Color(255,100,50), 1);

	p_grid->SetTriangleTile(0,1, sf::Color(50,255,50),  1);
	p_grid->SetTriangleTile(1,1, sf::Color(50,255,50),  0);
	p_grid->SetTriangleTile(0,2, sf::Color(50,255,50), -1);
	p_grid->SetTriangleTile(1,2, sf::Color(50,255,50),  0);

	p_grid->SetTriangleTile(2,2, sf::Color(50,50,255), -1);
	p_grid->SetTriangleTile(3,2, sf::Color(50,50,255),  0);
	p_grid->SetTriangleTile(4,2, sf::Color(50,50,255),  1);
	p_grid->SetTriangleTile(4,1, sf::Color(50,50,255), -1);

	p_grid->GenerateMissingTriangles(sf::Color(50,50,50));
	objectList.push_back(std::move(p_grid));
}

void Game::Run() {
	sf::Clock clock;
	
	float updateAccumulator = 0.f;
	float renderAccumulator = 0.f;
	    
	Time& timeService = Locator::GetTime();
	Input& inputService = Locator::GetInput();
	sf::RenderWindow& window = Locator::GetWindow().GetRenderWindow();
	while (window.isOpen()) {
		sf::Time deltaTime = clock.restart();

		float dt = deltaTime.asSeconds();
		timeService.UpdateTime(dt);

		ProcessEvents();
		if (!window.isOpen()) break;

		updateAccumulator += dt;
		while (updateAccumulator > timeService.GetFixedUpdateDeltaTime()) {
			FixedUpdate();
			updateAccumulator -= timeService.GetFixedUpdateDeltaTime();
		}

		VarUpdate();

		if (renderAccumulator == 0) Render();
		renderAccumulator += dt;
		if (renderAccumulator > timeService.GetFixedRenderDeltaTime()) renderAccumulator = 0;

		inputService.KeyReset();
	}
}

void Game::ProcessEvents() {
	sf::Event event;
	Input& inputService = Locator::GetInput();
	sf::RenderWindow& window = Locator::GetWindow().GetRenderWindow();

	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: {
			window.clear();
			window.close();
			return;
			}
		case sf::Event::KeyPressed:{
			inputService.KeyPress(event.key.code);
			break;
			}
		case sf::Event::KeyReleased: {
			inputService.KeyRelease(event.key.code);
			break;
			}
		case sf::Event::MouseMoved: {
			sf::Vector2f mousePos = sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y);
			Grid& g  = static_cast<Grid&>(*objectList.front());
			g.OnMouseMove(mousePos);
			break;
			}
		case sf::Event::MouseButtonPressed: {
			sf::Vector2f mousePos = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
			Grid& g  = static_cast<Grid&>(*objectList.front());
			g.OnMousePress(mousePos);
			break;
			}
		case sf::Event::MouseButtonReleased: {
			sf::Vector2f mousePos = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
			Grid& g  = static_cast<Grid&>(*objectList.front());
			g.OnMouseRelease(mousePos);
			break;
			}
		}
	}
}

void Game::FixedUpdate() {
	for (auto it = objectList.begin(); it != objectList.end(); ++it) {
		(*it)->FixedUpdate();
	}
}

void Game::VarUpdate() {
	for (auto it = objectList.begin(); it != objectList.end(); ++it) {
		(*it)->VarUpdate();
	}
}

void Game::Render() {
	sf::RenderWindow& window = Locator::GetWindow().GetRenderWindow();
	window.clear();

	for (auto& obj : objectList)
		obj->Render();

	std::string fpsString = "FPS: " + std::to_string(1.f/Locator::GetTime().GetDeltaTime());
	sf::Text text(fpsString, font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);
	window.draw(text);

	window.display();
}
