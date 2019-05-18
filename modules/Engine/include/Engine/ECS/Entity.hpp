#pragma once


#include <Engine/ECS/Component.hpp>

#include <Util/Types.hpp>

#include <algorithm>
#include <bitset>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>


namespace engine::ecs
{

class Entity
{
public:

        Entity() = default;

        Entity(const Entity& copy)
        : componentFlags(copy.componentFlags)
        , idIndices(copy.idIndices)
        {
                for (const std::unique_ptr<Component>& comp : copy.components)
                {
                        this->components.emplace_back(comp->copy());
                }
        }

        Entity(Entity&& move)
        : components(std::move(move.components))
        , componentFlags(std::move(move.componentFlags))
        , idIndices(std::move(move.idIndices))
        {
        }

        template<class CompClass, typename... Args>
        void addComponent(Args... args)
        {
                static_assert(std::is_base_of_v<Component, CompClass>);
                this->components.push_back(std::make_unique<CompClass>(std::forward<Args>(args)..., this));
                this->componentFlags.set(getComponentTypeID<CompClass>());
                this->idIndices.push_back(getComponentTypeID<CompClass>());
        }

        void update()
        {
                for (std::unique_ptr<Component>& component : this->components)
                {
                        component->update();
                }
        }

        template<class CompClass>
        bool hasComponent() const
        {
                static_assert(std::is_base_of_v<Component, CompClass>);
                return this->componentFlags.test(getComponentTypeID<CompClass>());
        }

        template<class CompClass>
        std::optional<std::reference_wrapper<CompClass>> getComponent()
        {
                static_assert(std::is_base_of_v<Component, CompClass>);
                static const std::size_t index = findComponentIndex<CompClass>();
                if (index < MAX_COMPONENTS)
                {
                        return reinterpret_cast<CompClass&>(*this->components[index]);
                }
                return {};
        }

private:

        template<class CompClass>
        std::size_t findComponentIndex()
        {
                if (not this->hasComponent<CompClass>())
                {
                        return -1;
                }
                static const ComponentTypeID id = getComponentTypeID<CompClass>();
                for (size_t i = 0; i < this->idIndices.size(); ++i)
                {
                        if (this->idIndices[i] == id)
                        {
                                return i;
                        }
                }
        }

private:

        util::UniquePtrs<Component> components;
        std::bitset<MAX_COMPONENTS> componentFlags;
        std::vector<ComponentTypeID> idIndices;
};

}