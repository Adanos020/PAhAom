#pragma once


#include <Engine/Resources.hpp>

#include <Script/Lua.hpp>

#include <Util/Concepts.hpp>
#include <Util/ErrorMessages.hpp>
#include <Util/Graphics.hpp>
#include <Util/Types.hpp>

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <memory>
#include <type_traits>
#include <unordered_map>


namespace script
{

// Externals

inline lua::Retval rgba(lua::Context& context)
{
        context.requireArgs<std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t>(4);
        return context.ret(lua::Table::records(context,
                "r", context.args[0].to<std::uint32_t>(),
                "g", context.args[1].to<std::uint32_t>(),
                "b", context.args[2].to<std::uint32_t>(),
                "a", context.args[3].to<std::uint32_t>()
        ));
}

inline lua::Retval rgb(lua::Context& context)
{
        context.requireArgs<std::uint32_t, std::uint32_t, std::uint32_t>(3);
        return context.ret(lua::Table::records(context,
                "r", context.args[0].to<std::uint32_t>(),
                "g", context.args[1].to<std::uint32_t>(),
                "b", context.args[2].to<std::uint32_t>()
        ));
}

// Internals

inline sf::Color stringToColor(const std::string& str)
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

        luaContext.error(util::err::badColorName(str));
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
        return {
                static_cast<sf::Uint8>(obj["r"].to<std::uint32_t>(0u)),
                static_cast<sf::Uint8>(obj["g"].to<std::uint32_t>(0u)),
                static_cast<sf::Uint8>(obj["b"].to<std::uint32_t>(0u)),
                static_cast<sf::Uint8>(obj["a"].to<std::uint32_t>(255u)),
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
inline sf::Rect<T> tableToRectangle(const lua::Table& obj)
{
        return {
                obj["left"  ].to<T>(0),
                obj["top"   ].to<T>(0),
                obj["width" ].to<T>(0),
                obj["height"].to<T>(0),
        };
}

/** Table of tables of numbers, where all inner tables must have equal lengths.
 */
template<util::Arithmetic T = float>
inline util::Matrix<T> tableToMatrix(const lua::Table& obj)
{
        util::Matrix<T> mat;
        mat.resize(obj.len().to<std::uint32_t>());

        obj.iterate([&](lua::Valref i, lua::Valref row) {
                if (not row.is<lua::Table>())
                {
                        luaContext.error(util::err::notATable);
                }
                static_cast<lua::Table>(row).iterate([&](lua::Valref, lua::Valref entry) {
                        if (not entry.is<float>())
                        {
                                luaContext.error(util::err::notANumber);
                        }
                        mat[static_cast<std::int32_t>(i - 1)].push_back(
                                static_cast<T>(entry.to<float>()));
                });
        });

        // All columns must have equal numbers of rows.
        if (std::any_of(mat.begin(), mat.end(), [&](auto& row)
                { return row.size() != mat[0].size(); }))
        {
                luaContext.error(util::err::matrixNotRegular);
        }

        return mat;
}

template<util::Drawable T>
inline void extractLocalBounds(const std::unique_ptr<T>& dobj, lua::Table& obj)
{
        const sf::FloatRect bounds = dobj->getLocalBounds();
        obj["localBounds"] = lua::Table::records(luaContext,
                "left",   bounds.left,
                "top",    bounds.top,
                "width",  bounds.width,
                "height", bounds.height
        );
}

template<util::Drawable T>
inline void extractGlobalBounds(const std::unique_ptr<T>& dobj, lua::Table& obj)
{
        const sf::FloatRect bounds = dobj->getGlobalBounds();
        obj["globalBounds"] = lua::Table::records(luaContext,
                "left",   bounds.left,
                "top",    bounds.top,
                "width",  bounds.width,
                "height", bounds.height
        );
}


// Shorthand for checking table properties.
#define prop(X, CPP_TYPE) (lua::Value X = obj[#X]; X.is<CPP_TYPE>())

template<class TransformableObj>
inline std::unique_ptr<TransformableObj>& updateTransformFromTable(
        std::unique_ptr<TransformableObj>& dobj, lua::Table& obj)
{
        static_assert(std::is_base_of_v<sf::Transformable, TransformableObj>);

        extractLocalBounds(dobj, obj);

        auto tobj = static_cast<sf::Transformable*>(dobj.get());
        if prop (position, lua::Table)
        {
                tobj->setPosition(util::Vector{position});
        }

        if prop (rotation, float)
        {
                tobj->setRotation(rotation);
        }

        if prop (scale, lua::Table)
        {
                tobj->setScale(util::Vector{scale});
        }
        else if prop (scale, float)
        {
                tobj->setScale(scale, scale);
        }

        if prop (origin, std::string)
        {
                if prop (localBounds, lua::Table)
                {
                        sf::FloatRect bounds = tableToRectangle(localBounds);
                        tobj->setOrigin(
                                origin == "center"       ? sf::Vector2f{bounds.width / 2, bounds.height / 2} :
                                origin == "top"          ? sf::Vector2f{bounds.width / 2, 0.f              } :
                                origin == "left"         ? sf::Vector2f{0.f,              bounds.height / 2} :
                                origin == "bottom"       ? sf::Vector2f{bounds.width / 2, bounds.height    } :
                                origin == "right"        ? sf::Vector2f{bounds.width,     bounds.height / 2} :
                                origin == "bottom-left"  ? sf::Vector2f{0.f,              bounds.height    } :
                                origin == "top-right"    ? sf::Vector2f{bounds.width,     0.f              } :
                                origin == "bottom-right" ? sf::Vector2f{bounds.width,     bounds.height    } :
                                /* origin == "top-left" */ sf::Vector2f{0.f,              0.f              }
                        );
                }
        }
        else if prop (origin, lua::Table)
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
        std::unique_ptr<ShapeClass>& shape, lua::Table& obj)
{
        static_assert(
                std::is_same_v<ShapeClass, sf::CircleShape> or
                std::is_same_v<ShapeClass, sf::ConvexShape> or
                std::is_same_v<ShapeClass, sf::RectangleShape>);

        if prop (texture, std::string)
        {
                if (auto tex = engine::Resources<sf::Texture>::get(texture))
                {
                        shape->setTexture(&tex->get());
                }
                else
                {
                        luaContext.error(util::err::badTextureName(texture));
                }
        }

        if prop (textureRect, lua::Table)
        {
                shape->setTextureRect(tableToRectangle<std::int32_t>(textureRect));
        }

        if prop (fillColor, std::string)
        {
                shape->setFillColor(stringToColor(fillColor));
        }
        else if prop (fillColor, lua::Table)
        {
                shape->setFillColor(tableToColor(fillColor));
        }

        if prop (outlineColor, std::string)
        {
                shape->setOutlineColor(stringToColor(outlineColor));
        }
        else if prop (outlineColor, lua::Table)
        {
                shape->setOutlineColor(tableToColor(outlineColor));
        }

        if prop (outlineThickness, float)
        {
                shape->setOutlineThickness(outlineThickness);
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
        std::unique_ptr<sf::CircleShape>& circle, lua::Table& obj)
{
        if prop (radius, float)
        {
                circle->setRadius(radius);
        }
        if prop (pointCount, std::uint32_t)
        {
                circle->setPointCount(pointCount.to<std::uint32_t>());
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
        std::unique_ptr<sf::ConvexShape>& convex, lua::Table& obj)
{
        if prop (points, lua::Table)
        {
                lua::Table pts = points;
                convex->setPointCount(pts.len().to<std::uint32_t>());
                pts.iterate([&](lua::Valref i, lua::Valref pos) {
                        convex->setPoint(i.to<std::uint32_t>() - 1, util::Vector{pos});
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
        std::unique_ptr<sf::RectangleShape>& rect, lua::Table& obj)
{
        if prop (size, lua::Table)
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
        std::unique_ptr<sf::Sprite>& sprite, lua::Table& obj)
{
        if prop (texture, std::string)
        {
                if (auto tex = engine::Resources<sf::Texture>::get(texture))
                {
                        sprite->setTexture(*tex);
                }
                else
                {
                        luaContext.error(util::err::badTextureName(texture));
                }
        }

        if prop (textureRect, lua::Table)
        {
                sprite->setTextureRect(tableToRectangle<std::int32_t>(textureRect));
        }

        if prop (color, std::string)
        {
                sprite->setColor(stringToColor(color));
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
        std::unique_ptr<sf::Text>& text, lua::Table& obj)
{       
        if prop (content, std::string)
        {
                text->setString(std::string(content));
        }

        if prop (font, std::string)
        {
                if (auto fptr = engine::Resources<sf::Font>::get(font))
                {
                        text->setFont(*fptr);
                }
                else
                {
                        luaContext.error(util::err::badFontName(font));
                }
        }

        if prop (characterSize, std::uint32_t)
        {
                text->setCharacterSize(characterSize);
        }

        if prop (lineSpacing, float)
        {
                text->setLineSpacing(lineSpacing);
        }

        if prop (letterSpacing, float)
        {
                text->setLetterSpacing(letterSpacing);
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
                        luaContext.error(util::err::badTextStyleName(style));
                        return sf::Text::Style::Regular;
                }
        };

        if prop (style, std::string)
        {
                text->setStyle(getStyle(style));
        }
        else if prop (style, lua::Table)
        {
                std::int32_t compound = sf::Text::Style::Regular;
                static_cast<lua::Table>(style).iterate(
                        [&](lua::Valref, lua::Valref s) { compound |= getStyle(s); });
                text->setStyle(compound);
        }

        if prop (fillColor, std::string)
        {
                text->setFillColor(stringToColor(fillColor));
        }
        else if prop (fillColor, lua::Table)
        {
                text->setFillColor(tableToColor(fillColor));
        }

        if prop (outlineColor, std::string)
        {
                text->setOutlineColor(stringToColor(outlineColor));
        }
        else if prop (outlineColor, lua::Table)
        {
                text->setOutlineColor(tableToColor(outlineColor));
        }

        if prop (outlineThickness, float)
        {
                text->setOutlineThickness(outlineThickness);
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
        std::unique_ptr<util::graphics::RectTileMap>& tmap, lua::Table& obj)
{
        if prop (tileSize, lua::Table)
        {
                tmap->setTileSize(util::Vector{tileSize});
        }
        else if prop (tileSize, float)
        {
                const float s = tileSize;
                tmap->setTileSize({s, s});
        }
        else
        {
                luaContext.error(util::err::noTileSize);
        }

        if prop (tileIconSize, lua::Table)
        {
                tmap->setTileIconSize(sf::Vector2u{util::Vector{tileIconSize}});
        }
        else if prop (tileIconSize, std::uint32_t)
        {
                const std::uint32_t s = tileIconSize;
                tmap->setTileIconSize({s, s});
        }

        if prop (texture, std::string)
        {
                if (auto tex = engine::Resources<sf::Texture>::get(texture))
                {
                        tmap->setTexture(&tex->get());
                }
                else
                {
                        luaContext.error(util::err::badTextureName(texture));
                } 
        }

        if prop (tiles, lua::Table)
        {
                auto tileMatrix = tableToMatrix<util::graphics::TileID>(tiles);
                tmap->setMap(tileMatrix);
        }

        if prop (size, lua::Table)
        {
                tmap->setSize(sf::Vector2u{util::Vector{size}});
        }
        else if prop (size, std::uint32_t)
        {
                const std::uint32_t s = size;
                tmap->setSize({s, s});
        }

        if prop (fill, std::uint32_t)
        {
                tmap->fill(fill.to<std::uint32_t>());
                obj["fill"] = lua::nil;
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
inline std::optional<std::unique_ptr<sf::Drawable>> tableToDrawable(lua::Table& obj)
{
        const lua::Value type = obj["type"];

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

        luaContext.error(util::err::noDrawableTypeId);
        return {};
}

}