#pragma once


#include <Engine/Resources.hpp>

#include <Script/Lua.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Graphics.hpp>
#include <Util/Math.hpp>
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

namespace impl
{
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

        /** Table of tables of numbers, where all inner tables must have equal lengths.
         */
        template<util::Arithmetic T = float>
        inline util::Matrix<T> tableToMatrix(sol::table obj)
        {
                util::Matrix<T> mat;
                mat.resize(obj.size());

                obj.for_each([&](sol::object i, sol::object row)
                {
                        if (row.get_type() != sol::type::table)
                        {
                                std::cerr << util::err::notATable << std::endl;
                                return;
                        }
                        row.as<sol::table>().for_each([&](sol::object, sol::object entry)
                        {
                                if (entry.get_type() != sol::type::number)
                                {
                                        std::cerr << util::err::notANumber << std::endl;
                                        return;
                                }
                                mat[i.as<std::int32_t>() - 1].push_back(entry.as<T>());
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
}



// Shorthand for checking table properties.
#define prop(X, CPP_TYPE) (sol::object X = obj[#X]; X.is<CPP_TYPE>())

template<util::Transformable T>
inline std::unique_ptr<T>& updateTransformFromTable(std::unique_ptr<T>& dobj, sol::table obj)
{
        obj["localBounds"] = dobj->getLocalBounds();

        auto tobj = static_cast<sf::Transformable*>(dobj.get());
        if prop (offset, sf::Vector2f)
        {
                tobj->setPosition(offset.as<sf::Vector2f>());
        }

        if prop (rotation, float)
        {
                tobj->setRotation(rotation.as<float>());
        }

        if prop (scale, sf::Vector2f)
        {
                tobj->setScale(scale.as<sf::Vector2f>());
        }
        else if prop (scale, float)
        {
                const auto s = scale.as<float>();
                tobj->setScale(s, s);
        }

        if prop (origin, std::string)
        {
                if prop (localBounds, sf::FloatRect)
                {
                        const auto o = origin.as<std::string>();
                        const sf::FloatRect bounds = localBounds.as<sf::FloatRect>();
                        const sf::Vector2f size = {bounds.width, bounds.height};
                        tobj->setOrigin(
                                o == "center"       ? sf::Vector2f{size.x / 2, size.y / 2} :
                                o == "top"          ? sf::Vector2f{size.x / 2, 0.f       } :
                                o == "left"         ? sf::Vector2f{0.f,        size.y / 2} :
                                o == "bottom"       ? sf::Vector2f{size.x / 2, size.y    } :
                                o == "right"        ? sf::Vector2f{size.x,     size.y / 2} :
                                o == "bottom-left"  ? sf::Vector2f{0.f,        size.y    } :
                                o == "top-right"    ? sf::Vector2f{size.x,     0.f       } :
                                o == "bottom-right" ? sf::Vector2f{size.x,     size.y    } :
                                /* o == "top-left" */ sf::Vector2f{0.f,        0.f       });
                }
        }
        else if prop (origin, sf::Vector2f)
        {
                tobj->setOrigin(origin.as<sf::Vector2f>());
        }

        obj["globalBounds"] = dobj->getGlobalBounds();
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
template<class ShapeClass> requires std::is_base_of_v<sf::Shape, ShapeClass>
inline std::unique_ptr<ShapeClass>& updateShapeFromTable(
        std::unique_ptr<ShapeClass>& shape, sol::table obj)
{
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

        if prop (textureRect, sf::IntRect)
        {
                shape->setTextureRect(textureRect.as<sf::IntRect>());
        }

        if prop (fillColor, std::string)
        {
                shape->setFillColor(impl::stringToColor(fillColor.as<std::string>()));
        }
        else if prop (fillColor, sf::Color)
        {
                shape->setFillColor(fillColor.as<sf::Color>());
        }

        if prop (outlineColor, std::string)
        {
                shape->setOutlineColor(impl::stringToColor(outlineColor.as<std::string>()));
        }
        else if prop (outlineColor, sf::Color)
        {
                shape->setOutlineColor(outlineColor.as<sf::Color>());
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
inline std::unique_ptr<sf::CircleShape> tableToCircleShape(sol::table obj)
{
        auto circle = std::make_unique<sf::CircleShape>();
        
        if prop (radius, float)
        {
                circle->setRadius(radius.as<float>());
        }
        if prop (pointCount, std::uint32_t)
        {
                circle->setPointCount(pointCount.as<std::uint32_t>());
        }

        updateShapeFromTable(circle, obj);
        return circle;
}

/** Transforms a Lua table into an sf::ConvexShape object.
 * 
 *  Table syntax:
 *  - points: Table of vectors representing positions of all vertices.
 *  - all properties from Shape
 */
inline std::unique_ptr<sf::ConvexShape> tableToConvexShape(sol::table obj)
{
        auto convex = std::make_unique<sf::ConvexShape>();
        
        if prop (points, sol::table)
        {
                sol::table pts = points;
                convex->setPointCount(pts.size());
                for (auto [i, pos] : pts)
                {
                        convex->setPoint(i.as<std::uint32_t>() - 1, pos.as<sf::Vector2f>());
                }
        }

        updateShapeFromTable(convex, obj);
        return convex;
}

/** Transforms a Lua table into an sf::RectangleShape object.
 * 
 *  Table syntax:
 *  - size: Vector representing size of the rectangle.
 *  - all properties from Shape
 */
inline std::unique_ptr<sf::RectangleShape> tableToRectangleShape(sol::table obj)
{
        auto rectangle = std::make_unique<sf::RectangleShape>();
        
        if prop (size, sf::Vector2f)
        {
                rectangle->setSize(size.as<sf::Vector2f>());
        }

        updateShapeFromTable(rectangle, obj);
        return rectangle;
}

/** Transforms a Lua table into an sf::Sprite object.
 * 
 *  Table syntax:
 *  - texture:     String containting the id of the texture.
 *  - textureRect: Rectangle representing the area of the texture to be displayed.
 *  - color:       Color blended with the texture.
 */
inline std::unique_ptr<sf::Sprite> tableToSprite(sol::table obj)
{
        auto sprite = std::make_unique<sf::Sprite>();
        
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

        if prop (textureRect, sf::IntRect)
        {
                sprite->setTextureRect(textureRect.as<sf::IntRect>());
        }

        if prop (color, std::string)
        {
                sprite->setColor(impl::stringToColor(color.as<std::string>()));
        }
        else if prop (color, sf::Color)
        {
                sprite->setColor(color.as<sf::Color>());
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
inline std::unique_ptr<sf::Text> tableToText(sol::table obj)
{       
        auto text = std::make_unique<sf::Text>();
        
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
                for (auto [_, s] : style.as<sol::table>())
                {
                        compound |= getStyle(s.as<std::string>());
                }
                text->setStyle(compound);
        }

        if prop (fillColor, std::string)
        {
                text->setFillColor(impl::stringToColor(fillColor.as<std::string>()));
        }
        else if prop (fillColor, sf::Color)
        {
                text->setFillColor(fillColor.as<sf::Color>());
        }

        if prop (outlineColor, std::string)
        {
                text->setOutlineColor(impl::stringToColor(outlineColor.as<std::string>()));
        }
        else if prop (outlineColor, sf::Color)
        {
                text->setOutlineColor(outlineColor.as<sf::Color>());
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
inline std::unique_ptr<util::graphics::RectTileMap> tableToRectTileMap(sol::table obj)
{
        auto rectTileMap = std::make_unique<util::graphics::RectTileMap>();

        if prop (tileSize, sf::Vector2f)
        {
                rectTileMap->setTileSize(tileSize.as<sf::Vector2f>());
        }
        else if prop (tileSize, float)
        {
                const float s = tileSize.as<float>();
                rectTileMap->setTileSize({s, s});
        }
        else
        {
                std::cerr << util::err::noTileSize << std::endl;
        }

        if prop (tileIconSize, sf::Vector2u)
        {
                rectTileMap->setTileIconSize(tileIconSize.as<sf::Vector2u>());
        }
        else if prop (tileIconSize, std::uint32_t)
        {
                const std::uint32_t s = tileIconSize.as<std::uint32_t>();
                rectTileMap->setTileIconSize({s, s});
        }

        if prop (texture, std::string)
        {
                if (auto tex = engine::Resources<sf::Texture>::get(texture.as<std::string>()))
                {
                        rectTileMap->setTexture(&tex->get());
                }
                else
                {
                        std::cerr << util::err::badTextureName(texture.as<std::string>()) << std::endl;
                } 
        }

        if prop (tiles, sol::table)
        {
                auto tileMatrix = impl::tableToMatrix<util::graphics::TileID>(tiles);
                rectTileMap->setMap(tileMatrix);
        }

        if prop (size, sf::Vector2u)
        {
                rectTileMap->setSize(size.as<sf::Vector2u>());
        }
        else if prop (size, std::uint32_t)
        {
                const auto s = size.as<std::uint32_t>();
                rectTileMap->setSize({s, s});
        }

        if prop (fill, std::uint32_t)
        {
                rectTileMap->fill(fill.as<std::uint32_t>());
                obj["fill"] = sol::nil;
        }

        updateTransformFromTable(rectTileMap, obj);
        return rectTileMap;
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

        if (type == "circle")
        {
                return tableToCircleShape(obj);
        }
        if (type == "convex")
        {
                return tableToConvexShape(obj);
        }
        if (type == "rectangle")
        {
                return tableToRectangleShape(obj);
        }
        if (type == "sprite")
        {
                return tableToSprite(obj);
        }
        if (type == "text")
        {
                return tableToText(obj);
        }
        if (type == "rect tile map")
        {
                return tableToRectTileMap(obj);
        }

        std::cerr << util::err::noDrawableTypeId << std::endl;
        return {};
}

inline static void loadGraphics()
{
        // Color
        const auto hspcm = [](float h, float s, float p, const float c, const float m)
        {
                struct fRGB { float r; float g; float b; };

                h = std::fmod(h, 360);
                s = std::clamp(s, 0.f, 1.f);
                p = std::clamp(p, 0.f, 1.f); // (The "p" here stands for "parameter", either l or v)

                const float x = c * (1 - std::fabs(std::fmod(h / 60, 2) - 1));
                const auto c1 = util::isWithin(h,   0.f,  60.f) ? fRGB{c, x, 0}
                              : util::isWithin(h,  60.f, 120.f) ? fRGB{x, c, 0}
                              : util::isWithin(h, 120.f, 180.f) ? fRGB{0, c, x}
                              : util::isWithin(h, 180.f, 240.f) ? fRGB{0, x, c}
                              : util::isWithin(h, 240.f, 300.f) ? fRGB{x, 0, c}
                              :             /* 300 ≤ h < 360 ? */ fRGB{c, 0, x};

                return sf::Color{static_cast<sf::Uint8>((c1.r + m) * 255), 
                                 static_cast<sf::Uint8>((c1.g + m) * 255), 
                                 static_cast<sf::Uint8>((c1.b + m) * 255)};
        };

        lua.new_usertype<sf::Color>("color",
                sol::no_constructor,
                "r", &sf::Color::r,
                "g", &sf::Color::g,
                "b", &sf::Color::b,
                "a", &sf::Color::a,
                "rgb",  [](const sf::Uint8 r, const sf::Uint8 g, const sf::Uint8 b)
                        {
                                return sf::Color{r, g, b};
                        },
                "rgba", [](const sf::Uint8 r, const sf::Uint8 g, const sf::Uint8 b, const sf::Uint8 a)
                        {
                                return sf::Color{r, g, b, a};
                        },
                "hsl",  [hspcm](const float h, const float s, const float l)
                        {
                                const float c = s * (1 - std::fabs(2 * l - 1));
                                const float m = l - c * 0.5f;
                                return hspcm(h, s, l, c, m);
                        },
                "hsv",  [hspcm](const float h, const float s, const float v)
                        {
                                const float c = v * s;
                                const float m = v - c;
                                return hspcm(h, s, v, c, m);
                        },
                "add",      std::plus<sf::Color>{},
                "subtract", std::minus<sf::Color>{},
                "multiply", std::multiplies<sf::Color>{});

        // Base classes
        lua.new_usertype<sf::Drawable>("sfdrawable", sol::no_constructor);
        lua.new_usertype<sf::Transformable>("sftransformable",
                sol::no_constructor,
                "offset", sol::property(
                        &sf::Transformable::getPosition,
                        static_cast<void(sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::setPosition)),
                "rotation", sol::property(
                        &sf::Transformable::getRotation,
                        &sf::Transformable::setRotation),
                "scale", sol::property(
                        &sf::Transformable::getScale,
                        static_cast<void(sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::setScale)),
                "origin", sol::property(
                        &sf::Transformable::getOrigin,
                        static_cast<void(sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::setOrigin)),
                "moveBy",   static_cast<void(sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::move),
                "scaleBy",  static_cast<void(sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::scale),
                "rotateBy", &sf::Transformable::rotate);

        lua.new_usertype<sf::Shape>("sfshape",
                sol::no_constructor,
                "texture", sol::property(
                        [](sf::Shape& s, const std::string& id)
                        {
                                if (auto tex = engine::Resources<sf::Texture>::get(id))
                                {
                                        s.setTexture(&tex->get());
                                }
                                else
                                {
                                        std::cerr << util::err::badTextureName(id) << std::endl;
                                }
                        }),
                "textureRect", sol::property(
                        &sf::Shape::getTextureRect,
                        &sf::Shape::setTextureRect),
                "fillColor", sol::property(
                        &sf::Shape::getFillColor,
                        &sf::Shape::setFillColor),
                "outlineColor", sol::property(
                        &sf::Shape::getOutlineColor,
                        &sf::Shape::setOutlineColor),
                "outlineThickness", sol::property(
                        &sf::Shape::getOutlineThickness,
                        &sf::Shape::setOutlineThickness),
                "point",        &sf::Shape::getPoint,
                "pointCount",   sol::property(&sf::Shape::getPointCount),
                "localBounds",  sol::property(&sf::Shape::getLocalBounds),
                "globalBounds", sol::property(&sf::Shape::getGlobalBounds),
                sol::base_classes, sol::bases<sf::Drawable, sf::Transformable>{});

        // Actual graphical objects
        lua.new_usertype<sf::CircleShape>("circle",
                sol::constructors<
                        sf::CircleShape(),
                        sf::CircleShape(float),
                        sf::CircleShape(float, std::size_t)>{},
                "radius", sol::property(
                        &sf::CircleShape::getRadius,
                        &sf::CircleShape::setRadius),
                "pointCount", sol::property(
                        &sf::CircleShape::getPointCount,
                        &sf::CircleShape::setPointCount),
                sol::base_classes, sol::bases<sf::Shape>{});

        lua.new_usertype<sf::ConvexShape>("convex",
                sol::constructors<
                        sf::ConvexShape(),
                        sf::ConvexShape(std::size_t)>{},
                "point", sol::overload(
                        &sf::ConvexShape::getPoint,
                        &sf::ConvexShape::setPoint),
                "pointCount", sol::property(
                        &sf::ConvexShape::getPointCount,
                        &sf::ConvexShape::setPointCount),
                sol::base_classes, sol::bases<sf::Shape>{});

        lua.new_usertype<sf::RectangleShape>("rectangle",
                sol::constructors<
                        sf::RectangleShape(),
                        sf::RectangleShape(const sf::Vector2f&)>(),
                "size", sol::property(
                        &sf::RectangleShape::getSize,
                        &sf::RectangleShape::setSize),
                sol::base_classes, sol::bases<sf::Shape>{});

        lua.new_usertype<sf::Sprite>("sprite",
                sol::constructors<sf::Sprite()>{},
                // Other constructors isn't be supported due to the presence of
                // sf::Texture& parameter.
                "texture", sol::property(
                        [](sf::Sprite& s, const std::string& id)
                        {
                                if (auto tex = engine::Resources<sf::Texture>::get(id))
                                {
                                        s.setTexture(tex->get());
                                }
                                else
                                {
                                        std::cerr << util::err::badTextureName(id) << std::endl;
                                }
                        }),
                "textureRect", sol::property(
                        &sf::Sprite::getTextureRect,
                        &sf::Sprite::setTextureRect),
                "color", sol::property(
                        &sf::Sprite::getColor,
                        &sf::Sprite::setColor),
                "localBounds",  sol::property(&sf::Sprite::getLocalBounds),
                "globalBounds", sol::property(&sf::Sprite::getGlobalBounds),
                sol::base_classes, sol::bases<sf::Drawable, sf::Transformable>{});

        lua.new_usertype<sf::Text>("text",
                sol::constructors<sf::Text()>{},
                // The other constructor isn't be supported due to the presence of
                // sf::Font& parameter.
                "string", sol::property(
                        [](sf::Text& t) { return t.getString().toAnsiString(); },
                        [](sf::Text& t, const std::string& s) { t.setString(s); }),
                "font", sol::property(
                        [](sf::Text& s, const std::string& id)
                        {
                                if (auto font = engine::Resources<sf::Font>::get(id))
                                {
                                        s.setFont(font->get());
                                }
                                else
                                {
                                        std::cerr << util::err::badFontName(id) << std::endl;
                                }
                        }),
                "charSize", sol::property(
                        &sf::Text::getCharacterSize,
                        &sf::Text::setCharacterSize),
                "lineSpacing", sol::property(
                        &sf::Text::getLineSpacing,
                        &sf::Text::setLineSpacing),
                "letterSpacing", sol::property(
                        &sf::Text::getLetterSpacing,
                        &sf::Text::setLetterSpacing),
                "style", sol::property(
                        &sf::Text::getStyle,
                        &sf::Text::setStyle),
                "fillColor", sol::property(
                        &sf::Text::getFillColor,
                        &sf::Text::setFillColor),
                "outlineColor", sol::property(
                        &sf::Text::getOutlineColor,
                        &sf::Text::setOutlineColor),
                "outlineThickness", sol::property(
                        &sf::Text::getOutlineThickness,
                        &sf::Text::setOutlineThickness),
                "localBounds",  sol::property(&sf::Text::getLocalBounds),
                "globalBounds", sol::property(&sf::Text::getGlobalBounds),
                "charPosition", &sf::Text::findCharacterPos,
                sol::base_classes, sol::bases<sf::Drawable, sf::Transformable>{});

        lua.create_named_table("textStyle",
                "regular",       sf::Text::Regular,
                "bold",          sf::Text::Bold,
                "italic",        sf::Text::Italic,
                "underlined",    sf::Text::Underlined,
                "strikeThrough", sf::Text::StrikeThrough);

        lua.new_usertype<util::graphics::RectTileMap>("rectTileMap",
                sol::constructors<
                        util::graphics::RectTileMap(),
                        util::graphics::RectTileMap(sf::Vector2u),
                        util::graphics::RectTileMap(sf::Vector2u, sf::Vector2f),
                        util::graphics::RectTileMap(sf::Vector2u, sf::Vector2f, sf::Vector2u),
                        util::graphics::RectTileMap(const util::graphics::RectTileMap&)>{},
                "fillWith",     &util::graphics::RectTileMap::fill,
                "fillAreaWith", &util::graphics::RectTileMap::fillArea,
                "setTile",      &util::graphics::RectTileMap::setTile,
                "setMap",       &util::graphics::RectTileMap::setMap,
                "size", sol::property(
                        &util::graphics::RectTileMap::getSize,
                        &util::graphics::RectTileMap::setSize),
                "tileSize", sol::property(
                        &util::graphics::RectTileMap::getTileSize,
                        &util::graphics::RectTileMap::setTileSize),
                "iconSize", sol::property(
                        &util::graphics::RectTileMap::getTileIconSize,
                        &util::graphics::RectTileMap::setTileIconSize),
                "localBounds",  sol::property(&util::graphics::RectTileMap::getLocalBounds),
                "globalBounds", sol::property(&util::graphics::RectTileMap::getGlobalBounds),
                sol::base_classes, sol::bases<sf::Drawable, sf::Transformable>{});
}

}