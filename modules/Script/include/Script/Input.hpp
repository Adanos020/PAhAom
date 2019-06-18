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
                        args.push_back(event.size.width, event.size.height);
                        break;
                }

                case sf::Event::TextEntered:
                {
                        args.push_back(event.text.unicode);
                        break;
                }

                case sf::Event::KeyPressed:
                {
                        args.push_back(
                                event.key.code,
                                event.key.alt,
                                event.key.control,
                                event.key.shift,
                                event.key.system);
                        break;
                }

                case sf::Event::KeyReleased:
                {
                        args.push_back(
                                event.key.code,
                                event.key.alt,
                                event.key.control,
                                event.key.shift,
                                event.key.system);
                        break;
                }

                case sf::Event::MouseWheelMoved:
                {
                        args.push_back(
                                event.mouseWheel.delta,
                                event.mouseWheel.x,
                                event.mouseWheel.y);
                        break;
                }

                case sf::Event::MouseWheelScrolled:
                {
                        args.push_back(
                                event.mouseWheelScroll.delta,
                                event.mouseWheelScroll.x,
                                event.mouseWheelScroll.y);
                        break;
                }

                case sf::Event::MouseButtonPressed:
                {
                        args.push_back(
                                event.mouseButton.button,
                                event.mouseButton.x,
                                event.mouseButton.y);
                        break;
                }

                case sf::Event::MouseButtonReleased:
                {
                        args.push_back(
                                event.mouseButton.button,
                                event.mouseButton.x,
                                event.mouseButton.y);
                        break;
                }

                case sf::Event::MouseMoved:
                {
                        args.push_back(event.mouseMove.x, event.mouseMove.y);
                        break;
                }

                case sf::Event::JoystickButtonPressed:
                {
                        args.push_back(event.joystickButton.joystickId, event.joystickButton.button);
                        break;
                }

                case sf::Event::JoystickButtonReleased:
                {
                        args.push_back(event.joystickButton.joystickId, event.joystickButton.button);
                        break;
                }

                case sf::Event::JoystickMoved:
                {
                        args.push_back(
                                event.joystickMove.joystickId,
                                event.joystickMove.axis,
                                event.joystickMove.position);
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
                        args.push_back(
                                event.touch.finger,
                                event.touch.x,
                                event.touch.y);
                        break;
                }

                case sf::Event::TouchMoved:
                {
                        args.push_back(
                                event.touch.finger,
                                event.touch.x,
                                event.touch.y);
                        break;
                }

                case sf::Event::TouchEnded:
                {
                        args.push_back(
                                event.touch.finger,
                                event.touch.x,
                                event.touch.y);
                        break;
                }

                case sf::Event::SensorChanged:
                {
                        args.push_back(
                                event.sensor.type,
                                event.sensor.x,
                                event.sensor.y,
                                event.sensor.z);
                        break;
                }

                default: break;
        }

        return args;
}

}