#pragma once


#include <Engine/Resources.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Script/Script.hpp>
#include <Util/Types.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
#include <type_traits>
#include <unordered_map>


namespace util::script
{

/** Transforms a Lua table into an sf::Color object.
 * 
 *  Table syntax:
 *  - r: Number specifying the r component.
 *  - g: Number specifying the g component.
 *  - b: Number specifying the b component.
 *  - a: Number specifying the a component.
 */
inline auto tableToColor(const lua::Table& obj) -> sf::Color
{
        const lua::Value r = obj["r"];
        const lua::Value g = obj["g"];
        const lua::Value b = obj["b"];
        const lua::Value a = obj["a"];
        return {
                sf::Uint8(r.is<unsigned>() ? r : 0),
                sf::Uint8(g.is<unsigned>() ? g : 0),
                sf::Uint8(b.is<unsigned>() ? b : 0),
                sf::Uint8(a.is<unsigned>() ? a : 255),
        };
}

inline auto stringToColor(const std::string& obj) -> sf::Color
{
        static const util::MapStringTo<sf::Color> predefinedColors = {
                { "black",       sf::Color::Black       },
                { "white",       sf::Color::White       },
                { "red",         sf::Color::Red         },
                { "green",       sf::Color::Green       },
                { "blue",        sf::Color::Blue        },
                { "yellow",      sf::Color::Yellow      },
                { "magenta",     sf::Color::Magenta     },
                { "cyan",        sf::Color::Cyan        },
                { "transparent", sf::Color::Transparent },
        };

        if (auto c = predefinedColors.find(obj); c != predefinedColors.end())
        {
                return c->second;
        }

        std::cerr << util::err::badColorName(obj) << std::endl;
        return sf::Color::Transparent;
}

/** Transforms a Lua table into an sf::Vector2<T> object.
 * 
 *  Table syntax:
 *  - x: Number specifying the x coordinate.
 *  - y: Number specifying the y coordinate.
 */
template<typename T = float>
inline auto tableToVector(const lua::Table& obj) -> sf::Vector2<T>
{
        const lua::Value x = obj["x"];
        const lua::Value y = obj["y"];
        return {
                T(x.is<T>() ? x : 0),
                T(y.is<T>() ? y : 0),
        };
}

/** Transforms a Lua table into an sf::Rect<T> object.
 * 
 *  Table syntax:
 *  - left:   Number specifying the x coordinate of the top-left corner.
 *  - top:    Number specifying the y coordinate of the top-left corner.
 *  - width:  Number specifying the rectangle's width.
 *  - height: Number specifying the rectangle's height.
 */
template<typename T = float>
inline auto tableToRectangle(const lua::Table& obj) -> sf::Rect<T>
{
        const lua::Value lft = obj["left"];
        const lua::Value top = obj["top"];
        const lua::Value wdh = obj["width"];
        const lua::Value hgt = obj["height"];
        return {
                T(lft.is<T>() ? lft : 0),
                T(top.is<T>() ? top : 0),
                T(wdh.is<T>() ? wdh : 0),
                T(hgt.is<T>() ? hgt : 0),
        };
}

template<typename T>
inline auto extractBounds(lua::Table& obj, const std::unique_ptr<T>& drawable) -> void
{
        static_assert(std::is_base_of_v<sf::Drawable, T>);

        const sf::FloatRect globalBounds = drawable->getGlobalBounds();
        obj["globalBounds"] = lua::Table::records(luaContext,
                "left",   globalBounds.left,
                "top",    globalBounds.top,
                "width",  globalBounds.width,
                "height", globalBounds.height
        );

        const sf::FloatRect localBounds = drawable->getLocalBounds();
        obj["localBounds"] = lua::Table::records(luaContext,
                "left",   localBounds.left,
                "top",    localBounds.top,
                "width",  localBounds.width,
                "height", localBounds.height
        );
}


// Shorthand for checking table properties.
#define prop(x, CppType) if (lua::Value x = obj[#x]; x.is<CppType>())


/** Transforms a Lua table into an sf::CircleShape object.
 * 
 *  Table syntax:
 *  - radius:     Number representing radius of the circle.
 *  - pointCount: Number representing number of vertices around the center.
 *  - all properties from Shape
 */
inline auto tableToCircleShape(lua::Table& obj) -> std::unique_ptr<sf::CircleShape>
{
        auto circleShape = std::make_unique<sf::CircleShape>();

        prop (radius, float)
        {
                circleShape->setRadius(radius);
        }
        prop (pointCount, unsigned)
        {
                circleShape->setPointCount(unsigned(pointCount));
        }

        return circleShape;
}

/** Transforms a Lua table into an sf::ConvexShape object.
 * 
 *  Table syntax:
 *  - points: Table of vectors representing positions of all vertices.
 *  - all properties from Shape
 */
inline auto tableToConvexShape(lua::Table& obj) -> std::unique_ptr<sf::ConvexShape>
{
        auto convShape = std::make_unique<sf::ConvexShape>();

        prop (points, lua::Table)
        {
                lua::Table pts = points;
                convShape->setPointCount(int(pts.len()));
                pts.iterate([&](lua::Valref i, lua::Valref pos) {
                        convShape->setPoint(int(i) - 1, tableToVector(pos));
                });
        }

        return convShape;
}

/** Transforms a Lua table into an sf::RectangleShape object.
 * 
 *  Table syntax:
 *  - size: Vector representing size of the rectangle.
 *  - all properties from Shape
 */
inline auto tableToRectangleShape(lua::Table& obj) -> std::unique_ptr<sf::RectangleShape>
{
        auto rectShape = std::make_unique<sf::RectangleShape>();

        prop (size, lua::Table)
        {
                rectShape->setSize(tableToVector(size));
        }

        return rectShape;
}

/** Transforms a Lua table into an sf::Shape object.
 * 
 *  Table syntax:
 *  - texture:          String containting the id of the texture.
 *  - textureRect:      Rectangle representing the area of the texture to be displayed.
 *  - fillColor:        Color of the font.
 *  - outlineColor:     Color of the text outline.
 *  - outlineThickness: Number representing width of the text outline.
 */
inline auto tableToShape(lua::Table& obj) -> std::unique_ptr<sf::Shape>
{
        std::unique_ptr<sf::Shape> shape { nullptr };
        const lua::Value type = obj["type"];

        if (type == "sfCircleShape")
        {
                shape = tableToCircleShape(obj);
        }
        else if (type == "sfConvexShape")
        {
                shape = tableToConvexShape(obj);
        }
        else if (type == "sfRectangleShape")
        {
                shape = tableToRectangleShape(obj);
        }

        prop (texture, std::string)
        {
                if (auto tex = engine::Resources::get<sf::Texture>(texture))
                {
                        shape->setTexture(tex);
                }
                else
                {
                        std::cerr << std::endl;
                }
        }
        prop (textureRect, lua::Table)
        {
                shape->setTextureRect(tableToRectangle<int>(textureRect));
        }
        prop (fillColor, std::string)
        {
                shape->setFillColor(stringToColor(fillColor));
        }
        prop (fillColor, lua::Table)
        {
                shape->setFillColor(tableToColor(fillColor));
        }
        prop (outlineColor, std::string)
        {
                shape->setOutlineColor(stringToColor(outlineColor));
        }
        prop (outlineColor, lua::Table)
        {
                shape->setOutlineColor(tableToColor(outlineColor));
        }
        prop (outlineThickness, float)
        {
                shape->setOutlineThickness(outlineThickness);
        }

        extractBounds(obj, shape);

        return shape;
}

/** Transforms a Lua table into an sf::Sprite object.
 * 
 *  Table syntax:
 *  - texture:     String containting the id of the texture.
 *  - textureRect: Rectangle representing the area of the texture to be displayed.
 *  - color:       Color of the font.
 */
inline auto tableToSprite(lua::Table& obj) -> std::unique_ptr<sf::Sprite>
{
        auto sprite = std::make_unique<sf::Sprite>();

        prop (texture, std::string)
        {
                if (auto tex = engine::Resources::get<sf::Texture>(texture))
                {
                        sprite->setTexture(*tex);
                }
                else
                {
                        std::cerr << std::endl;
                }
        }
        prop (textureRect, lua::Table)
        {
                sprite->setTextureRect(tableToRectangle<int>(textureRect));
        }
        prop (color, std::string)
        {
                sprite->setColor(stringToColor(color));
        }

        extractBounds(obj, sprite);

        return sprite;
}

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
inline auto tableToText(lua::Table& obj) -> std::unique_ptr<sf::Text>
{
        static const util::MapStringTo<sf::Text::Style> styles = {
                { "regular",       sf::Text::Regular       },
                { "bold",          sf::Text::Bold          },
                { "italic",        sf::Text::Italic        },
                { "underlined",    sf::Text::Underlined    },
                { "strikethrough", sf::Text::StrikeThrough },
        };
        
        auto text = std::make_unique<sf::Text>();

        const auto getStyle = [&](const std::string& style) -> sf::Text::Style
        {
                if (auto s = styles.find(style); s != styles.end())
                {
                        return s->second;
                }
                else
                {
                        std::cerr << util::err::badTextStyleName(style) << std::endl;
                        return sf::Text::Style::Regular;
                }
        };
        
        prop (content, std::string)
        {
                text->setString(std::string(content));
        }
        prop (font, std::string)
        {
                if (auto fptr = engine::Resources::get<sf::Font>(font))
                {
                        text->setFont(*fptr);
                }
                else
                {
                        std::cerr << util::err::badFontName(font) << std::endl;
                }
        }
        prop (characterSize, unsigned)
        {
                text->setCharacterSize(characterSize);
        }
        prop (lineSpacing, float)
        {
                text->setLineSpacing(lineSpacing);
        }
        prop (letterSpacing, float)
        {
                text->setLetterSpacing(letterSpacing);
        }
        prop (style, std::string)
        {
                text->setStyle(getStyle(style));
        }
        prop (style, lua::Table)
        {
                int compound = sf::Text::Style::Regular;
                static_cast<lua::Table>(style).iterate(
                        [&](lua::Valref, lua::Valref s) { compound |= getStyle(s); });
                text->setStyle(compound);
        }
        prop (fillColor, std::string)
        {
                text->setFillColor(stringToColor(fillColor));
        }
        prop (fillColor, lua::Table)
        {
                text->setFillColor(tableToColor(fillColor));
        }
        prop (outlineColor, std::string)
        {
                text->setOutlineColor(stringToColor(outlineColor));
        }
        prop (outlineColor, lua::Table)
        {
                text->setOutlineColor(tableToColor(outlineColor));
        }
        prop (outlineThickness, float)
        {
                text->setOutlineThickness(outlineThickness);
        }

        extractBounds(obj, text);
        
        return text;
}

/** Transforms a Lua table into a sf::Drawable object.
 * 
 *  Table syntax for all sf::Drawable objects:
 *  - type:     String representing drawable type ID (full list of IDs below).
 *  - position: Vector representing the world coordinates of the sf::Text object.
 *  - rotation: Number representing the angle (in degrees) by which the object is rotated.
 *  - scale:    Vector representing the factors by which the object should be scaled.
 *  - origin:   Vector representing the coordinates of the object's reference frame's origin,
 *              or a string choosing one of the predefined anchors (top, bottom, left, right,
 *              center, top-left, top-right, bottom-left, bottom-right)
 * 
 *  Drawable type IDs:
 *  - sfText: sf::Text
 * 
 *  Special property type definitions:
 *  - Vector: Table containing "x" and "y" entries.
 *  - Color:  String representing the color name; or Table containing "r", "g", "b", and "a"
 *            entries.
 */
inline auto tableToDrawable(lua::Table& obj) -> std::unique_ptr<sf::Drawable>
{
        const lua::Value type = obj["type"];

        if (not type)
        {
                std::cerr << util::err::noDrawableTypeId() << std::endl;
                return nullptr;
        }

        std::unique_ptr<sf::Drawable> drawable{ nullptr };

        if (type == "sfText")
        {
                drawable = tableToText(obj);
        }
        else if (type == "sfSprite")
        {
                drawable = tableToSprite(obj);
        }
        else if (type == "sfCircleShape" ||
                 type == "sfConvexShape" ||
                 type == "sfRectangleShape")
        {
                drawable = tableToShape(obj);
        }
        else
        {
                return nullptr;
        }

        auto transformable = dynamic_cast<sf::Transformable*>(drawable.get());
        prop (position, lua::Table)
        {
                transformable->setPosition(tableToVector(position));
        }
        prop (rotation, float)
        {
                transformable->setRotation(rotation);
        }
        prop (scale, lua::Table)
        {
                transformable->setScale(tableToVector(scale));
        }
        prop (origin, std::string)
        {
                prop (globalBounds, lua::Table)
                {
                        sf::FloatRect bounds = tableToRectangle(globalBounds);
                        transformable->setOrigin(
                                origin == "center"       ? sf::Vector2f(bounds.width / 2, bounds.height / 2) :
                                origin == "top"          ? sf::Vector2f(bounds.width / 2, 0.f              ) :
                                origin == "left"         ? sf::Vector2f(0.f,              bounds.height / 2) :
                                origin == "bottom"       ? sf::Vector2f(bounds.width / 2, bounds.height    ) :
                                origin == "right"        ? sf::Vector2f(bounds.width,     bounds.height / 2) :
                                origin == "bottom-left"  ? sf::Vector2f(0.f,              bounds.height    ) :
                                origin == "top-right"    ? sf::Vector2f(bounds.width,     0.f              ) :
                                origin == "bottom-right" ? sf::Vector2f(bounds.width,     bounds.height    ) :
                                /* origin == "top-left" */ sf::Vector2f(0.f,              0.f              )
                        );
                }
        }
        prop (origin, lua::Table)
        {
                transformable->setOrigin(tableToVector(origin));
        }

        return drawable;
}

#undef prop

}