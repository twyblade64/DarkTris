#include "MenuState.hpp"
#include "../Core/Game.hpp"
#include "../Core/Locator.hpp"
#include "../GameObjects/Button.hpp"
#include "../Components/DefaultButtonControllerComponent.hpp"
#include "../Constants/Resources.hpp"
#include "../Utility/MemberCommand.hpp"
#include "../Utility/StaticCommand.hpp"
#include <memory>

MenuState::MenuState(Game& game) : mGame(game) {

}


void MenuState::Enter() {
	ResourceLoader& resourceLoader = Locator::GetResourceLoader();
	resourceLoader.LoadFont(RES_FONT_DEBUG_ID, RES_FONT_DEBUG_PATH);

	mChangeToGame = false;

	std::unique_ptr<Button> p_button = std::unique_ptr<Button>(
		new Button(
			sf::Vector2f(320,240), 
			sf::Vector2f(100,32), 
			std::move(std::unique_ptr<ButtonControllerComponent>(
				new DefaultButtonControllerComponent(
					sf::Vector2f(320,240), 
					sf::Vector2f(100,32), 
					"Potato", 
					*resourceLoader.GetFont(RES_FONT_DEBUG_ID)
				)
			))
		)
	);

	p_button->GetButtonController().SetOnMouseClick(std::move(std::unique_ptr<Command>( new MemberCommand<MenuState>( *this, &MenuState::ChangeToGame))));

	mGame.objectList.push_back(std::move(p_button));
}

State* MenuState::Update() {
	if (mChangeToGame) return &mGame.mGameState;
	return this;
}

void MenuState::Exit() {

}

void MenuState::ChangeToGame() {
	mChangeToGame = true;
}
