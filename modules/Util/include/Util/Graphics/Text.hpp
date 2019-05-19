#pragma once


#include <Util/Graphics/Graphical.hpp>


namespace util::graphics
{

class Text : public Graphical, public sf::Text
{
public:

        Text()
        : sf::Text()
        {
        }

        Text(const sf::String& string, const sf::Font& font, const unsigned int characterSize = 30)
        : sf::Text(string, font, characterSize)
        {
        }

        virtual std::unique_ptr<Graphical> copy() const override
        {
                return std::make_unique<Text>(*this);
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::Text&>(*this), states);
        }
};

}