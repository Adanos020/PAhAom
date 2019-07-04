#pragma once


#include <Engine/Settings.hpp>

#include <Script/Lua.hpp>

#include <Util/String.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>


namespace script
{

static constexpr util::CStr EVENT_HANDLERS[sf::Event::Count] = {
        "onClosed",
        "onResized",
        "onLostFocus",
        "onGainedFocus",
        "onTextEntered",
        "onKeyPressed",
        "onKeyReleased",
        "onMouseWheelMoved",
        "onMouseWheelScrolled",
        "onMousePressed",
        "onMouseReleased",
        "onMouseMoved",
        "onMouseEntered",
        "onMouseLeft",
        "onJoystickPressed",
        "onJoystickReleased",
        "onJoystickMoved",
        "onJoystickConnected",
        "onJoystickDisconnected",
        "onTouchBegan",
        "onTouchMoved",
        "onTouchEnded",
        "onSensorChanged",
};

inline static void callInputHandler(sol::table obj, sol::table handlers, sf::Event event)
{
        if (handlers[EVENT_HANDLERS[event.type]].get_type() != sol::type::function)
        {
                return;
        }

        const sf::Vector2f rsRatio = engine::Settings::Video::resolutionSizeRatio();

        sol::function handler = handlers[EVENT_HANDLERS[event.type]];
        switch (event.type)
        {
                case sf::Event::Resized:
                {
                        handler(obj,
                                event.size.width,
                                event.size.height);
                        break;
                }

                case sf::Event::TextEntered:
                {
                        handler(obj,
                                event.text.unicode);
                        break;
                }

                case sf::Event::KeyPressed:
                {
                        handler(obj,
                                event.key.code,
                                event.key.alt,
                                event.key.control,
                                event.key.shift,
                                event.key.system);
                        break;
                }

                case sf::Event::KeyReleased:
                {
                        handler(obj,
                                event.key.code,
                                event.key.alt,
                                event.key.control,
                                event.key.shift,
                                event.key.system);
                        break;
                }

                case sf::Event::MouseWheelMoved:
                {
                        handler(obj,
                                event.mouseWheel.delta,
                                event.mouseWheel.x * rsRatio.x,
                                event.mouseWheel.y * rsRatio.y);
                        break;
                }

                case sf::Event::MouseWheelScrolled:
                {
                        handler(obj,
                                event.mouseWheelScroll.delta,
                                event.mouseWheelScroll.x * rsRatio.x,
                                event.mouseWheelScroll.y * rsRatio.y);
                        break;
                }

                case sf::Event::MouseButtonPressed:
                {
                        handler(obj,
                                event.mouseButton.button,
                                event.mouseButton.x * rsRatio.x,
                                event.mouseButton.y * rsRatio.y);
                        break;
                }

                case sf::Event::MouseButtonReleased:
                {
                        handler(obj,
                                event.mouseButton.button,
                                event.mouseButton.x * rsRatio.x,
                                event.mouseButton.y * rsRatio.y);
                        break;
                }

                case sf::Event::MouseMoved:
                {
                        handler(obj,
                                event.mouseMove.x * rsRatio.x,
                                event.mouseMove.y * rsRatio.y);
                        break;
                }

                case sf::Event::JoystickButtonPressed:
                {
                        handler(obj,
                                event.joystickButton.joystickId,
                                event.joystickButton.button);
                        break;
                }

                case sf::Event::JoystickButtonReleased:
                {
                        handler(obj,
                                event.joystickButton.joystickId,
                                event.joystickButton.button);
                        break;
                }

                case sf::Event::JoystickMoved:
                {
                        handler(obj,
                                event.joystickMove.joystickId,
                                event.joystickMove.axis,
                                event.joystickMove.position);
                        break;
                }

                case sf::Event::JoystickConnected:
                {
                        handler(obj,
                                event.joystickConnect.joystickId);
                        break;
                }

                case sf::Event::JoystickDisconnected:
                {
                        handler(obj,
                                event.joystickConnect.joystickId);
                        break;
                }

                case sf::Event::TouchBegan:
                {
                        handler(obj,
                                event.touch.finger,
                                event.touch.x * rsRatio.x,
                                event.touch.y * rsRatio.y);
                        break;
                }

                case sf::Event::TouchMoved:
                {
                        handler(obj,
                                event.touch.finger,
                                event.touch.x * rsRatio.x,
                                event.touch.y * rsRatio.y);
                        break;
                }

                case sf::Event::TouchEnded:
                {
                        handler(obj,
                                event.touch.finger,
                                event.touch.x * rsRatio.x,
                                event.touch.y * rsRatio.y);
                        break;
                }

                case sf::Event::SensorChanged:
                {
                        handler(obj,
                                event.sensor.type,
                                event.sensor.x,
                                event.sensor.y,
                                event.sensor.z);
                        break;
                }

                default: break;
        }
}

inline static void loadInput(sf::Window& window [[maybe_unused]])
{
        // Joystick
        lua.create_named_table("joystick",
                "axisX",        sf::Joystick::X,
                "axisY",        sf::Joystick::Y,
                "axisZ",        sf::Joystick::Z,
                "axisR",        sf::Joystick::R,
                "axisU",        sf::Joystick::U,
                "axisV",        sf::Joystick::V,
                "axisPovX",     sf::Joystick::PovX,
                "axisPovY",     sf::Joystick::PovY,
                "axisCount",    sf::Joystick::AxisCount,
                "buttonCount",  sf::Joystick::ButtonCount,
                "count",        sf::Joystick::Count,
                "isConnected",  sf::Joystick::isConnected,
                "isPressed",    sf::Joystick::isButtonPressed,
                "buttonCount",  sf::Joystick::getButtonCount,
                "axisPosition", sf::Joystick::getAxisPosition,
                "info",         sf::Joystick::getIdentification,
                "update",       sf::Joystick::update);

        // Keyboard
        lua.create_named_table("keyboard",
                "unknown",   sf::Keyboard::Unknown,
                "a",         sf::Keyboard::A,
                "b",         sf::Keyboard::B,
                "c",         sf::Keyboard::C,
                "d",         sf::Keyboard::D,
                "e",         sf::Keyboard::E,
                "f",         sf::Keyboard::F,
                "g",         sf::Keyboard::G,
                "h",         sf::Keyboard::H,
                "i",         sf::Keyboard::I,
                "j",         sf::Keyboard::J,
                "k",         sf::Keyboard::K,
                "l",         sf::Keyboard::L,
                "m",         sf::Keyboard::M,
                "n",         sf::Keyboard::N,
                "o",         sf::Keyboard::O,
                "p",         sf::Keyboard::P,
                "q",         sf::Keyboard::Q,
                "r",         sf::Keyboard::R,
                "s",         sf::Keyboard::S,
                "t",         sf::Keyboard::T,
                "u",         sf::Keyboard::U,
                "v",         sf::Keyboard::V,
                "w",         sf::Keyboard::W,
                "x",         sf::Keyboard::X,
                "y",         sf::Keyboard::Y,
                "z",         sf::Keyboard::Z,
                "num0",      sf::Keyboard::Num0,
                "num1",      sf::Keyboard::Num1,
                "num2",      sf::Keyboard::Num2,
                "num3",      sf::Keyboard::Num3,
                "num4",      sf::Keyboard::Num4,
                "num5",      sf::Keyboard::Num5,
                "num6",      sf::Keyboard::Num6,
                "num7",      sf::Keyboard::Num7,
                "num8",      sf::Keyboard::Num8,
                "num9",      sf::Keyboard::Num9,
                "escape",    sf::Keyboard::Escape,
                "lControl",  sf::Keyboard::LControl,
                "lShift",    sf::Keyboard::LShift,
                "lAlt",      sf::Keyboard::LAlt,
                "lSystem",   sf::Keyboard::LSystem,
                "rControl",  sf::Keyboard::RControl,
                "rShift",    sf::Keyboard::RShift,
                "rAlt",      sf::Keyboard::RAlt,
                "rSystem",   sf::Keyboard::RSystem,
                "menu",      sf::Keyboard::Menu,
                "lBracket",  sf::Keyboard::LBracket,
                "rBracket",  sf::Keyboard::RBracket,
                "semicolon", sf::Keyboard::Semicolon,
                "comma",     sf::Keyboard::Comma,
                "period",    sf::Keyboard::Period,
                "quote",     sf::Keyboard::Quote,
                "slash",     sf::Keyboard::Slash,
                "backslash", sf::Keyboard::Backslash,
                "tilde",     sf::Keyboard::Tilde,
                "equal",     sf::Keyboard::Equal,
                "hyphen",    sf::Keyboard::Hyphen,
                "space",     sf::Keyboard::Space,
                "enter",     sf::Keyboard::Enter,
                "backspace", sf::Keyboard::Backspace,
                "tab",       sf::Keyboard::Tab,
                "pageUp",    sf::Keyboard::PageUp,
                "pageDown",  sf::Keyboard::PageDown,
                "end",       sf::Keyboard::End,
                "home",      sf::Keyboard::Home,
                "insert",    sf::Keyboard::Insert,
                "delete",    sf::Keyboard::Delete,
                "add",       sf::Keyboard::Add,
                "subtract",  sf::Keyboard::Subtract,
                "multiply",  sf::Keyboard::Multiply,
                "divide",    sf::Keyboard::Divide,
                "left",      sf::Keyboard::Left,
                "right",     sf::Keyboard::Right,
                "up",        sf::Keyboard::Up,
                "down",      sf::Keyboard::Down,
                "numpad0",   sf::Keyboard::Numpad0,
                "numpad1",   sf::Keyboard::Numpad1,
                "numpad2",   sf::Keyboard::Numpad2,
                "numpad3",   sf::Keyboard::Numpad3,
                "numpad4",   sf::Keyboard::Numpad4,
                "numpad5",   sf::Keyboard::Numpad5,
                "numpad6",   sf::Keyboard::Numpad6,
                "numpad7",   sf::Keyboard::Numpad7,
                "numpad8",   sf::Keyboard::Numpad8,
                "numpad9",   sf::Keyboard::Numpad9,
                "f1",        sf::Keyboard::F1,
                "f2",        sf::Keyboard::F2,
                "f3",        sf::Keyboard::F3,
                "f4",        sf::Keyboard::F4,
                "f5",        sf::Keyboard::F5,
                "f6",        sf::Keyboard::F6,
                "f7",        sf::Keyboard::F7,
                "f8",        sf::Keyboard::F8,
                "f9",        sf::Keyboard::F9,
                "f10",       sf::Keyboard::F10,
                "f11",       sf::Keyboard::F11,
                "f12",       sf::Keyboard::F12,
                "f13",       sf::Keyboard::F13,
                "f14",       sf::Keyboard::F14,
                "f15",       sf::Keyboard::F15,
                "pause",     sf::Keyboard::Pause,
                "keyCount",  sf::Keyboard::KeyCount,
                "isPressed", sf::Keyboard::isKeyPressed);

        // Mouse
        lua.create_named_table("mouse",
                "left",            sf::Mouse::Left,
                "right",           sf::Mouse::Right,
                "middle",          sf::Mouse::Middle,
                "x1",              sf::Mouse::XButton1,
                "x2",              sf::Mouse::XButton2,
                "buttonCount",     sf::Mouse::ButtonCount,
                "verticalWheel",   sf::Mouse::VerticalWheel,
                "horizontalWheel", sf::Mouse::HorizontalWheel,
                "isPressed",       sf::Mouse::isButtonPressed,

                "position", sol::property(
                        [] { return sf::Mouse::getPosition(); },
                        [] (const sf::Vector2i pos) { sf::Mouse::setPosition(pos); }),
                "positionInWindow", sol::property(
                        [&] { return sf::Mouse::getPosition(window); },
                        [&] (const sf::Vector2i pos) { sf::Mouse::setPosition(pos, window); }));
}

}