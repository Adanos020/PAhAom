#pragma once


#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <memory>
#include <type_traits>


namespace engine::ecs
{

class Entity;

using ComponentTypeID = unsigned int;
static constexpr std::size_t MAX_COMPONENTS = 32;

class Component
{
public:

        virtual ~Component() {}
        virtual void update() = 0;

        std::unique_ptr<Component> copy() const;

protected:

        ComponentTypeID typeID;
        Entity* owner;
};

inline ComponentTypeID getComponentTypeID()
{
        static ComponentTypeID id = 0;
        return id++;
}

template<class CompClass>
inline ComponentTypeID getComponentTypeID() noexcept
{
        static_assert(std::is_base_of_v<Component, CompClass>);
        static const ComponentTypeID id = getComponentTypeID();
        return id;
}

}