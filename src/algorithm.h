#ifndef ALGORITHM
#define ALGORITHM

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <set>
#include <chrono>
#include <thread>

#include "tileCollection.h"
#include "node.h"

class algorithm {
    private:
        tileCollection* tiles;
        int tileSize;
        int screenWidth;
        int screenHeight;
    public:
        algorithm(tileCollection* tiles, int tileSize, int screenWidth, int screen);
        node* Astar(sf::RenderWindow& window, tile* starTile, tile* goalTile);
        void displayPath(sf::RenderWindow& window, node* finalNode);
        void displayFail(sf::RenderWindow& window);
};

#endif