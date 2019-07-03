#pragma once


#include <Engine/Resources.hpp>

#include <Script/Lua.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Graphics.hpp>
#include <Util/Types.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>

#include <cstdint>
#include <iostream>
#include <memory>
#include <type_traits>
#include <unordered_map>


namespace script
{

// Externals

inline static sol::table rgba(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a)
{
        return lua.create_table_with("r", r, "g", g, "b", b, "a", a);
}

inline static sol::table rgb(std::uint32_t r, std::uint32_t g, std::uint32_t b)
{
        return lua.create_table_with("r", r, "g", g, "b", b);
}

inline static void loadGraphics()
{
        lua["rgba"] = rgba;
        lua["rgb"]  = rgb;
}

// Internals

inline static sf::Color stringToColor(const std::string& str)
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

        if (auto c = predefinedColors.find(str); c != predefinedColors.end())
        {
                return c->second;
        }

        std::cerr << util::err::badColorName(str) << std::endl;
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
inline sf::Color tableToColor(sol::table obj)
{
        return {
                static_cast<sf::Uint8>(obj.get_or("r", 0u)),
                static_cast<sf::Uint8>(obj.get_or("g", 0u)),
                static_cast<sf::Uint8>(obj.get_or("b", 0u)),
                static_cast<sf::Uint8>(obj.get_or("a", 255u)),
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
template<util::Arithmetic T = float>
inline sf::Rect<T> tableToRectangle(sol::table obj)
{
        return {
                obj.get_or("left"  , T{0}),
                obj.get_or("top"   , T{0}),
                obj.get_or("width" , T{0}),
                obj.get_or("height", T{0}),
        };
}

/** Table of tables of numbers, where all inner tables must have equal lengths.
 */
template<util::Arithmetic T = float>
inline util::Matrix<T> tableToMatrix(sol::table obj)
{
        util::Matrix<T> mat;
        mat.resize(obj.size());

        obj.for_each([&](sol::object i, sol::object row) {
                if (not row.is<sol::table>())
                {
                        std::cerr << util::err::notATable << std::endl;
                }
                row.as<sol::table>().for_each([&](sol::object, sol::object entry) {
                        if (entry.get_type() != sol::type::number)
                        {
                                std::cerr << util::err::notANumber << std::endl;
                        }
                        mat[(i.as<std::int32_t>() - 1)].push_back(
                                static_cast<T>(entry.as<float>()));
                });
        });

        // All columns must have equal numbers of rows.
        if (std::any_of(mat.begin(), mat.end(), [&](auto& row)
                { return row.size() != mat[0].size(); }))
        {
                std::cerr << util::err::matrixNotRegular << std::endl;
        }

        return mat;
}

template<util::Graphical T>
inline void extractLocalBounds(const std::unique_ptr<T>& dobj, sol::table obj)
{
        const sf::FloatRect bounds = dobj->getLocalBounds();
        obj["localBounds"] = lua.create_table_with(
                "left",   bounds.left,
                "top",    bounds.top,
                "width",  bounds.width,
                "height", bounds.height);
}

template<util::Graphical T>
inline void extractGlobalBounds(const std::unique_ptr<T>& dobj, sol::table obj)
{
        const sf::FloatRect bounds = dobj->getGlobalBounds();
        obj["globalBounds"] = lua.create_table_with(
                "left",   bounds.left,
                "top",    bounds.top,
                "width",  bounds.width,
                "height", bounds.height);
}


// Shorthand for checking table properties.
#define prop(X, CPP_TYPE) (sol::object X = obj[#X]; X.is<CPP_TYPE>())

template<util::Transformable T>
inline std::unique_ptr<T>& updateTransformFromTable(std::unique_ptr<T>& dobj, sol::table obj)
{
        extractLocalBounds(dobj, obj);

        auto tobj = static_cast<sf::Transformable*>(dobj.get());
        if prop (position, sol::table)
        {
                tobj->setPosition(util::Vector{position});
        }

        if prop (rotation, float)
        {
                tobj->setRotation(rotation.as<float>());
        }

        if prop (scale, sol::table)
        {
                tobj->setScale(util::Vector{scale});
        }
        else if prop (scale, float)
        {
                const auto s = scale.as<float>();
                tobj->setScale(s, s);
        }

        if prop (origin, std::string)
        {
                if prop (localBounds, sol::table)
                {
                        const auto o = origin.as<std::string>();
                        const sf::FloatRect bounds = tableToRectangle(localBounds);
                        tobj->setOrigin(
                                o == "center"       ? sf::Vector2f{bounds.width / 2, bounds.height / 2} :
                                o == "top"          ? sf::Vector2f{bounds.width / 2, 0.f              } :
                                o == "left"         ? sf::Vector2f{0.f,              bounds.height / 2} :
                                o == "bottom"       ? sf::Vector2f{bounds.width / 2, bounds.height    } :
                                o == "right"        ? sf::Vector2f{bounds.width,     bounds.height / 2} :
                                o == "bottom-left"  ? sf::Vector2f{0.f,              bounds.height    } :
                                o == "top-right"    ? sf::Vector2f{bounds.width,     0.f              } :
                                o == "bottom-right" ? sf::Vector2f{bounds.width,     bounds.height    } :
                                /* o == "top-left" */ sf::Vector2f{0.f,              0.f              });
                }
        }
        else if prop (origin, sol::table)
        {
                tobj->setOrigin(util::Vector{origin});
        }

        extractGlobalBounds(dobj, obj);
        return dobj;
}

/** Transforms a Lua table into an ShapeClass object.
 * 
 *  Table syntax:
 *  - texture:          String containting the id of the texture.
 *  - textureRect:      Rectangle representing the area of the texture to be displayed.
 *  - fillColor:        Color of the font.
 *  - outlineColor:     Color of the text outline.
 *  - outlineThickness: Number representing width of the text outline.
 */
template<class ShapeClass>
inline std::unique_ptr<ShapeClass>& updateShapeFromTable(
        std::unique_ptr<ShapeClass>& shape, sol::table obj)
{
        static_assert(
                std::is_same_v<ShapeClass, sf::CircleShape> or
                std::is_same_v<ShapeClass, sf::ConvexShape> or
                std::is_same_v<ShapeClass, sf::RectangleShape>);

        if prop (texture, std::string)
        {
                if (auto tex = engine::Resources<sf::Texture>::get(texture.as<std::string>()))
                {
                        shape->setTexture(&tex->get());
                }
                else
                {
                        std::cerr << util::err::badTextureName(texture.as<std::string>()) << std::endl;
                }
        }

        if prop (textureRect, sol::table)
        {
                shape->setTextureRect(tableToRectangle<std::int32_t>(textureRect));
        }

        if prop (fillColor, std::string)
        {
                shape->setFillColor(stringToColor(fillColor.as<std::string>()));
        }
        else if prop (fillColor, sol::table)
        {
                shape->setFillColor(tableToColor(fillColor));
        }

        if prop (outlineColor, std::string)
        {
                shape->setOutlineColor(stringToColor(outlineColor.as<std::string>()));
        }
        else if prop (outlineColor, sol::table)
        {
                shape->setOutlineColor(tableToColor(outlineColor));
        }

        if prop (outlineThickness, float)
        {
                shape->setOutlineThickness(outlineThickness.as<float>());
        }

        updateTransformFromTable(shape, obj);
        return shape;
}

/** Transforms a Lua table into an sf::CircleShape object.
 * 
 *  Table syntax:
 *  - radius:     Number representing radius of the circle.
 *  - pointCount: Number representing number of vertices around the center.
 *  - all properties from Shape
 */
inline std::unique_ptr<sf::CircleShape>& updateCircleShapeFromTable(
        std::unique_ptr<sf::CircleShape>& circle, sol::table obj)
{
        if prop (radius, float)
        {
                circle->setRadius(radius.as<float>());
        }
        if prop (pointCount, std::uint32_t)
        {
                circle->setPointCount(pointCount.as<std::uint32_t>());
        }

        updateShapeFromTable<sf::CircleShape>(circle, obj);
        return circle;
}

/** Transforms a Lua table into an sf::ConvexShape object.
 * 
 *  Table syntax:
 *  - points: Table of vectors representing positions of all vertices.
 *  - all properties from Shape
 */
inline std::unique_ptr<sf::ConvexShape>& updateConvexShapeFromTable(
        std::unique_ptr<sf::ConvexShape>& convex, sol::table obj)
{
        if prop (points, sol::table)
        {
                sol::table pts = points;
                convex->setPointCount(pts.size());
                pts.for_each([&](sol::object i, sol::object pos)
                {
                        convex->setPoint(i.as<std::uint32_t>() - 1, util::Vector{pos.as<sol::table>()});
                });
        }

        updateShapeFromTable<sf::ConvexShape>(convex, obj);
        return convex;
}

/** Transforms a Lua table into an sf::RectangleShape object.
 * 
 *  Table syntax:
 *  - size: Vector representing size of the rectangle.
 *  - all properties from Shape
 */
inline std::unique_ptr<sf::RectangleShape>& updateRectangleShapeFromTable(
        std::unique_ptr<sf::RectangleShape>& rect, sol::table obj)
{
        if prop (size, sol::table)
        {
                rect->setSize(util::Vector{size});
        }

        updateShapeFromTable<sf::RectangleShape>(rect, obj);
        return rect;
}

/** Transforms a Lua table into an sf::Sprite object.
 * 
 *  Table syntax:
 *  - texture:     String containting the id of the texture.
 *  - textureRect: Rectangle representing the area of the texture to be displayed.
 *  - color:       Color blended with the texture.
 */
inline std::unique_ptr<sf::Sprite>& updateSpriteFromTable(
        std::unique_ptr<sf::Sprite>& sprite, sol::table obj)
{
        if prop (texture, std::string)
        {
                if (auto tex = engine::Resources<sf::Texture>::get(texture.as<std::string>()))
                {
                        sprite->setTexture(*tex);
                }
                else
                {
                        std::cerr << util::err::badTextureName(texture.as<std::string>()) << std::endl;
                }
        }

        if prop (textureRect, sol::table)
        {
                sprite->setTextureRect(tableToRectangle<std::int32_t>(textureRect));
        }

        if prop (color, std::string)
        {
                sprite->setColor(stringToColor(color.as<std::string>()));
        }

        updateTransformFromTable(sprite, obj);
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
inline std::unique_ptr<sf::Text>& updateTextFromTable(
        std::unique_ptr<sf::Text>& text, sol::table obj)
{       
        if prop (content, std::string)
        {
                text->setString(std::string(content.as<std::string>()));
        }

        if prop (font, std::string)
        {
                if (auto fptr = engine::Resources<sf::Font>::get(font.as<std::string>()))
                {
                        text->setFont(*fptr);
                }
                else
                {
                        std::cerr << util::err::badFontName(font.as<std::string>()) << std::endl;
                }
        }

        if prop (characterSize, std::uint32_t)
        {
                text->setCharacterSize(characterSize.as<std::uint32_t>());
        }

        if prop (lineSpacing, float)
        {
                text->setLineSpacing(lineSpacing.as<float>());
        }

        if prop (letterSpacing, float)
        {
                text->setLetterSpacing(letterSpacing.as<float>());
        }

        static const util::MapStringTo<sf::Text::Style> styles = {
                { "regular",       sf::Text::Regular       },
                { "bold",          sf::Text::Bold          },
                { "italic",        sf::Text::Italic        },
                { "underlined",    sf::Text::Underlined    },
                { "strikethrough", sf::Text::StrikeThrough },
        };

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

        if prop (style, std::string)
        {
                text->setStyle(getStyle(style.as<std::string>()));
        }
        else if prop (style, sol::table)
        {
                std::int32_t compound = sf::Text::Style::Regular;
                static_cast<sol::table>(style).for_each([&](sol::object, sol::object s)
                {
                        compound |= getStyle(s.as<std::string>());
                });
                text->setStyle(compound);
        }

        if prop (fillColor, std::string)
        {
                text->setFillColor(stringToColor(fillColor.as<std::string>()));
        }
        else if prop (fillColor, sol::table)
        {
                text->setFillColor(tableToColor(fillColor));
        }

        if prop (outlineColor, std::string)
        {
                text->setOutlineColor(stringToColor(outlineColor.as<std::string>()));
        }
        else if prop (outlineColor, sol::table)
        {
                text->setOutlineColor(tableToColor(outlineColor));
        }

        if prop (outlineThickness, float)
        {
                text->setOutlineThickness(outlineThickness.as<float>());
        }

        updateTransformFromTable(text, obj);
        return text;
}

/** Transforms a Lua table into a RectTileMap object.
 * 
 *  Table syntax:
 *  - size:         Vector or number (for a square) specifying the number of rows and columns
 *                  in the tile matrix.
 *  - tileSize:     Vector or number (for a square) specifying the visual size of one tile.
 *  - tileIconSize: Vector or number (for a square) specifying the size of a tile saved in the
 *                  texture.
 *  - tiles:        Matrix specifying IDs of every single tile in the map.
 *  - fill:         Number specifying the ID of the tile with which the map should be filled.
 *  - texture:      String specifying the ID of the texture.
 */
inline std::unique_ptr<util::graphics::RectTileMap>& updateRectTileMapFromTable(
        std::unique_ptr<util::graphics::RectTileMap>& tmap, sol::table obj)
{
        if prop (tileSize, sol::table)
        {
                tmap->setTileSize(util::Vector{tileSize});
        }
        else if prop (tileSize, float)
        {
                const float s = tileSize.as<float>();
                tmap->setTileSize({s, s});
        }
        else
        {
                std::cerr << util::err::noTileSize << std::endl;
        }

        if prop (tileIconSize, sol::table)
        {
                tmap->setTileIconSize(sf::Vector2u{util::Vector{tileIconSize}});
        }
        else if prop (tileIconSize, std::uint32_t)
        {
                const std::uint32_t s = tileIconSize.as<std::uint32_t>();
                tmap->setTileIconSize({s, s});
        }

        if prop (texture, std::string)
        {
                if (auto tex = engine::Resources<sf::Texture>::get(texture.as<std::string>()))
                {
                        tmap->setTexture(&tex->get());
                }
                else
                {
                        std::cerr << util::err::badTextureName(texture.as<std::string>()) << std::endl;
                } 
        }

        if prop (tiles, sol::table)
        {
                auto tileMatrix = tableToMatrix<util::graphics::TileID>(tiles);
                tmap->setMap(tileMatrix);
        }

        if prop (size, sol::table)
        {
                tmap->setSize(sf::Vector2u{util::Vector{size}});
        }
        else if prop (size, std::uint32_t)
        {
                const auto s = size.as<std::uint32_t>();
                tmap->setSize({s, s});
        }

        if prop (fill, std::uint32_t)
        {
                tmap->fill(fill.as<std::uint32_t>());
                obj["fill"] = sol::nil;
        }

        updateTransformFromTable(tmap, obj);
        return tmap;
}

#undef prop

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
 *  - circle (sf::CircleShape)
 *  - convex (sf::ConvexShape)
 *  - rectangle (sf::RectangleShape)
 *  - sprite (sf::Sprite)
 *  - rect tile map (RectTileMap)
 *  - text (sf::Text)
 */
inline std::optional<std::unique_ptr<sf::Drawable>> tableToDrawable(sol::table obj)
{
        const std::string type = obj["type"];

        if (type == "text")
        {
                auto text = std::make_unique<sf::Text>();
                return std::move(updateTextFromTable(text, obj));
        }
        if (type == "sprite")
        {
                auto sprite = std::make_unique<sf::Sprite>();
                return std::move(updateSpriteFromTable(sprite, obj));
        }
        if (type == "circle")
        {
                auto circleShape = std::make_unique<sf::CircleShape>();
                return std::move(updateCircleShapeFromTable(circleShape, obj));
        }
        if (type == "convex")
        {
                auto convexShape = std::make_unique<sf::ConvexShape>();
                return std::move(updateConvexShapeFromTable(convexShape, obj));
        }
        if (type == "rectangle")
        {
                auto rectangleShape = std::make_unique<sf::RectangleShape>();
                return std::move(updateRectangleShapeFromTable(rectangleShape, obj));
        }
        if (type == "rect tile map")
        {
                auto rectTileMap = std::make_unique<util::graphics::RectTileMap>();
                return std::move(updateRectTileMapFromTable(rectTileMap, obj));
        }

        std::cerr << util::err::noDrawableTypeId << std::endl;
        return {};
}

}