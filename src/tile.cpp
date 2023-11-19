#include "tile.h"
#include <sfml/Graphics/RectangleShape.hpp>

tile::tile(int x, int y, int width, int height, sf::Color color) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
}

void tile::setColor(sf::Color) {
    this->color = color;
}

sf::Color tile::getColor() {
    return this->color;
}

int tile::getX() {
    return this->x;
}

int tile::getY() {
    return this->y;
}

sf::RectangleShape tile::tileRectangle() {
    sf::RectangleShape tileRect;
    tileRect.setOutlineColor(sf::Color::Black);
    tileRect.setOutlineThickness(1);
    tileRect.setFillColor(this->color);
    tileRect.setPosition(this->x, this->y);
    sf::Vector2f size(this->width, this->height);
    tileRect.setSize(size);
    return tileRect;
}