#pragma once

#include <Util/Math.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstdint>

namespace util::graphics
{

using TileID = int32_t;

class RectTileMap : public sf::Drawable, public sf::Transformable
{
public: // Constructors.

        RectTileMap(const sf::Vector2u size = {0, 0},
                    const sf::Vector2f tileSize = {0, 0},
                    const sf::Vector2u tileIconSize = {0, 0},
                    sf::Texture* const texture = nullptr,
                    const TileID fill = 0);
        RectTileMap(const Matrix<TileID>& tiles,
                    const sf::Vector2f tileSize = {0, 0},
                    const sf::Vector2u tileIconSize = {0, 0},
                    sf::Texture* const texture = nullptr);
        RectTileMap(const RectTileMap& other);
        RectTileMap(RectTileMap&& other);

public: // Mutators.

        void fill(const TileID fill);
        void fillArea(const TileID fill, const sf::UintRect area);
        void setTile(const sf::Vector2u pos, const TileID iconIndex);
        void setMap(const Matrix<TileID>& tiles);
        void setTexture(sf::Texture* const texture);
        void setTileSize(const sf::Vector2f tileSize);
        void setTileIconSize(const sf::Vector2u tileIconSize);

public: // Accessors.
        sf::Texture* getTexture() const;
        TileID getTile(const sf::Vector2u pos) const;
        TileID getTile(const std::size_t row, const std::size_t col) const;
        sf::Vector2u getSize() const;
        sf::Vector2f getTileSize() const;
        sf::Vector2u getTileIconSize() const;
        sf::FloatRect getGlobalBounds() const;
        sf::FloatRect getLocalBounds() const;

public: // Overloaded operators.
        RectTileMap& operator=(const RectTileMap& other);
        RectTileMap& operator=(RectTileMap&& other);

public: // Derived interface.
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private: // Helper functions.
        void placeVertices();

private: // Fields.
        sf::Vector2u size;
        sf::Vector2f tileSize;
        sf::Vector2u tileIconSize;

        Matrix<TileID> tiles;
        sf::VertexArray vertices;
        class sf::Texture* texture;
};

}
