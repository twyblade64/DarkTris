#ifndef HEX_STATE_H_
#define HEX_STATE_H_

class State {
public:
    virtual void Enter() = 0;
    virtual State* Update() = 0;
    virtual void Exit() = 0;
};

#endif // HEX_STATE_H_
