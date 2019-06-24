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

template<class T>
concept Resource =
        std::is_same_v<T, sf::Font> or
        std::is_same_v<T, sf::Texture>;

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