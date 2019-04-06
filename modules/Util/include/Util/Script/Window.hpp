#pragma once


#include <Util/Script/Script.hpp>

#include <SFML/Window/Event.hpp>


namespace util::script
{

inline lua::Table eventToTable(const sf::Event& event)
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

}