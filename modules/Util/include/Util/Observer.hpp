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

/** 
 */
struct Message
{
        // Scenes

        struct SwitchScene
        {
                std::string sceneName;
        };

        struct SaveAndSwitchScene
        {
                std::string sceneName;
        };

        struct LoadScene
        {
                std::string sceneName;
        };

        struct SaveAndLoadScene
        {
                std::string sceneName;
        };

        struct Quit {};

        struct SaveAndQuit {};

        // ECS

        struct AddEntity
        {
                lua::Table data;
        };

        struct SetEntityPosition
        {
                entt::entity entity;
                Vector position;
        };

        struct SetEntityRotation
        {
                entt::entity entity;
                float rotation;
        };

        struct SetEntityScale
        {
                entt::entity entity;
                Vector scale;
        };

        struct MoveEntityBy
        {
                entt::entity entity;
                Vector displacement;
        };

        struct RotateEntityBy
        {
                entt::entity entity;
                float rotation;
        };

        struct ScaleEntityBy
        {
                entt::entity entity;
                Vector scale;
        };


        std::variant<
                SwitchScene, SaveAndSwitchScene,
                LoadScene, SaveAndLoadScene,
                Quit, SaveAndQuit,
                AddEntity,
                SetEntityPosition, SetEntityRotation, SetEntityScale,
                MoveEntityBy, RotateEntityBy, ScaleEntityBy
        > msg;
};

/** Helper template type for message handlers.
 */
template<class... Ts> struct MsgHandlers : Ts... { using Ts::operator()...; };
template<class... Ts> MsgHandlers(Ts...) -> MsgHandlers<Ts...>;

/**
 * 
 */
class Observer
{
        friend class Subject;
        virtual void receive(const Message&) = 0;

public:

        virtual ~Observer() {}
};

/**
 * 
 */
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