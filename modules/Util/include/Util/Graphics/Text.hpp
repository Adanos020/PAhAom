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