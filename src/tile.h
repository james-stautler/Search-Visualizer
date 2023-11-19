#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class tile {

    private:
        int x;
        int y;
        int width;
        int height;
        sf::Color color;
    
    public:
        tile(int x, int y, int width, int height, sf::Color color);

        sf::Color getColor();
        int getX();
        int getY();

        void setColor(sf::Color color);
        sf::RectangleShape tileRectangle();

};

#endif