#pragma once


#include <Script/Lua.hpp>

#include <Util/String.hpp>

#include <SFML/Window/Event.hpp>


namespace script
{

inline lua::Valset eventToHandlerArgs(const lua::Table& sceneObj, const sf::Event& event)
{
        auto args = lua::Valset{sceneObj};

        switch (event.type)
        {
                case sf::Event::Resized:
                {
                        args.push_back(event.size.width);
                        args.push_back(event.size.height);
                        break;
                }

                case sf::Event::TextEntered:
                {
                        args.push_back(event.text.unicode);
                        break;
                }

                case sf::Event::KeyPressed:
                {
                        args.push_back(event.key.code);
                        args.push_back(event.key.alt);
                        args.push_back(event.key.control);
                        args.push_back(event.key.shift);
                        args.push_back(event.key.system);
                        break;
                }

                case sf::Event::KeyReleased:
                {
                        args.push_back(event.key.code);
                        args.push_back(event.key.alt);
                        args.push_back(event.key.control);
                        args.push_back(event.key.shift);
                        args.push_back(event.key.system);
                        break;
                }

                case sf::Event::MouseWheelMoved:
                {
                        args.push_back(event.mouseWheel.delta);
                        args.push_back(event.mouseWheel.x);
                        args.push_back(event.mouseWheel.y);
                        break;
                }

                case sf::Event::MouseWheelScrolled:
                {
                        args.push_back(event.mouseWheelScroll.delta);
                        args.push_back(event.mouseWheelScroll.x);
                        args.push_back(event.mouseWheelScroll.y);
                        break;
                }

                case sf::Event::MouseButtonPressed:
                {
                        args.push_back(event.mouseButton.button);
                        args.push_back(event.mouseButton.x);
                        args.push_back(event.mouseButton.y);
                        break;
                }

                case sf::Event::MouseButtonReleased:
                {
                        args.push_back(event.mouseButton.button);
                        args.push_back(event.mouseButton.x);
                        args.push_back(event.mouseButton.y);
                        break;
                }

                case sf::Event::MouseMoved:
                {
                        args.push_back(event.mouseMove.x);
                        args.push_back(event.mouseMove.y);
                        break;
                }

                case sf::Event::JoystickButtonPressed:
                {
                        args.push_back(event.joystickButton.joystickId);
                        args.push_back(event.joystickButton.button);
                        break;
                }

                case sf::Event::JoystickButtonReleased:
                {
                        args.push_back(event.joystickButton.joystickId);
                        args.push_back(event.joystickButton.button);
                        break;
                }

                case sf::Event::JoystickMoved:
                {
                        args.push_back(event.joystickMove.joystickId);
                        args.push_back(event.joystickMove.axis);
                        args.push_back(event.joystickMove.position);
                        break;
                }

                case sf::Event::JoystickConnected:
                {
                        args.push_back(event.joystickConnect.joystickId);
                        break;
                }

                case sf::Event::JoystickDisconnected:
                {
                        args.push_back(event.joystickConnect.joystickId);
                        break;
                }

                case sf::Event::TouchBegan:
                {
                        args.push_back(event.touch.finger);
                        args.push_back(event.touch.x);
                        args.push_back(event.touch.y);
                        break;
                }

                case sf::Event::TouchMoved:
                {
                        args.push_back(event.touch.finger);
                        args.push_back(event.touch.x);
                        args.push_back(event.touch.y);
                        break;
                }

                case sf::Event::TouchEnded:
                {
                        args.push_back(event.touch.finger);
                        args.push_back(event.touch.x);
                        args.push_back(event.touch.y);
                        break;
                }

                case sf::Event::SensorChanged:
                {
                        args.push_back(event.sensor.type);
                        args.push_back(event.sensor.x);
                        args.push_back(event.sensor.y);
                        args.push_back(event.sensor.z);
                        break;
                }

                default: break;
        }

        return args;
}

}