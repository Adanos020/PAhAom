#pragma once


#include <Util/ErrorMessages.hpp>
#include <Util/Types.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>
#include <type_traits>
#include <unordered_map>


namespace engine
{

// Concepts

template<class T>
concept Loadable = requires(T r)
{
        { r.loadFromFile("") } -> std::same_as<bool>;
        { r.loadFromMemory("", 0) } -> std::same_as<bool>;
};

template<class T>
concept Openable = requires(T r)
{
        { r.openFromFile("") } -> std::same_as<bool>;
        { r.openFromMemory("", 0) } -> std::same_as<bool>;
};

template<class T>
concept Resource = Loadable<T> or Openable<T>;


/** Manager of given type of resources.
 */
template<Resource Type>
class Resources
{
        Resources() = delete;

public:

        static bool load(const std::string& id, const std::string& path)
        {
                return resources[id].loadFromFile(path);
        }

        static util::OptionalRef<Type> get(const std::string& id)
        {
                if (auto search = resources.find(id); search != resources.end())
                {
                        return std::ref(search->second);
                }
                return {};
        }

        static bool unload(const std::string& id)
        {
                return resources.erase(id);
        }

        static void unloadAll()
        {
                resources.clear();
        }

private:

        inline static util::MapStringTo<Type> resources;
};

}