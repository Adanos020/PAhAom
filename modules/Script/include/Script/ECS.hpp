#pragma once

#include <Script/Lua.hpp>
#include <Script/Math.hpp>

#include <SFML/System/Vector2.hpp>

namespace script
{

// Transform

void setPosition(sol::table entity, sf::Vector2f position);
void moveBy(sol::table entity, sf::Vector2f displacement);
void setRotation(sol::table entity, const float rotation);
void rotateBy(sol::table entity, const float rotation);
void setScale(sol::table entity, const sf::Vector2f scale);
void setScale(sol::table entity, const float scale);
void scaleBy(sol::table entity, const sf::Vector2f scale);
void scaleBy(sol::table entity, const float scale);

// Physics

void setVelocity(sol::table entity, const sf::Vector2f velocity);
void accelerateBy(sol::table entity, const sf::Vector2f acceleration);
void setMass(sol::table entity, const float mass);

// General

void addEntity(sol::table entity);
void loadECS();

}
