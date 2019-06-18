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

template<class T> constexpr bool isResource =
        std::is_same_v<T, sf::Font> or
        std::is_same_v<T, sf::Texture>
;

template<class ResourceType>
class Resources
{
        static_assert(isResource<ResourceType>, typeNotResource);
        Resources() = delete;

public:

        static bool load(const std::string& id, const std::string& path)
        {
                return resources[id].loadFromFile(path);
        }

        static util::OptionalRef<ResourceType> get(const std::string& id)
        {
                if (auto search = resources.find(id); search != resources.end())
                {
                        return search->second;
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

        inline static util::MapStringTo<ResourceType> resources;
};

}