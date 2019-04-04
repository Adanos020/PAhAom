#pragma once


#include <Engine/Resources.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Script.hpp>
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
                sf::Uint8(r.type() == lua::ValueType::Number ? r : 0),
                sf::Uint8(g.type() == lua::ValueType::Number ? g : 0),
                sf::Uint8(b.type() == lua::ValueType::Number ? b : 0),
                sf::Uint8(a.type() == lua::ValueType::Number ? a : 255),
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
                T(x.type() == lua::ValueType::Number ? x : 0),
                T(y.type() == lua::ValueType::Number ? y : 0),
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
        const lua::Value left   = obj["left"];
        const lua::Value top    = obj["top"];
        const lua::Value width  = obj["width"];
        const lua::Value height = obj["height"];
        return {
                T(left.type()   == lua::ValueType::Number ? left   : 0),
                T(top.type()    == lua::ValueType::Number ? top    : 0),
                T(width.type()  == lua::ValueType::Number ? width  : 0),
                T(height.type() == lua::ValueType::Number ? height : 0),
        };
}

template<typename T>
inline auto extractBounds(lua::Table& obj, T* drawable) -> void
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
#define prop(x, luatype)\
        if (lua::Value x = obj[#x]; x.type() == lua::ValueType::luatype)


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

        prop (radius, Number)
        {
                circleShape->setRadius(radius);
        }
        prop (pointCount, Number)
        {
                circleShape->setPointCount(int(pointCount));
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

        prop (points, Table)
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

        prop (size, Table)
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

#define get(type, retfun) if (obj["type"] == #type) shape = retfun(obj)

        get(sfCircleShape, tableToCircleShape); else
        get(sfConvexShape, tableToConvexShape); else
        get(sfRectangleShape, tableToRectangleShape);

#undef get

        if (not shape) return shape;

        prop (texture, String)
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
        prop (textureRect, Table)
        {
                shape->setTextureRect(tableToRectangle<int>(textureRect));
        }
        prop (fillColor, String)
        {
                shape->setFillColor(stringToColor(fillColor));
        }
        prop (fillColor, Table)
        {
                shape->setFillColor(tableToColor(fillColor));
        }
        prop (outlineColor, String)
        {
                shape->setOutlineColor(stringToColor(outlineColor));
        }
        prop (outlineColor, Table)
        {
                shape->setOutlineColor(tableToColor(outlineColor));
        }
        prop (outlineThickness, Number)
        {
                shape->setOutlineThickness(outlineThickness);
        }

        extractBounds(obj, shape.get());

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

        prop (texture, String)
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
        prop (textureRect, Table)
        {
                sprite->setTextureRect(tableToRectangle<int>(textureRect));
        }
        prop (color, String)
        {
                sprite->setColor(stringToColor(color));
        }

        extractBounds(obj, sprite.get());

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

        const auto getStyle = [&](const std::string& style)
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
        
        prop (content, String)
        {
                text->setString(std::string(content));
        }
        prop (font, String)
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
        prop (characterSize, Number)
        {
                text->setCharacterSize(characterSize);
        }
        prop (lineSpacing, Number)
        {
                text->setLineSpacing(lineSpacing);
        }
        prop (letterSpacing, Number)
        {
                text->setLetterSpacing(letterSpacing);
        }
        prop (style, String)
        {
                text->setStyle(getStyle(style));
        }
        prop (style, Table)
        {
                int compound = sf::Text::Style::Regular;
                static_cast<lua::Table>(style).iterate(
                        [&](lua::Valref, lua::Valref s) { compound |= getStyle(s); });
                text->setStyle(compound);
        }
        prop (fillColor, String)
        {
                text->setFillColor(stringToColor(fillColor));
        }
        prop (fillColor, Table)
        {
                text->setFillColor(tableToColor(fillColor));
        }
        prop (outlineColor, String)
        {
                text->setOutlineColor(stringToColor(outlineColor));
        }
        prop (outlineColor, Table)
        {
                text->setOutlineColor(tableToColor(outlineColor));
        }
        prop (outlineThickness, Number)
        {
                text->setOutlineThickness(outlineThickness);
        }

        extractBounds(obj, text.get());
        
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
        if (not obj["type"])
        {
                std::cerr << util::err::noDrawableTypeId() << std::endl;
                return nullptr;
        }

        std::unique_ptr<sf::Drawable> drawable{ nullptr };

#define get(type, retfun) if (obj["type"] == #type) drawable = retfun(obj)

        get(sfText, tableToText);         else
        get(sfCircleShape, tableToShape); else
        get(sfConvexShape, tableToShape); else
        get(sfRectangleShape, tableToShape);

#undef get

        if (not drawable) return drawable;

        auto transformable = dynamic_cast<sf::Transformable*>(drawable.get());
        prop (position, Table)
        {
                transformable->setPosition(tableToVector(position));
        }
        prop (rotation, Number)
        {
                transformable->setRotation(rotation);
        }
        prop (scale, Table)
        {
                transformable->setScale(tableToVector(scale));
        }
        prop (origin, String)
        {
                prop (globalBounds, Table)
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
        prop (origin, Table)
        {
                transformable->setOrigin(tableToVector(origin));
        }

        return drawable;
}

#undef prop

}