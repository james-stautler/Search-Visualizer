#include "algorithm.h"

algorithm::algorithm(tileCollection* tiles, int tileSize, int screenWidth, int screenHeight) {
    this->tiles = tiles;
    this->tileSize = tileSize;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

struct nodeCompare {
    bool operator() (const node* lhs, const node* rhs) const {
        return lhs->getScore() > rhs->getScore();
    }
};

node* algorithm::Astar(sf::RenderWindow& window, tile* startTile, tile* goalTile) {
    std::set<tile*> visited;
    std::priority_queue<node*, std::vector<node*>, nodeCompare> pq;
    pq.push(new node(startTile, goalTile));
    while (!pq.empty()) {
        node* curr = pq.top();
        pq.pop();
        if (curr->getTile() == goalTile) {
            return curr;
        }
        if (visited.find(curr->getTile()) != visited.cend()) {
            continue;
        }
        if (curr->getTile()->getColor() == sf::Color::Black) {
            visited.insert(curr->getTile());
            continue;
        }
        curr->getTile()->setColor(sf::Color(255, 20, 147));
        tiles->drawTiles(window);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        visited.insert(curr->getTile());
        std::vector<tile*> neighbors = tiles->getNeighbors(curr->getTile(), tileSize, screenWidth, screenHeight);
        for (int i = 0; i < neighbors.size(); i++) {
            pq.push(new node(neighbors.at(i), curr, goalTile));
        }
    }
    return nullptr;
};

void algorithm::displayPath(sf::RenderWindow& window, node* finalNode) {
    node* curr = finalNode->getParent();
    while (curr->getParent() != nullptr) {
        curr->getTile()->setColor(sf::Color::Green);
        curr = curr->getParent();
    }
    curr->getTile()->setColor(sf::Color::Blue);
    tiles->drawTiles(window);
    window.display();
}

void algorithm::displayFail(sf::RenderWindow& window) {
    for (int i = 0; i < tiles->getTiles().size(); i++) {
        for (int j = 0; j < tiles->getTiles().at(i).size(); j++) {
            if (tiles->getTiles().at(i).at(j)->getColor() != sf::Color::Black) {
                tiles->getTiles().at(i).at(j)->setColor(sf::Color::Red);
            }
        }
    }
    tiles->drawTiles(window);
}