#ifndef HEX_GAME_STATE_H_
#define HEX_GAME_STATE_H_

#include "../Core/State.hpp"

class Game;
class GameState: public State {
public:
    GameState(Game& game);
public:
    virtual void Enter() override;
    virtual State* Update() override;
    virtual void Exit() override;
private:
    Game& mGame;
};

#endif // HEX_GAME_STATE_H_
