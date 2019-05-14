#include "MenuState.hpp"
#include "../Core/Game.hpp"

MenuState::MenuState(Game& game) : mGame(game) {

}


void MenuState::Enter() {

}

State* MenuState::Update() {
	return this;
}

void MenuState::Exit() {

}