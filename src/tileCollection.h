#ifndef TILE_COLLECTION_H
#define TILE_COLLECTION_H

#include "tile.h"


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
};

#endif 