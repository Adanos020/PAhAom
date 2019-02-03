#pragma once


#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>
#include <type_traits>
#include <unordered_map>


namespace PAhAom
{

class Resources
{
        Resources() = delete;

public:

        template<typename Resource>
        static bool load(std::string_view id, const std::string& path)
        {
                static_assert(std::is_same<Resource, sf::Font>::value ||
                              std::is_same<Resource, sf::Texture>::value,
                              "Resource type is not recognised.");

                if constexpr (std::is_same<Resource, sf::Font>::value)
                {
                        return fonts[id].loadFromFile(path);
                }
                else if constexpr (std::is_same<Resource, sf::Texture>::value)
                {
                        return textures[id].loadFromFile(path);
                }
        }

        template<typename Resource>
        static auto get(std::string_view id)
        {
                static_assert(std::is_same<Resource, sf::Font>::value ||
                              std::is_same<Resource, sf::Texture>::value,
                              "Resource type is not recognised.");

                if constexpr (std::is_same<Resource, sf::Font>::value)
                {
                        if (auto search = fonts.find(id); search != fonts.end())
                        {
                                return &search->second;
                        }
                        return static_cast<sf::Font*>(nullptr);
                }
                else if constexpr (std::is_same<Resource, sf::Texture>::value)
                {
                        if (auto search = textures.find(id); search != textures.end())
                        {
                                return &search->second;
                        }
                        return static_cast<sf::Texture*>(nullptr);
                }
        }

        template<typename Resource>
        static bool unload(std::string_view id)
        {
                static_assert(std::is_same<Resource, sf::Font>::value ||
                              std::is_same<Resource, sf::Texture>::value,
                              "Resource type is not recognised.");

                if constexpr (std::is_same<Resource, sf::Font>::value)
                {
                        return fonts.erase(id);
                }
                else if constexpr (std::is_same<Resource, sf::Texture>::value)
                {
                        return textures.erase(id);
                }
        }

        template<typename Resource>
        static void unloadAll()
        {
                static_assert(std::is_same<Resource, sf::Font>::value ||
                              std::is_same<Resource, sf::Texture>::value,
                              "Resource type is not recognised.");

                if constexpr (std::is_same<Resource, sf::Font>::value)
                {
                        fonts.clear();
                }
                else if constexpr (std::is_same<Resource, sf::Texture>::value)
                {
                        textures.clear();
                }
        }

private:

        inline static std::unordered_map<std::string_view, sf::Font> fonts;
        inline static std::unordered_map<std::string_view, sf::Texture> textures;
};

}