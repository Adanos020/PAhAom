#include "gui.h"

namespace rr {

    Image::Image(sf::Vector2f pos, int iconSize, std::string path, unsigned index) {
        icn = iconSize;
        skin.loadFromFile(path);

        body.setPrimitiveType(sf::Quads);
        body.resize(4);

        unsigned tu = index%(skin.getSize().x/icn);
        unsigned tv = index/(skin.getSize().x/icn);

        body[0].position = pos;
        body[1].position = sf::Vector2f(pos.x+icn, pos.y);
        body[2].position = sf::Vector2f(pos.x+icn, pos.y+icn);
        body[3].position = sf::Vector2f(pos.x, pos.y+icn);

        body[0].texCoords = sf::Vector2f(tu*icn, tv*icn);
        body[1].texCoords = sf::Vector2f((tu+1)*icn, tv*icn);
        body[2].texCoords = sf::Vector2f((tu+1)*icn, (tv+1)*icn);
        body[3].texCoords = sf::Vector2f(tu*icn, (tv+1)*icn);
    }

    Image::~Image() {}

    sf::Texture Image::getSkin() {
        return skin;
    }

    sf::VertexArray Image::getBody() {
        return body;
    }
    void Image::change(unsigned index) {
        unsigned tu = index%(skin.getSize().x/icn);
        unsigned tv = index/(skin.getSize().x/icn);

        body[0].texCoords = sf::Vector2f(tu*icn, tv*icn);
        body[1].texCoords = sf::Vector2f((tu+1)*icn, tv*icn);
        body[2].texCoords = sf::Vector2f((tu+1)*icn, (tv+1)*icn);
        body[3].texCoords = sf::Vector2f(tu*icn, (tv+1)*icn);
    }

    void Image::change(sf::VertexArray va, sf::Texture tx) {
        body = va;
        skin = tx;
    }

    void Image::scale(sf::Vector2f v) {
        for (unsigned i=1; i<4; i++) {
            body[i].position.x *= v.x;
            body[i].position.y *= v.y;
        }
    }

    void Image::paint(sf::Color c) {
        for (unsigned i=0; i<4; i++)
            body[i].color = c;
    }

    void Image::setPosition(sf::Vector2f pos) {
        body[0].position = pos;
        body[1].position = pos+sf::Vector2f(icn*5, 0);
        body[2].position = pos+sf::Vector2f(icn*5, icn*5);
        body[3].position = pos+sf::Vector2f(0, icn*5);
    }

    void Image::setSize(sf::Vector2f s) {
        body[1].position = sf::Vector2f(body[0].position.x+s.x, body[0].position.y);
        body[2].position = sf::Vector2f(body[0].position.x+s.x, body[0].position.y+s.y);
        body[3].position = sf::Vector2f(body[0].position.x, body[0].position.y+s.y);
    }

    sf::Vector2f Image::getPosition() {
        return body[0].position;
    }

    sf::Vector2f Image::getSize() {
        return sf::Vector2f(body[1].position.x-body[0].position.x, body[2].position.y-body[1].position.y);
    }

    void Image::draw(sf::RenderWindow& rw) {
        rw.draw(body, &skin);
    }
}
