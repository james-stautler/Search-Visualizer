#include "tileCollection.h"

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 800;
int OFFSET = 200;

tileCollection::tileCollection(int tileSize) {
    if ((SCREEN_WIDTH - OFFSET) % tileSize != 0 || SCREEN_HEIGHT % tileSize != 0) {
        printf("Invalid tile size, screen height and size must be divisible by tile size.");
        return;
    }
    for (int y = 0; y < SCREEN_HEIGHT; y += tileSize) {
        std::vector<tile*> rowTiles;
        for (int x = OFFSET; x < SCREEN_WIDTH; x += tileSize) {
            tile* newTile = new tile(x, y, tileSize, tileSize, sf::Color::White);
            rowTiles.push_back(newTile);
        }
        tiles.push_back(rowTiles);
    }
}

std::vector<std::vector<tile*> > tileCollection::getTiles() {
    return this->tiles;
}

tile* tileCollection::tileInCoordinate(int x, int y, int tileSize) {
    tile* tile;
    int row = floor((x - 200) / tileSize);
    int col = floor(y / tileSize); 
    return tiles.at(row).at(col);
}