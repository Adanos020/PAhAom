#pragma once


#include <Engine/Resources.hpp>

#include <selene.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <iostream>
#include <memory>
#include <unordered_map>


namespace util
{

class Lua
{
        Lua() = delete;

public: // Basic functions.

        static void load(const std::string& path)
        {
                state.Load(path);
        }

        static bool runCode(const std::string& code)
        {
                return state(code.c_str());
        }

        static void setVariable(const std::string& varName, const std::string& value)
        {
                runCode(varName + "=" + value);
        }

        static sel::Selector getVariable(const std::string& varName)
        {
                return state[varName.c_str()];
        }

        static bool hasType(sel::Selector& obj, const std::string& type)
        {
                // std::cout << type << "\t" << static_cast<std::string>(state["type"](obj)) << std::endl;
                return obj.exists() and state["type"](obj) == type;
        }

public: // Graphics-related.

        /** Transforms a Lua table into an sf::Color object.
         * 
         *  Table syntax:
         *  - r: Number specifying the r component.
         *  - g: Number specifying the g component.
         *  - b: Number specifying the b component.
         *  - a: Number specifying the a component.
         */
        static sf::Color tableToColor(const sel::Selector& obj)
        {
                auto r = obj["r"];
                auto g = obj["g"];
                auto b = obj["b"];
                auto a = obj["a"];
                return {
                        hasType(r, "number") ? r : sf::Uint8(0),
                        hasType(g, "number") ? g : sf::Uint8(0),
                        hasType(b, "number") ? b : sf::Uint8(0),
                        hasType(a, "number") ? a : sf::Uint8(255),
                };
        }

        static sf::Color stringToColor(const sel::Selector& obj)
        {
                static const std::unordered_map<std::string, sf::Color> predefinedColors = {
                        { "black",       sf::Color::Black },
                        { "white",       sf::Color::White },
                        { "red",         sf::Color::Red },
                        { "green",       sf::Color::Green },
                        { "blue",        sf::Color::Blue },
                        { "yellow",      sf::Color::Yellow },
                        { "magenta",     sf::Color::Magenta },
                        { "cyan",        sf::Color::Cyan },
                        { "transparent", sf::Color::Transparent },
                };

                if (auto c = predefinedColors.find(obj); c != predefinedColors.end())
                {
                        return c->second;
                }

                const std::string cname = obj;
                std::cerr << "Error: color name '" << cname << "' was not recognized." << std::endl;

                return sf::Color::Transparent;
        }

        /** Transforms a Lua table into an sf::Vector2f object.
         * 
         *  Table syntax:
         *  - x: Number specifying the x coordinate.
         *  - y: Number specifying the y coordinate.
         */
        static sf::Vector2f tableToVector(const sel::Selector& obj)
        {
                auto x = obj["x"];
                auto y = obj["y"];
                return {
                        hasType(x, "number") ? x : 0.f,
                        hasType(y, "number") ? y : 0.f,
                };
        }

#define prop(x, type) if (auto x = obj[#x]; hasType(x, #type))

