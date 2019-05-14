#ifndef HEX_MENU_STATE_H_
#define HEX_MENU_STATE_H_

#include "../Core/State.hpp"

class Game;
class MenuState: public State {
public:
    MenuState(Game& game);
public:
    virtual void Enter() override;
    virtual State* Update() override;
    virtual void Exit() override;
private:
    Game& mGame;
};

#endif // HEX_MENU_STATE_H_
