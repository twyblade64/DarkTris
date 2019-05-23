#ifndef HEX_MEMBER_COMMAND_H_
#define HEX_MEMBER_COMMAND_H_

#include "Command.hpp"

template <class T>
class MemberCommand : public Command {
    public:
        MemberCommand(T& target, void (T::*action)()) : target(target), action(action) { };
    public:
        void Call() override {
            (target.*action)();
        };
    private:
        T& target;
        void (T::*action)();
};

#endif // HEX_MEMBER_COMMAND_H_
