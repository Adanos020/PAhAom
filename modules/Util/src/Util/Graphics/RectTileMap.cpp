#include <Util/Graphics/RectTileMap.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace util::graphics
{

RectTileMap::RectTileMap(
        const sf::Vector2u size,
        const sf::Vector2f tileSize,
        const sf::Vector2u tileIconSize,
        sf::Texture* const texture,
        const TileID fill
)
        : size(size)
        , tileSize(tileSize)
        , tileIconSize(tileIconSize)
        , tiles(size.y, size.x)
        , vertices(sf::Quads)
        , texture(texture)
{
        this->placeVertices();
        this->fill(fill);
}

RectTileMap::RectTileMap(
        const Matrix<TileID>& tiles,
        const sf::Vector2f tileSize,
        const sf::Vector2u tileIconSize,
        sf::Texture* const texture
)
        : RectTileMap(sf::Vector2u(tiles.columns(), tiles.rows()), tileSize, tileIconSize, texture)
{
        this->setMap(tiles);
}

RectTileMap::RectTileMap(const RectTileMap& other)
        : size        (other.size)
        , tileSize    (other.tileSize)
        , tileIconSize(other.tileIconSize)
        , tiles       (other.tiles)
        , vertices    (other.vertices)
        , texture     (other.texture)
{
}

RectTileMap::RectTileMap(RectTileMap&& other)
        : size        (std::move(other.size))
        , tileSize    (std::move(other.tileSize))
        , tileIconSize(std::move(other.tileIconSize))
        , tiles       (std::move(other.tiles))
        , vertices    (std::move(other.vertices))
        , texture     (std::move(other.texture))
{
}

void RectTileMap::fill(const TileID fill)
{
        this->fillArea(fill, {{}, this->size});
}

void RectTileMap::fillArea(const TileID fill, const sf::UintRect area)
{
        for (uint32_t y = area.top; y < area.height; ++y)
        for (uint32_t x = area.left; x < area.width; ++x)
        {
                this->setTile({x, y}, fill);
        }
}

void RectTileMap::setTile(const sf::Vector2u pos, const TileID iconIndex)
{
        this->tiles.set(pos.y, pos.x, iconIndex);

        const std::size_t vertex = 4 * (pos.x + pos.y * this->size.x);

        const auto iconSize = sf::Vector2f(this->tileIconSize);
        const std::size_t texWidth = this->texture->getSize().x;
        const sf::Vector2f texCoords = {
                iconIndex % (texWidth / this->tileIconSize.x) * iconSize.x,
                iconIndex / (texWidth / this->tileIconSize.x) * iconSize.y,
        };

        const sf::Vector2f topLeft     = {0,          0};
        const sf::Vector2f topRight    = {iconSize.x, 0};
        const sf::Vector2f bottomRight = {iconSize.x, iconSize.y};
        const sf::Vector2f bottomLeft  = {0,          iconSize.y};

        this->vertices[vertex + 0].texCoords = texCoords + topLeft;
        this->vertices[vertex + 1].texCoords = texCoords + topRight;
        this->vertices[vertex + 2].texCoords = texCoords + bottomRight;
        this->vertices[vertex + 3].texCoords = texCoords + bottomLeft;
}

void RectTileMap::setMap(const Matrix<TileID>& tiles)
{
        this->tiles = tiles;
        this->size.x = tiles.columns();
        this->size.y = tiles.rows();

        this->placeVertices();

        for (uint32_t y = 0; y < this->size.y; ++y)
        for (uint32_t x = 0; x < this->size.x; ++x)
        {
                this->setTile({x, y}, tiles.get(y, x));
        }
}

void RectTileMap::setTexture(sf::Texture* const texture)
{
        this->texture = texture;
}

void RectTileMap::setTileSize(const sf::Vector2f tileSize)
{
        this->tileSize = tileSize;
}

void RectTileMap::setTileIconSize(const sf::Vector2u tileIconSize)
{
        this->tileIconSize = tileIconSize;
}

sf::Texture* RectTileMap::getTexture() const
{
        return this->texture;
}

TileID RectTileMap::getTile(const sf::Vector2u pos) const
{
        return this->tiles.get(pos.y, pos.x);
}

TileID RectTileMap::getTile(const std::size_t row, const std::size_t col) const
{
        return this->tiles.get(col, row);
}

sf::Vector2u RectTileMap::getSize() const
{
        return this->size;
}

sf::Vector2f RectTileMap::getTileSize() const
{
        return this->tileSize;
}

sf::Vector2u RectTileMap::getTileIconSize() const
{
        return this->tileIconSize;
}

sf::FloatRect RectTileMap::getGlobalBounds() const
{
        return {this->getPosition(),
                {this->size.x * this->tileSize.x,
                        this->size.y * this->tileSize.y}};
}

sf::FloatRect RectTileMap::getLocalBounds() const
{
        return {0.f, 0.f,
                this->size.x * this->tileSize.x,
                this->size.y * this->tileSize.y};
}

RectTileMap& RectTileMap::operator=(const RectTileMap& other)
{
        this->size         = other.size;
        this->tileSize     = other.tileSize;
        this->tileIconSize = other.tileIconSize;
        this->tiles        = other.tiles;
        this->vertices     = other.vertices;
        this->texture      = other.texture;
        return *this;
}

RectTileMap& RectTileMap::operator=(RectTileMap&& other)
{
        this->size         = std::move(other.size);
        this->tileSize     = std::move(other.tileSize);
        this->tileIconSize = std::move(other.tileIconSize);
        this->tiles        = std::move(other.tiles);
        this->vertices     = std::move(other.vertices);
        this->texture      = std::move(other.texture);
        return *this;
}

void RectTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        states.transform *= this->getTransform();
        states.texture = this->texture;
        target.draw(vertices, states);
}

void RectTileMap::placeVertices()
{
        this->vertices.resize(4 * this->size.x * this->size.y);

        // Vertices of a tile.
        const sf::Vector2f topLeft     = {0,                0};
        const sf::Vector2f topRight    = {this->tileSize.x, 0};
        const sf::Vector2f bottomRight = {this->tileSize.x, this->tileSize.y};
        const sf::Vector2f bottomLeft  = {0,                this->tileSize.y};

        for (std::size_t x = 0; x < this->size.x; ++x)
        for (std::size_t y = 0; y < this->size.y; ++y)
        {
                const std::size_t firstVertex = 4 * (x + y * this->size.x);
                const sf::Vector2f position = {
                        x * this->tileSize.x,
                        y * this->tileSize.y,
                };
                this->vertices[firstVertex + 0].position = position + topLeft;
                this->vertices[firstVertex + 1].position = position + topRight;
                this->vertices[firstVertex + 2].position = position + bottomRight;
                this->vertices[firstVertex + 3].position = position + bottomLeft;
        }
}

}
