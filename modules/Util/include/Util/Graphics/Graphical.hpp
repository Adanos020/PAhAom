#pragma once


#include <Util/Math.hpp>

#include <SFML/Graphics.hpp>

#include <memory>


namespace util::graphics
{

using GraphicalTypeID = unsigned int;
static constexpr std::size_t MAX_GRAPHICALS = 32;

class Graphical : public sf::Drawable, public sf::Transformable
{
public:

        std::unique_ptr<Graphical> copy() const;

private:

        GraphicalTypeID typeID;
};

inline GraphicalTypeID getGraphicalTypeID()
{
        static GraphicalTypeID id = 0;
        return id++;
}

template<class GraphClass>
inline GraphicalTypeID getGraphicalTypeID() noexcept
{
        static_assert(std::is_base_of_v<Graphical, GraphClass>);
        static const GraphicalTypeID id = getGraphicalTypeID();
        return id;
}

}