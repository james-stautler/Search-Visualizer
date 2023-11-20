#include "node.h"


node::node(tile* nodeTile, tile* goalTile) {
    this->nodeTile = nodeTile;
    this->goalTile = goalTile;
    this->parent = nullptr;
    this->f = 0;
    this->g = 100000;
}

node::node(tile* nodeTile, node* parent, tile* goalTile) {
    this->nodeTile = nodeTile;
    this->goalTile = goalTile;
    this->parent = parent;
    this->f = parent->f + 20;
    this->g = heuristic(nodeTile, goalTile);
}

int node::heuristic(tile* startTile, tile* goalTile) {
    return abs(startTile->getX() - goalTile->getX()) + abs(startTile->getY() - goalTile->getY());
}

tile* node::getTile() {
    return this->nodeTile;
}

int node::getScore() const {
    return (f + g);
}

node* node::getParent() {
    return this->parent;
}