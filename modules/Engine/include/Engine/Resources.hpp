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

template<typename T> constexpr bool is_resource =
        std::is_same_v<T, sf::Font> or
        std::is_same_v<T, sf::Texture>
;

class Resources
{
        Resources() = delete;

public:

        template<typename Resource>
        static bool load(const std::string& id, const std::string& path)
        {
                static_assert(is_resource<Resource>, typeNotResource);

                if constexpr (std::is_same_v<Resource, sf::Font>)
                {
                        return fonts[id].loadFromFile(path);
                }
                else if constexpr (std::is_same_v<Resource, sf::Texture>)
                {
                        return textures[id].loadFromFile(path);
                }
        }

        template<typename Resource>
        static Resource* get(const std::string& id)
        {
                static_assert(is_resource<Resource>, typeNotResource);

                if constexpr (std::is_same_v<Resource, sf::Font>)
                {
                        if (auto search = fonts.find(id); search != fonts.end())
                        {
                                return &search->second;
                        }
                        return static_cast<sf::Font*>(nullptr);
                }
                else if constexpr (std::is_same_v<Resource, sf::Texture>)
                {
                        if (auto search = textures.find(id); search != textures.end())
                        {
                                return &search->second;
                        }
                        return static_cast<sf::Texture*>(nullptr);
                }
        }

        template<typename Resource>
        static bool unload(const std::string& id)
        {
                static_assert(is_resource<Resource>, typeNotResource);

                if constexpr (std::is_same_v<Resource, sf::Font>)
                {
                        return fonts.erase(id);
                }
                else if constexpr (std::is_same_v<Resource, sf::Texture>)
                {
                        return textures.erase(id);
                }
        }

        template<typename Resource>
        static void unloadAll()
        {
                static_assert(is_resource<Resource>, typeNotResource);

                if constexpr (std::is_same_v<Resource, sf::Font>)
                {
                        fonts.clear();
                }
                else if constexpr (std::is_same_v<Resource, sf::Texture>)
                {
                        textures.clear();
                }
        }

private:

        inline static util::MapStringTo<sf::Font> fonts;
        inline static util::MapStringTo<sf::Texture> textures;
};

}