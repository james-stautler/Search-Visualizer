#include "algorithm.h"

sf::Color FRONTIER_COLOR = sf::Color(255,20,147);
sf::Color EXPLORED_COLOR = sf::Color(255,140,0);

algorithm::algorithm(tileCollection* tiles, int tileSize, int screenWidth, int screenHeight) {
    this->tiles = tiles;
    this->tileSize = tileSize;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

struct astarNodeCompare {
    bool operator() (const node* lhs, const node* rhs) const {
        return lhs->getScore() > rhs->getScore();
    }
};

struct greedyCompare {
    bool operator() (const node* lhs, const node* rhs) const {
        return lhs->getHeuristicScore() > rhs->getHeuristicScore();
    }
};

node* algorithm::Astar(sf::RenderWindow& window, tile* startTile, tile* goalTile) {
    std::set<tile*> visited;
    std::priority_queue<node*, std::vector<node*>, astarNodeCompare> pq;
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
        curr->getTile()->setColor(FRONTIER_COLOR);
        window.clear(sf::Color::White);
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
}

node* algorithm::BestFS(sf::RenderWindow& window, tile* startTile, tile* goalTile) {
    std::set<tile*> visited;
    std::priority_queue<node*, std::vector<node*>, greedyCompare> pq;
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
        curr->getTile()->setColor(FRONTIER_COLOR);
        window.clear(sf::Color::White);
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
}


node* algorithm::BFS(sf::RenderWindow& window, tile* startTile, tile* goalTile) {
    std::set<tile*> visited;
    std::queue<node*> q;
    q.push(new node(startTile, goalTile));
    while (!q.empty()) {
        node* curr = q.front();
        q.pop();
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
        curr->getTile()->setColor(FRONTIER_COLOR);
        window.clear(sf::Color::White);
        tiles->drawTiles(window);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        visited.insert(curr->getTile());
        std::vector<tile*> neighbors = tiles->getNeighbors(curr->getTile(), tileSize, screenWidth, screenHeight);
        for (int i = 0; i < neighbors.size(); i++) {
            q.push(new node(neighbors.at(i), curr, goalTile));
        }
    }
    return nullptr;
}

node* algorithm::DFS(sf::RenderWindow& window, tile* startTile, tile* goalTile) {
    std::set<tile*> visited;
    std::stack<node*> stack;
    stack.push(new node(startTile, goalTile));
    while (!stack.empty()) {
        node* curr = stack.top();
        stack.pop();
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
        window.clear(sf::Color::White);
        tiles->drawTiles(window);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        visited.insert(curr->getTile());
        std::vector<tile*> neighbors = tiles->getNeighbors(curr->getTile(), tileSize, screenWidth, screenHeight);
        for (int i = 0; i < neighbors.size(); i++) {
            stack.push(new node(neighbors.at(i), curr, goalTile));
        }
    }
    return nullptr;
}

void algorithm::displayPath(sf::RenderWindow& window, node* finalNode) {
    node* curr = finalNode->getParent();
    while (curr->getParent() != nullptr) {
        curr->getTile()->setColor(sf::Color::Green);
        curr = curr->getParent();
    }
    curr->getTile()->setColor(sf::Color::Blue);
    tiles->drawTiles(window);
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

void algorithm::clearPath(sf::RenderWindow& window) {
    for (int i = 0; i < tiles->getTiles().size(); i++) {
        for (int j = 0; j < tiles->getTiles().at(i).size(); j++) {
            if (tiles->getTiles().at(i).at(j)->getColor() == FRONTIER_COLOR || tiles->getTiles().at(i).at(j)->getColor() == sf::Color::Green) {
                tiles->getTiles().at(i).at(j)->setColor(sf::Color::White);
            }
        }
    }
    tiles->drawTiles(window);
}