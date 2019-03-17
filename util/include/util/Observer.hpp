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

        virtual void receive(const Message&) = 0;
};


class Subject
{
        Subject() = delete;

public:

        static void addObserver(Observer* const o)
        {
                observers.insert(o);
        }

        static void send(const Message& msg)
        {
                for (Observer* o: observers)
                {
                        o->receive(msg);
                }
        }

private:

        inline static std::unordered_set<Observer*> observers;
};

}