#ifndef ALGORITHM
#define ALGORITHM

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <set>
#include <chrono>
#include <thread>
#include <stack>

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
        node* Astar(sf::RenderWindow& window, tile* startTile, tile* goalTile);
        node* BestFS(sf::RenderWindow& window, tile* startTile, tile* goalTile);
        node* BFS(sf::RenderWindow& window, tile* startTile, tile* goalTile);
        node* DFS(sf::RenderWindow& window, tile* startTile, tile* goalTile);
        void displayPath(sf::RenderWindow& window, node* finalNode);
        void displayFail(sf::RenderWindow& window);
        void clearPath(sf::RenderWindow& window);
};

#endif