        /** Transforms a Lua table into an sf::Text object.
         * 
         *  Table syntax:
         *  - content:          String containing the string content of the sf::Text object.
         *  - font:             String containing the id of the font.
         *  - characterSize:    Number specifying the text's font size.
         *  - lineSpacing:      Number specifying the size of the space between lines.
         *  - letterSpacing:    Number specifying the size of the space between letters.
         *  - style:            String or table of strings representing the text style. Full
         *                      styles list below.
         *  - fillColor:        Color of the font.
         *  - outlineColor:     Color of the text outline.
         *  - outlineThickness: Number representing width of the text outline.
         * 
         *  Styles list:
         *  - regular
         *  - bold
         *  - italic
         *  - underlined
         *  - strikethrough
         */
        static std::unique_ptr<sf::Text> tableToText(const sel::Selector& obj)
        {
                static const std::unordered_map<std::string, sf::Text::Style> styles = {
                        { "regular",       sf::Text::Regular       },
                        { "bold",          sf::Text::Bold          },
                        { "italic",        sf::Text::Italic        },
                        { "underlined",    sf::Text::Underlined    },
                        { "strikethrough", sf::Text::StrikeThrough },
                };
                
                auto text = new sf::Text;

                const auto setStyle = [&](const sel::Selector& style)
                {
                        if (auto s = styles.find(style); s != styles.end())
                        {
                                text->setStyle(s->second);
                        }
                        else
                        {
                                const std::string sname = style;
                                std::cerr << "Error: style'" << sname << "' was not recognized." << std::endl;
                        }
                };
                
                prop (content, string)
                {
                        text->setString(content);
                }
                prop (font, string)
                {
                        if (auto fptr = engine::Resources::get<sf::Font>(font))
                        {
                                text->setFont(*fptr);
                        }
                        else
                        {
                                const std::string fname = font;
                                std::cerr << "Error: font '" << fname << "' was not found." << std::endl;
                        }
                }
                prop (characterSize, number)
                {
                        text->setCharacterSize(characterSize);
                }
                prop (lineSpacing, number)
                {
                        text->setLineSpacing(lineSpacing);
                }
                prop (letterSpacing, number)
                {
                        text->setLetterSpacing(letterSpacing);
                }
                prop (style, string)
                {
                        setStyle(style);
                }
                prop (style, table)
                {
                        state["temp"] = style;
                        for (size_t i = 1, nStyles = state["#temp"]; i < nStyles; ++i)
                        {
                                setStyle(style[i]);
                        }
                }
                prop (fillColor, string)
                {
                        text->setFillColor(stringToColor(fillColor));
                }
                prop (fillColor, table)
                {
                        text->setFillColor(tableToColor(fillColor));
                }
                prop (outlineColor, string)
                {
                        text->setOutlineColor(stringToColor(outlineColor));
                }
                prop (outlineColor, table)
                {
                        text->setOutlineColor(tableToColor(outlineColor));
                }
                prop (outlineThickness, number)
                {
                        text->setOutlineThickness(outlineThickness);
                }
                
                return std::unique_ptr<sf::Text>(text);
        }

        /** Transforms a Lua table into a sf::Drawable object.
         * 
         *  Table syntax for all sf::Drawable objects:
         *  - type:     String representing drawable type ID (full list of IDs below).
         *  - position: Vector representing the world coordinates of the sf::Text object.
         *  - rotation: Number representing the angle (in degrees) by which the object
         *              is rotated.
         *  - scale:    Vector representing the factors by which the object should be scaled.
         *  - origin:   Vector representing the coordinates of the object's reference frame's origin.
         * 
         *  Drawable type IDs:
         *  - sfText: sf::Text
         * 
         *  Special property type definitions:
         *  - Vector: Table containing "x" and "y" entries.
         *  - Color:  String representing the color name; or Table containing "r", "g", "b", and "a"
         *            entries.
         */
        static std::unique_ptr<sf::Drawable> tableToDrawable(const sel::Selector& obj)
        {
                if (!obj["type"].exists())
                {
                        std::cerr << "Error: drawable type ID was not specified." << std::endl;
                        return nullptr;
                }

                std::unique_ptr<sf::Drawable> drawable{ nullptr };

#define get(luatype, retfun) if (obj["type"] == #luatype) drawable = retfun(obj)

                get(sfText, tableToText);

#undef get

                auto transformable = dynamic_cast<sf::Transformable*>(drawable.get());
                prop (position, table)
                {
                        transformable->setPosition(tableToVector(position));
                }
                prop (rotation, number)
                {
                        transformable->setRotation(rotation);
                }
                prop (scale, table)
                {
                        transformable->setScale(tableToVector(scale));
                }
                prop (origin, table)
                {
                        transformable->setOrigin(tableToVector(origin));
                }

                return drawable;
        }

#undef prop

private:

        inline static sel::State state{ true };
};

class LuaVariable
{
public:

        LuaVariable(const std::string& name, const std::string& value)
        : name(name)
        {
                Lua::setVariable(this->name, value);
        }

        ~LuaVariable()
        {
                Lua::setVariable(this->name, "nil");
        }

        sel::Selector get() const
        {
                return Lua::getVariable(this->name);
        }

private:

        const std::string name;
};

}