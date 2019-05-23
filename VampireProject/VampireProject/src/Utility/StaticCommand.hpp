#ifndef HEX_STATIC_COMMAND_H_
#define HEX_STATIC_COMMAND_H_

#include "Command.hpp"

class StaticCommand : public Command {
   public:
        StaticCommand(void (*action)()) : action(action) { };
    public:
        void Call() override {
            action();
        };
    private:
        void (*action)();
};

#endif // HEX_STATIC_COMMAND_H_
