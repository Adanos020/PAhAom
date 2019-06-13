#pragma once


#include <Script/Aux.hpp>
#include <Script/ECS.hpp>
#include <Script/Graphics.hpp>
#include <Script/Input.hpp>
#include <Script/Math.hpp>
#include <Script/Random.hpp>
#include <Script/Resources.hpp>
#include <Script/Scenes.hpp>


namespace script
{

inline static void init()
{
        // ECS
        luaContext.global["set_position"] = setPosition;
        luaContext.global["set_rotation"] = setRotation;
        luaContext.global["set_scale"]    = setScale;

        // Input
        luaContext.global["window_closed"]         = windowClosed;
        luaContext.global["window_resized"]        = windowResized;
        luaContext.global["window_lost_focus"]     = windowLostFocus;
        luaContext.global["window_gained_focus"]   = windowGainedFocus;
        luaContext.global["text_entered"]          = textEntered;
        luaContext.global["mouse_wheel_moved"]     = mouseWheelMoved;
        luaContext.global["mouse_wheel_scrolled"]  = mouseWheelScrolled;
        luaContext.global["mouse_moved"]           = mouseMoved;
        luaContext.global["mouse_entered"]         = mouseEntered;
        luaContext.global["mouse_left"]            = mouseLeft;
        luaContext.global["joystick_connected"]    = joystickConnected;
        luaContext.global["joystick_disconnected"] = joystickDisconnected;
        luaContext.global["touch_began"]           = touchBegan;
        luaContext.global["touch_moved"]           = touchMoved;
        luaContext.global["touch_ended"]           = touchEnded;
        luaContext.global["sensorChanged"]         = sensorChanged;
        luaContext.global["key_pressed"]           = keyPressed;
        luaContext.global["key_released"]          = keyReleased;
        luaContext.global["mouse_pressed"]         = mousePressed;
        luaContext.global["mouse_released"]        = mouseReleased;
        luaContext.global["joystick_pressed"]      = joystickPressed;
        luaContext.global["joystick_released"]     = joystickReleased;

        // Math
        lua::Table math = luaContext.global["math"];
        math["clamp"]     = clamp;
        math["lerp"]      = numberLerp;
        math["normalize"] = numberNormalize;
        math["map"]       = numberMap;
        
        math["is_vector"]              = isVector;
        math["vector_equal"]           = vectorEquals;
        math["vector_add"]             = vectorAdd;
        math["vector_subtract"]        = vectorSubtract;
        math["vector_multiply"]        = vectorMultiply;
        math["vector_divide"]          = vectorDivide;
        math["vector_inverse"]         = vectorInverse;
        math["vector_length_squared"]  = vectorLengthSquared;
        math["vector_length"]          = vectorLength;
        math["vector_set_length"]      = vectorSetLength;
        math["vector_limit"]           = vectorLimit;
        math["vector_normalize"]       = vectorNormalize;
        math["vector_clamp_to_area"]   = vectorClampToArea;
        math["vector_clamp_to_length"] = vectorClampToLength;
        math["vector_from_polar"]      = vectorFromPolar;
        math["vector_dot"]             = vectorDot;
        math["vector_angle_between"]   = vectorAngleBetween;
        math["vector_lerp"]            = vectorLerp;
        
        math["is_rectangle"]         = isRectangle;
        math["rectangle_contains"]   = rectangleContains;
        math["rectangle_intersects"] = rectangleIntersects;

        // Resources
        luaContext.global["load_font"]    = load<sf::Font>;
        luaContext.global["load_texture"] = load<sf::Texture>;

        // Random
        lua::Table random{luaContext};
        random["chance"]  = chance;
        random["uniform"] = uniform;
        random["normal"]  = normal;
        luaContext.global["random"] = random;

        // Scenes
        luaContext.global["pop_scene"]  = popScene;
        luaContext.global["push_scene"] = pushScene;

        luaState.runFile("data/scripts/init.lua");
}

}