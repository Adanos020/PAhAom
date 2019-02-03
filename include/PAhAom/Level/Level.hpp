#pragma once


#include <PAhAom/Level/Generator.hpp>
#include <PAhAom/Level/GfxMap.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>


namespace PAhAom::Level
{

template<size_t width, size_t height>
class Level : public sf::Drawable, public sf::Transformable
{
public:

        Level<width, height>();
        Level<width, height>(Generator<width, height>&);
        Level<width, height>(std::string_view path);

public:

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

        GfxMap<width, height> map;
};

}