#include <assert.h>
#include <memory>
#include <string>
#include "../Core/Game.hpp"
#include "../Core/Locator.hpp"
#include "../Services/Window.hpp"
#include "../Services/Time.hpp"
#include "../Services/Input.hpp"
#include "../Math/Utils.hpp"
#include "../Math/Quaternion.hpp"

sf::Vector2f mousePos;
sf::Font font;

Game::Game() : mGameState(*this), mMenuState(*this) {
	// Init Systems
	std::unique_ptr<Window> windowService = std::unique_ptr<Window>(new Window(640, 480, "Hex Project"));
	std::unique_ptr<Time> timeService = std::unique_ptr<Time>(new Time(120.f, 60.f));
	std::unique_ptr<Input> inputService = std::unique_ptr<Input>(new Input());

	Locator::InitWindowService(std::move(windowService));
	Locator::InitTimeService(std::move(timeService));
	Locator::InitInputService(std::move(inputService));

	srand((int)time(NULL));

	// Setup initial state
	mCurrentState = &mGameState;
	mCurrentState->Enter();

	// Resource load (?)
	font.loadFromFile("Resources/Fonts/Xolonium-Regular.otf");
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

		State* newState = mCurrentState->Update();
		if (newState != mCurrentState) {
			mCurrentState->Exit();
			mCurrentState = newState;
			mCurrentState->Enter();
		}

		inputService.InputReset();
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
			inputService.MouseMove(mousePos);
			break;
			}
		case sf::Event::MouseButtonPressed: {
			inputService.MousePress(event.mouseButton.button);
			break;
			}
		case sf::Event::MouseButtonReleased: {
			inputService.MouseRelease(event.mouseButton.button);
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
