#pragma once


#include <Util/Math.hpp>

#include <SFML/Graphics.hpp>

#include <memory>


namespace util::graphics
{

class Graphical : public sf::Drawable, public sf::Transformable
{
public:
        std::unique_ptr<Graphical> copy() const;
};

// Type redefinitions.

class CircleShape : public Graphical, public sf::CircleShape
{
public:
        CircleShape(const float radius = 0, const std::size_t pointCount = 30)
        : sf::CircleShape(radius, pointCount)
        {
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::CircleShape&>(*this), states);
        }
};

class ConvexShape : public Graphical, public sf::ConvexShape
{
public:
        ConvexShape(const std::size_t pointCount = 0)
        : sf::ConvexShape(pointCount)
        {
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::ConvexShape&>(*this), states);
        }
};

class RectangleShape : public Graphical, public sf::RectangleShape
{
public:
        RectangleShape(const Vector size = {0, 0})
        : sf::RectangleShape(size)
        {
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::RectangleShape&>(*this), states);
        }
};

class Sprite : public Graphical, public sf::Sprite
{
public:
        Sprite()
        : sf::Sprite()
        {
        }

        Sprite(const sf::Texture& texture)
        : sf::Sprite(texture)
        {
        }

        Sprite(const sf::Texture& texture, const sf::IntRect& rectangle)
        : sf::Sprite(texture, rectangle)
        {
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::Sprite&>(*this), states);
        }
};

class Text : public Graphical, public sf::Text
{
public:
        Text()
        : sf::Text()
        {
        }

        Text(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30)
        : sf::Text(string, font, characterSize)
        {
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::Text&>(*this), states);
        }
};

}