#pragma once


#include <Engine/Resources.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Observer.hpp>

#include <lua.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <memory>
#include <unordered_map>


namespace util
{

inline static lua::State luaState;
inline static lua::Context luaContext = {
        luaState.getRawState(),
        lua::Context::initializeExplicitly
};


// Messages.

/** Broadcasts a message from Lua to the Subject.
 */
inline auto broadcast(lua::Context& context) -> lua::Retval
{
        const lua::Table msg = context.args.at(0);

        lua::Value type = msg["type"];
        if (type.type() != lua::ValueType::String)
        {
                std::cerr << util::err::noMessageTypeId() << std::endl;
        }

        if (type == "PushState")
        {
                if (lua::Value state = msg["state"]; state.type() == lua::ValueType::String)
                {
                        util::Subject::send({ util::Message::PushState{ state } });
                }
                else
                {
                        std::cerr << util::err::noPushStateName() << std::endl;
                }
        }
        else if (type == "PopState")
        {
                util::Subject::send({ util::Message::PopState{} });
        }

        return context.ret();
}

// Window handling.

inline auto eventToTable(const sf::Event& event) -> lua::Table
{
        lua::Table table { luaContext };

        switch (event.type)
        {
                case sf::Event::Closed:
                {
                        table["type"] = "Closed";
                        break;
                }

                case sf::Event::Resized:
                {
                        table["type"] = "Resized";
                        table["width"] = event.size.width;
                        table["height"] = event.size.height;
                        break;
                }

                case sf::Event::LostFocus:
                {
                        table["type"] = "LostFocus";
                        break;
                }

                case sf::Event::GainedFocus:
                {
                        table["type"] = "GainedFocus";
                        break;
                }

                case sf::Event::TextEntered:
                {
                        table["type"] = "TextEntered";
                        table["unicode"] = "unicode";
                        break;
                }

                case sf::Event::KeyPressed:
                {
                        table["type"] = "KeyPressed";
                        table["code"]    = event.key.code;
                        table["alt"]     = event.key.alt;
                        table["control"] = event.key.control;
                        table["shift"]   = event.key.shift;
                        table["system"]  = event.key.system;
                        break;
                }

                case sf::Event::KeyReleased:
                {
                        table["type"] = "KeyReleased";
                        table["code"]    = event.key.code;
                        table["alt"]     = event.key.alt;
                        table["control"] = event.key.control;
                        table["shift"]   = event.key.shift;
                        table["system"]  = event.key.system;
                        break;
                }

                case sf::Event::MouseWheelMoved:
                {
                        table["type"] = "MouseWheelMoved";
                        table["delta"] = event.mouseWheel.delta;
                        table["x"] = event.mouseWheel.x;
                        table["y"] = event.mouseWheel.y;
                        break;
                }

                case sf::Event::MouseWheelScrolled:
                {
                        table["type"] = "MouseWheelScrolled";
                        table["delta"] = event.mouseWheelScroll.delta;
                        table["x"] = event.mouseWheelScroll.x;
                        table["y"] = event.mouseWheelScroll.y;
                        break;
                }

                case sf::Event::MouseButtonPressed:
                {
                        table["type"] = "MouseButtonPressed";
                        table["button"] = event.mouseButton.button;
                        table["x"] = event.mouseButton.x;
                        table["y"] = event.mouseButton.y;
                        break;
                }

                case sf::Event::MouseButtonReleased:
                {
                        table["type"] = "MouseButtonReleased";
                        table["button"] = event.mouseButton.button;
                        table["x"] = event.mouseButton.x;
                        table["y"] = event.mouseButton.y;
                        break;
                }

                case sf::Event::MouseMoved:
                {
                        table["type"] = "MouseMoved";
                        table["x"] = event.mouseMove.x;
                        table["y"] = event.mouseMove.y;
                        break;
                }

                case sf::Event::MouseEntered:
                {
                        table["type"] = "MouseEntered";
                        break;
                }

                case sf::Event::MouseLeft:
                {
                        table["type"] = "MouseLeft";
                        break;
                }

                case sf::Event::JoystickButtonPressed:
                {
                        table["type"] = "JoystickButtonPressed";
                        table["joystickId"] = event.joystickButton.joystickId;
                        table["button"] = event.joystickButton.button;
                        break;
                }

                case sf::Event::JoystickButtonReleased:
                {
                        table["type"] = "JoystickButtonReleased";
                        table["joystickId"] = event.joystickButton.joystickId;
                        table["button"] = event.joystickButton.button;
                        break;
                }

                case sf::Event::JoystickMoved:
                {
                        table["type"] = "JoystickMoved";
                        table["joystickId"] = event.joystickMove.joystickId;
                        table["axis"] = event.joystickMove.axis;
                        table["position"] = event.joystickMove.position;
                        break;
                }

                case sf::Event::JoystickConnected:
                {
                        table["type"] = "JoystickConnected";
                        table["joystickId"] = event.joystickConnect.joystickId;
                        break;
                }

                case sf::Event::JoystickDisconnected:
                {
                        table["type"] = "JoystickDisconnected";
                        table["joystickId"] = event.joystickConnect.joystickId;
                        break;
                }

                case sf::Event::TouchBegan:
                {
                        table["type"] = "TouchBegan";
                        table["finger"] = event.touch.finger;
                        table["x"] = event.touch.x;
                        table["y"] = event.touch.y;
                        break;
                }

                case sf::Event::TouchMoved:
                {
                        table["type"] = "TouchMoved";
                        table["finger"] = event.touch.finger;
                        table["x"] = event.touch.x;
                        table["y"] = event.touch.y;
                        break;
                }

                case sf::Event::TouchEnded:
                {
                        table["type"] = "TouchEnded";
                        table["finger"] = event.touch.finger;
                        table["x"] = event.touch.x;
                        table["y"] = event.touch.y;
                        break;
                }

                case sf::Event::SensorChanged:
                {
                        table["type"] = "SensorChanged";
                        table["sensorType"] = event.sensor.type;
                        table["x"] = event.sensor.x;
                        table["y"] = event.sensor.y;
                        table["z"] = event.sensor.z;
                        break;
                }

                default: break;
        }

        return table;
}

// Graphics-related.

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
        static const std::unordered_map<std::string, sf::Color> predefinedColors = {
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


// Shorthand for checking table properties.
#define prop(x, luatype) if (lua::Value x = obj[#x]; x.type() == lua::ValueType::luatype)


/** Transforms a Lua table into an sf::CircleShape object.
 * 
 *  Table syntax:
 *  - radius:     Number representing radius of the circle.
 *  - pointCount: Number representing number of vertices around the center.
 *  - all properties from Shape
 */
inline auto tableToCircleShape(const lua::Table& obj) -> std::unique_ptr<sf::CircleShape>
{
        std::unique_ptr<sf::CircleShape> circleShape { new sf::CircleShape };

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
inline auto tableToConvexShape(const lua::Table& obj) -> std::unique_ptr<sf::ConvexShape>
{
        std::unique_ptr<sf::ConvexShape> convShape { new sf::ConvexShape };

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
inline auto tableToRectangleShape(const lua::Table& obj) -> std::unique_ptr<sf::RectangleShape>
{
        std::unique_ptr<sf::RectangleShape> rectShape { new sf::RectangleShape };

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
inline auto tableToShape(const lua::Table& obj) -> std::unique_ptr<sf::Shape>
{
        std::unique_ptr<sf::Shape> shape { nullptr };

#define get(type, retfun) if (obj["type"] == #type) shape = retfun(obj)

        get(sfCircleShape, tableToCircleShape); else
        get(sfConvexShape, tableToConvexShape); else
        get(sfRectangleShape, tableToRectangleShape);

#undef get

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

        return shape;
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
inline auto tableToText(const lua::Table& obj) -> std::unique_ptr<sf::Text>
{
        static const std::unordered_map<std::string, sf::Text::Style> styles = {
                { "regular",       sf::Text::Regular       },
                { "bold",          sf::Text::Bold          },
                { "italic",        sf::Text::Italic        },
                { "underlined",    sf::Text::Underlined    },
                { "strikethrough", sf::Text::StrikeThrough },
        };
        
        auto text = new sf::Text;

        const auto setStyle = [&](const std::string& style)
        {
                if (auto s = styles.find(style); s != styles.end())
                {
                        text->setStyle(s->second);
                }
                else
                {
                        std::cerr << util::err::badTextStyleName(style) << std::endl;
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
                setStyle(style);
        }
        prop (style, Table)
        {
                for (int i = 1, nStyles = style.len(); i < nStyles; ++i)
                {
                        setStyle(style[i]);
                }
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
inline auto tableToDrawable(const lua::Value& obj) -> std::unique_ptr<sf::Drawable>
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
        prop (origin, Table)
        {
                transformable->setOrigin(tableToVector(origin));
        }

        return drawable;
}

#undef prop
#undef get

}