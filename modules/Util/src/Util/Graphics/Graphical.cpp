#include <Util/Graphics.hpp>


namespace util::graphics
{

std::unique_ptr<Graphical> Graphical::copy() const
{
        if (this->typeID == getGraphicalTypeID<CircleShape>())
        {
                return std::make_unique<CircleShape>(
                        reinterpret_cast<const CircleShape&>(*this));
        }
        if (this->typeID == getGraphicalTypeID<ConvexShape>())
        {
                return std::make_unique<ConvexShape>(
                        reinterpret_cast<const ConvexShape&>(*this));
        }
        if (this->typeID == getGraphicalTypeID<RectangleShape>())
        {
                return std::make_unique<RectangleShape>(
                        reinterpret_cast<const RectangleShape&>(*this));
        }
        if (this->typeID == getGraphicalTypeID<RectTileMap>())
        {
                return std::make_unique<RectTileMap>(
                        reinterpret_cast<const RectTileMap&>(*this));
        }
        if (this->typeID == getGraphicalTypeID<Sprite>())
        {
                return std::make_unique<Sprite>(
                        reinterpret_cast<const Sprite&>(*this));
        }
        if (this->typeID == getGraphicalTypeID<Text>())
        {
                return std::make_unique<Text>(
                        reinterpret_cast<const Text&>(*this));
        }
        return nullptr;
}

}