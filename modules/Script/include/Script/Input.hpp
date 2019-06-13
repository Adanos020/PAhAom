#pragma once


#include <Script/Lua.hpp>

#include <Util/String.hpp>

#include <SFML/Window/Event.hpp>


namespace script
{

inline lua::Table eventToTable(const sf::Event& event)
{
        auto table = lua::Table{luaContext};

        switch (event.type)
        {
                case sf::Event::Closed:
                {
                        table["type"] = "closed";
                        break;
                }

                case sf::Event::Resized:
                {
                        table["type"] = "resized";
                        table["width"] = event.size.width;
                        table["height"] = event.size.height;
                        break;
                }

                case sf::Event::LostFocus:
                {
                        table["type"] = "lost focus";
                        break;
                }

                case sf::Event::GainedFocus:
                {
                        table["type"] = "gained focus";
                        break;
                }

                case sf::Event::TextEntered:
                {
                        table["type"] = "text entered";
                        table["unicode"] = "unicode";
                        break;
                }

                case sf::Event::KeyPressed:
                {
                        table["type"] = "key pressed";
                        table["code"]    = event.key.code;
                        table["alt"]     = event.key.alt;
                        table["control"] = event.key.control;
                        table["shift"]   = event.key.shift;
                        table["system"]  = event.key.system;
                        break;
                }

                case sf::Event::KeyReleased:
                {
                        table["type"] = "key released";
                        table["code"]    = event.key.code;
                        table["alt"]     = event.key.alt;
                        table["control"] = event.key.control;
                        table["shift"]   = event.key.shift;
                        table["system"]  = event.key.system;
                        break;
                }

                case sf::Event::MouseWheelMoved:
                {
                        table["type"] = "mouse wheel moved";
                        table["delta"] = event.mouseWheel.delta;
                        table["x"] = event.mouseWheel.x;
                        table["y"] = event.mouseWheel.y;
                        break;
                }

                case sf::Event::MouseWheelScrolled:
                {
                        table["type"] = "mouse wheel scrolled";
                        table["delta"] = event.mouseWheelScroll.delta;
                        table["x"] = event.mouseWheelScroll.x;
                        table["y"] = event.mouseWheelScroll.y;
                        break;
                }

                case sf::Event::MouseButtonPressed:
                {
                        table["type"] = "mouse pressed";
                        table["button"] = event.mouseButton.button;
                        table["x"] = event.mouseButton.x;
                        table["y"] = event.mouseButton.y;
                        break;
                }

                case sf::Event::MouseButtonReleased:
                {
                        table["type"] = "mouse released";
                        table["button"] = event.mouseButton.button;
                        table["x"] = event.mouseButton.x;
                        table["y"] = event.mouseButton.y;
                        break;
                }

                case sf::Event::MouseMoved:
                {
                        table["type"] = "mouse moved";
                        table["x"] = event.mouseMove.x;
                        table["y"] = event.mouseMove.y;
                        break;
                }

                case sf::Event::MouseEntered:
                {
                        table["type"] = "mouse entered";
                        break;
                }

                case sf::Event::MouseLeft:
                {
                        table["type"] = "mouse left";
                        break;
                }

                case sf::Event::JoystickButtonPressed:
                {
                        table["type"] = "joystick pressed";
                        table["joystickId"] = event.joystickButton.joystickId;
                        table["button"] = event.joystickButton.button;
                        break;
                }

                case sf::Event::JoystickButtonReleased:
                {
                        table["type"] = "joystick released";
                        table["joystickId"] = event.joystickButton.joystickId;
                        table["button"] = event.joystickButton.button;
                        break;
                }

                case sf::Event::JoystickMoved:
                {
                        table["type"] = "joystick moved";
                        table["joystickId"] = event.joystickMove.joystickId;
                        table["axis"] = event.joystickMove.axis;
                        table["position"] = event.joystickMove.position;
                        break;
                }

                case sf::Event::JoystickConnected:
                {
                        table["type"] = "joystick connected";
                        table["joystickId"] = event.joystickConnect.joystickId;
                        break;
                }

                case sf::Event::JoystickDisconnected:
                {
                        table["type"] = "joystick disconnected";
                        table["joystickId"] = event.joystickConnect.joystickId;
                        break;
                }

                case sf::Event::TouchBegan:
                {
                        table["type"] = "touch began";
                        table["finger"] = event.touch.finger;
                        table["x"] = event.touch.x;
                        table["y"] = event.touch.y;
                        break;
                }

                case sf::Event::TouchMoved:
                {
                        table["type"] = "touch moved";
                        table["finger"] = event.touch.finger;
                        table["x"] = event.touch.x;
                        table["y"] = event.touch.y;
                        break;
                }

                case sf::Event::TouchEnded:
                {
                        table["type"] = "touch ended";
                        table["finger"] = event.touch.finger;
                        table["x"] = event.touch.x;
                        table["y"] = event.touch.y;
                        break;
                }

                case sf::Event::SensorChanged:
                {
                        table["type"] = "sensor changed";
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


// Function wrappers

#define eventOccurred(FN, TN)                                           \
        inline static lua::Retval FN(lua::Context& context)             \
        {                                                               \
                context.requireArgs<lua::Table>(1);                     \
                return context.ret(context.args[0]["type"] == TN);      \
        }

eventOccurred(windowClosed, "closed")
eventOccurred(windowResized, "resized")
eventOccurred(windowLostFocus, "lost focus")
eventOccurred(windowGainedFocus, "gained focus")
eventOccurred(textEntered, "text entered")
eventOccurred(mouseWheelMoved, "mouse wheel moved")
eventOccurred(mouseWheelScrolled, "mouse wheel scrolled")
eventOccurred(mouseMoved, "mouse moved")
eventOccurred(mouseEntered, "mouse entered")
eventOccurred(mouseLeft, "mouse left")
eventOccurred(joystickConnected, "joystick connected")
eventOccurred(joystickDisconnected, "joystick disconnected")
eventOccurred(touchBegan, "touch began")
eventOccurred(touchMoved, "touch moved")
eventOccurred(touchEnded, "touch ended")
eventOccurred(sensorChanged, "sensor changed")

#undef eventOccurred


inline static lua::Retval keyPressed(lua::Context& context)
{
        bool pressed =
                context.args[0]["type"] == "key pressed" and
                context.args[0]["code"] == context.args[1];

        // Is the Ctrl, Alt, Shift, and/or System key pressed too?
        for (int i = 2, nArgs = context.args.size(); i < nArgs; ++i)
        {
                pressed = pressed and context.args[0][context.args[i]];
        }

        return context.ret(pressed);
}

inline static lua::Retval keyReleased(lua::Context& context)
{
        bool released =
                context.args[0]["type"] == "key released" and
                context.args[0]["code"] == context.args[1];

        // Was the Ctrl, Alt, Shift, and/or System key pressed too?
        for (int i = 2, nArgs = context.args.size(); i < nArgs; ++i)
        {
                released = released and context.args[0][context.args[i]];
        }

        return context.ret(released);
}

inline static lua::Retval mousePressed(lua::Context& context)
{
        context.requireArgs<lua::Table, int>(2);

        const bool pressed =
                context.args[0]["type"] == "mouse pressed" and
                context.args[0]["button"] == context.args[1];

        return context.ret(pressed);
}

inline static lua::Retval mouseReleased(lua::Context& context)
{
        context.requireArgs<lua::Table, int>(2);

        const bool released =
                context.args[0]["type"] == "mouse released" and
                context.args[0]["button"] == context.args[1];

        return context.ret(released);
}

inline static lua::Retval joystickPressed(lua::Context& context)
{
        context.requireArgs<lua::Table, int, int>(3);

        const bool pressed =
                context.args[0]["type"] == "joystick pressed"    and
                context.args[0]["joystickId"] == context.args[1] and
                context.args[0]["button"] == context.args[2];

        return context.ret(pressed);
}

inline static lua::Retval joystickReleased(lua::Context& context)
{
        context.requireArgs<lua::Table, int, int>(3);

        const bool released =
                context.args[0]["type"] == "joystick released"   and
                context.args[0]["joystickId"] == context.args[1] and
                context.args[0]["button"] == context.args[2];

        return context.ret(released);
}

}