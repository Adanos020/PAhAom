#pragma once


#include <Engine/Graphics/SquareTileMap.hpp>
#include <Engine/Resources.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Script/Script.hpp>
#include <Util/Types.hpp>

#include <SFML/Graphics.hpp>

#include <memory>
#include <type_traits>
#include <unordered_map>


namespace util::script
{

inline sf::Color stringToColor(const std::string& obj)
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

        luaContext.error(util::err::badColorName(obj));
        return sf::Color::Transparent;
}

/** Transforms a Lua table into an sf::Color object.
 * 
 *  Table syntax:
 *  - r: Number specifying the r component.
 *  - g: Number specifying the g component.
 *  - b: Number specifying the b component.
 *  - a: Number specifying the a component.
 */
inline sf::Color tableToColor(const lua::Table& obj)
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

/** Transforms a Lua table into an sf::Vector2<T> object.
 * 
 *  Table syntax:
 *  - x: Number specifying the x coordinate.
 *  - y: Number specifying the y coordinate.
 */
template<typename T = float>
inline sf::Vector2<T> tableToVector(const lua::Table& obj)
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
inline sf::Rect<T> tableToRectangle(const lua::Table& obj)
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
inline void extractBounds(lua::Table& obj, const std::unique_ptr<T>& drawable)
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
inline std::unique_ptr<sf::CircleShape> tableToCircleShape(lua::Table& obj)
{
        auto circleShape = std::make_unique<sf::CircleShape>();

        prop (radius, float)
        {
                circleShape->setRadius(radius);
        }
        prop (pointCount, unsigned)
        {
                circleShape->setPointCount(pointCount.to<unsigned>());
        }

        return circleShape;
}

/** Transforms a Lua table into an sf::ConvexShape object.
 * 
 *  Table syntax:
 *  - points: Table of vectors representing positions of all vertices.
 *  - all properties from Shape
 */
inline std::unique_ptr<sf::ConvexShape> tableToConvexShape(lua::Table& obj)
{
        auto convShape = std::make_unique<sf::ConvexShape>();

        prop (points, lua::Table)
        {
                lua::Table pts = points;
                convShape->setPointCount(pts.len().to<unsigned>());
                pts.iterate([&](lua::Valref i, lua::Valref pos) {
                        convShape->setPoint(i.to<unsigned>() - 1, tableToVector(pos));
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
inline std::unique_ptr<sf::RectangleShape> tableToRectangleShape(lua::Table& obj)
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
inline std::unique_ptr<sf::Shape> tableToShape(lua::Table& obj)
{
        std::unique_ptr<sf::Shape> shape { nullptr };
        const lua::Value type = obj["type"];

        if (type == "circle shape")
        {
                shape = tableToCircleShape(obj);
        }
        else if (type == "convex shape")
        {
                shape = tableToConvexShape(obj);
        }
        else if (type == "rectangle shape")
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
                        luaContext.error(util::err::badTextureName(texture));
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
inline std::unique_ptr<sf::Sprite> tableToSprite(lua::Table& obj)
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
                        luaContext.error(util::err::badTextureName(texture));
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
inline std::unique_ptr<sf::Text> tableToText(lua::Table& obj)
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
                        luaContext.error(util::err::badTextStyleName(style));
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
                        luaContext.error(util::err::badFontName(font));
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
 *  - scale:    Vector representing the factors or a single number also representing the factor
 *              by which the object should be scaled.
 *  - origin:   Vector representing the coordinates of the object's reference frame's origin,
 *              or a string choosing one of the predefined anchors (top, bottom, left, right,
 *              center, top-left, top-right, bottom-left, bottom-right)
 * 
 *  Drawable type IDs:
 *  - circle shape (sf::CircleShape)
 *  - convex shape (sf::ConvexShape)
 *  - rectangle shape (sf::RectangleShape)
 *  - sprite (sf::Sprite)
 *  - square tile map (SquareTileMap)
 *  - text (sf::Text)
 */
inline std::unique_ptr<sf::Drawable> tableToDrawable(lua::Table& obj)
{
        const lua::Value type = obj["type"];

        if (not type)
        {
                luaContext.error(util::err::noDrawableTypeId());
                return nullptr;
        }

        std::unique_ptr<sf::Drawable> drawable{ nullptr };

        if (type == "text")
        {
                drawable = tableToText(obj);
        }
        else if (type == "sprite")
        {
                drawable = tableToSprite(obj);
        }
        else if (type == "circle shape" ||
                 type == "convex shape" ||
                 type == "rectangle shape")
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
        prop (scale, float)
        {
                transformable->setScale(scale, scale);
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