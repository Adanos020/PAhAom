#pragma once


#include <Engine/Scene.hpp>

#include <Util/Math.hpp>

#include <entt/entity/entity.hpp>

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
        struct PopScene {};

        struct PushScene
        {
                std::string stateName;
        };

        struct SetPosition
        {
                entt::entity entity;
                Vector position;
        };

        struct SetRotation
        {
                entt::entity entity;
                float rotation;
        };

        struct SetScale
        {
                entt::entity entity;
                Vector scale;
        };

        std::variant<
                None,
                PopScene, PushScene,
                SetPosition, SetRotation, SetScale
        > msg;
};


class Observer
{
        friend class Subject;
        virtual void receive(const Message&) = 0;

public:

        virtual ~Observer() {}
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
                std::for_each(observers.begin(), observers.end(),
                        [&](Observer* o) { o->receive(msg); });
        }

private:

        inline static std::unordered_set<Observer*> observers;
};

}