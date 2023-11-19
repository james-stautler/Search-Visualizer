#include "tile.h"

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