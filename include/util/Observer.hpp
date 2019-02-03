#pragma once


#include <PAhAom/GameState/GameState.hpp>

#include <string_view>
#include <type_traits>
#include <unordered_set>
#include <variant>


namespace util
{

struct Message
{
        struct None {};
        struct PopState {};

        struct PushState
        {
                PAhAom::GameState::State* state;
        };

        std::variant<None,
                     PopState,
                     PushState
        > msg;
};


class Observer
{
        friend class Subject;
private:

        virtual void receive(const Message) = 0;
};


class Subject
{
        Subject() = delete;

public:

        static void addObserver(Observer* const);
        static void send(const Message);

private:

        inline static std::unordered_set<Observer*> observers;
};

}