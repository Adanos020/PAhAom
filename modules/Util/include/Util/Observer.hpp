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

        // Scenes

        struct PopScene {};

        struct PushScene
        {
                std::string stateName;
        };

        // ECS

        struct AddEntity
        {
                lua::Table data;
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
                AddEntity,
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

        static void deleteObserver(Observer* const o)
        {
                observers.erase(o);
        }

        template<class T>
        static void send(const T& msgType)
        {
                send(Message{msgType});
        }

        static void send(const Message& msg)
        {
                for (Observer* o : observers)
                {
                        o->receive(msg);
                }
        }

private:

        inline static std::unordered_set<Observer*> observers;
};

}