#pragma once


#include <Engine/GameState.hpp>

#include <algorithm>
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
                std::string stateName;
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

        virtual auto receive(const Message&) -> void = 0;
};


class Subject
{
        Subject() = delete;

public:

        static auto addObserver(Observer* const o) -> void
        {
                observers.insert(o);
        }

        static auto send(const Message& msg) -> void
        {
                std::for_each(observers.begin(), observers.end(),
                        [&](Observer* o) { o->receive(msg); });
        }

private:

        inline static std::unordered_set<Observer*> observers;
};

}