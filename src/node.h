#ifndef NODE
#define NODE

#include <vector>
#include "tile.h"

class node {

    private:
        tile* nodeTile;
        tile* goalTile;
        node* parent;
        int f;
        int g;
        
    public:
        node(tile* nodeTile, tile* goalTile);
        node(tile* nodeTile, node* parent, tile* goalTile);
        int heuristic(tile* startTile, tile* goalTile);
        tile* getTile();
        node* getParent();
        int getScore() const;
};


#endif