#ifndef TILE_COLLECTION_H
#define TILE_COLLECTION_H

#include <SFML/Graphics.hpp>
#include "tile.h"
#include <vector>


class tileCollection {
    private:
        std::vector<std::vector<tile*> > tiles;

    public:
        tileCollection(int tileSize);
        std::vector<std::vector<tile*> > getTiles();
        tile* tileInCoordinate(int x, int y, int tileSize); 
        void randomize(int threshold);
        void clear();
        void clearBlockers();
        void drawTiles(sf::RenderWindow& window);
        std::vector<tile*> getNeighbors(tile* currTile, int tileSize, int screenWidth, int screenHeight);
};

#endif 