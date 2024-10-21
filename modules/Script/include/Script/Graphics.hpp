#pragma once

#include <Engine/Resources.hpp>

#include <Script/Lua.hpp>

// #include <Util/ErrorMessages.hpp>
#include <Util/Graphics.hpp>
// #include <Util/Math.hpp>
// #include <Util/Types.hpp>

#include <SFML/Graphics.hpp>

// #include <cstdint>
#include <memory>
// #include <type_traits>

namespace script
{

namespace impl
{
        sf::Color stringToColor(const std::string& str);
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
inline std::unique_ptr<ShapeClass>& updateShapeFromTable(std::unique_ptr<ShapeClass>& shape, sol::table obj)
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

#undef prop

/** Transforms a Lua table into an sf::CircleShape object.
 * 
 *  Table syntax:
 *  - radius:     Number representing radius of the circle.
 *  - pointCount: Number representing number of vertices around the center.
 *  - all properties from Shape
 */
std::unique_ptr<sf::CircleShape> tableToCircleShape(sol::table obj);

/** Transforms a Lua table into an sf::ConvexShape object.
 * 
 *  Table syntax:
 *  - points: Table of vectors representing positions of all vertices.
 *  - all properties from Shape
 */
std::unique_ptr<sf::ConvexShape> tableToConvexShape(sol::table obj);

/** Transforms a Lua table into an sf::RectangleShape object.
 * 
 *  Table syntax:
 *  - size: Vector representing size of the rectangle.
 *  - all properties from Shape
 */
std::unique_ptr<sf::RectangleShape> tableToRectangleShape(sol::table obj);

/** Transforms a Lua table into an sf::Sprite object.
 * 
 *  Table syntax:
 *  - texture:     String containting the id of the texture.
 *  - textureRect: Rectangle representing the area of the texture to be displayed.
 *  - color:       Color blended with the texture.
 */
std::unique_ptr<sf::Sprite> tableToSprite(sol::table obj);

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
std::unique_ptr<sf::Text> tableToText(sol::table obj);

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
std::unique_ptr<util::graphics::RectTileMap> tableToRectTileMap(sol::table obj);

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
std::optional<std::unique_ptr<sf::Drawable>> tableToDrawable(sol::table obj);

void loadGraphics();

}