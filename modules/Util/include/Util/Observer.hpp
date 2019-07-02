#pragma once


#include <Util/Math.hpp>
#include <Util/Types.hpp>

#include <entt/entity/registry.hpp>

#include <algorithm>
#include <unordered_set>
#include <variant>


namespace util
{

/** Message representation 
 */
struct Message
{
        // Scenes

        struct SwitchScene
        {
                std::string sceneName;
        };

        struct SaveScene
        {
                SceneID sceneId;
        };

        struct LoadScene
        {
                SceneID sceneId;
        };

        struct Quit {};


        // ECS - Transform

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


        // ECS - Physics

        struct SetEntityVelocity
        {
                entt::entity entity;
                Vector velocity;
        };

        struct AccelerateEntityBy
        {
                entt::entity entity;
                Vector acceleration;
        };

        struct SetEntityMass
        {
                entt::entity entity;
                float mass;
        };


        // Message data

        std::variant<
                SwitchScene,
                SaveScene,
                LoadScene,
                Quit,
                AddEntity,
                SetEntityPosition, MoveEntityBy,
                SetEntityRotation, RotateEntityBy,
                SetEntityScale,    ScaleEntityBy,
                SetEntityVelocity, AccelerateEntityBy,
                SetEntityMass
        > msg;
};


/** Helper template type for message handlers.
 */
template<class... Ts> struct MsgHandlers : Ts... { using Ts::operator()...; };
template<class... Ts> MsgHandlers(Ts...) -> MsgHandlers<Ts...>;


/** Empty message handler for discarding all unhandled messages.
 */
static constexpr auto discardTheRest = [](const auto&) {};


/** Base class for objects that are receiving messages broadcasted by Subject.
 */
class Observer
{
        friend class Subject;

public:

        virtual ~Observer()
        {
        }

private:

        virtual void receive(const Message&) = 0;
};


/** System for broadcasting messages to all gathered observers.
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