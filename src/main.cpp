#include <SFML/Graphics.hpp>
#include <iostream>

#include "tile.h"
#include "button.h"
#include "tileCollection.h"
#include "algorithm.h"

using namespace std;

enum Selection {
    NO_SELECTION,
    START_TILE,
    GOAL_TILE,
    BLOCKER_TILE,
    ERASE,
    CLEAR,
    RANDOM,
    SEARCH
};

int main() {

    sf::Font ARIAL_FONT;
    if (!ARIAL_FONT.loadFromFile("./assets/arial.ttf")) {
        printf("Unable to load font, exiting...");
        exit(-1);
    }

    Selection currentSelection = NO_SELECTION;

    int SCREEN_WIDTH = 1200;
    int SCREEN_HEIGHT = 800;

    int TILE_SIZE = 20;

    int BUTTON_HEIGHT = 30;
    int BUTTON_WIDTH = 150;

    int BUTTON_X = 25;
    int BUTTON_Y = 25;

    int FONT_SIZE = 15;

    int RANDOMIZE_THRESHOLD = 70;

    sf::Color WHITE = sf::Color(255, 255, 255);
    sf::Color GRAY = sf::Color(128, 128, 128);
    sf::Color BLACK = sf::Color(0,0,0);
    sf::Color BLUE = sf::Color::Blue;

    sf::Color START_TILE_COLOR = BLUE;
    sf::Color GOAL_TILE_COLOR = BLUE;
    sf::Color BLANK_TILE_COLOR = WHITE;
    sf::Color BLOCKER_TILE_COLOR = BLACK;

    string START_TILE_TEXT = "Start Tile";
    string GOAL_TILE_TEXT = "Goal Tile";
    string BLOCKER_TILE_TEXT = "Blocker Tile";
    string RANDOM_BLOCKER_TEXT = "Random Blockers";
    string SEARCH_TEXT = "Search";
    string ERASE_TEXT = "Erase";
    string CLEAR_TEXT = "CLEAR";

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SEARCH VISUALIZER");
    
    button* currentButtonSelection;
    button startTileButton(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, START_TILE_TEXT, WHITE, GRAY);
    button goalTileButton(BUTTON_X, BUTTON_Y + 40, BUTTON_WIDTH, BUTTON_HEIGHT, GOAL_TILE_TEXT, WHITE, GRAY);
    button blockerTileButton(BUTTON_X, BUTTON_Y + 80, BUTTON_WIDTH, BUTTON_HEIGHT, BLOCKER_TILE_TEXT, WHITE, GRAY);
    button randomBlockerButton(BUTTON_X, BUTTON_Y + 120, BUTTON_WIDTH, BUTTON_HEIGHT, RANDOM_BLOCKER_TEXT, WHITE, GRAY);
    button eraseButton(BUTTON_X, BUTTON_Y + 160, BUTTON_WIDTH, BUTTON_HEIGHT, ERASE_TEXT, WHITE, GRAY);
    button clearButton(BUTTON_X, BUTTON_Y + 200, BUTTON_WIDTH, BUTTON_HEIGHT, CLEAR_TEXT, WHITE, GRAY);
    button searchButton(BUTTON_X, BUTTON_Y + 240, BUTTON_WIDTH, BUTTON_HEIGHT, SEARCH_TEXT, WHITE, GRAY);

    vector<button> buttons;
    buttons.push_back(startTileButton);
    buttons.push_back(goalTileButton);
    buttons.push_back(blockerTileButton);
    buttons.push_back(randomBlockerButton);
    buttons.push_back(eraseButton);
    buttons.push_back(clearButton);
    buttons.push_back(searchButton);

    tileCollection* tiles = new tileCollection(TILE_SIZE);
    tile* startTile = nullptr;
    tile* goalTile = nullptr;

    algorithm algorithmHandler(tiles, TILE_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i position = sf::Mouse::getPosition(window);

                if (startTileButton.inBounds(position.x, position.y)) {
                    startTileButton.changeState();
                    if (!(currentButtonSelection == nullptr)) {
                        currentButtonSelection->changeState();
                    }
                    currentButtonSelection = &startTileButton;
                    currentSelection = START_TILE;
                }

                if (goalTileButton.inBounds(position.x, position.y)) {
                    goalTileButton.changeState();
                    if (!(currentButtonSelection == nullptr)) {
                        currentButtonSelection->changeState();
                    }
                    currentButtonSelection = &goalTileButton;
                    currentSelection = GOAL_TILE;
                }

                if (blockerTileButton.inBounds(position.x, position.y)) {
                    blockerTileButton.changeState();
                    if (!(currentButtonSelection == nullptr)) {
                        currentButtonSelection->changeState();
                    }
                    currentButtonSelection = &blockerTileButton;
                    currentSelection = BLOCKER_TILE;
                }

                if (eraseButton.inBounds(position.x, position.y)) {
                    eraseButton.changeState();
                    if (!(currentButtonSelection == nullptr)) {
                        currentButtonSelection->changeState();
                    }
                    currentButtonSelection = &eraseButton;
                    currentSelection = ERASE;
                }

                if (clearButton.inBounds(position.x, position.y)) {
                    clearButton.changeState();
                    tiles->clear();
                    if (!(currentButtonSelection == nullptr)) {
                        currentButtonSelection->changeState();
                    }
                    currentButtonSelection = &clearButton;
                    currentSelection = CLEAR;
                }

                if (randomBlockerButton.inBounds(position.x, position.y) && currentSelection != RANDOM) {
                    randomBlockerButton.changeState();
                    tiles->clearBlockers();
                    tiles->randomize(RANDOMIZE_THRESHOLD);
                    if (!(currentButtonSelection == nullptr)) {
                        currentButtonSelection->changeState();
                    }
                    currentButtonSelection = &randomBlockerButton;
                    currentSelection = RANDOM;
                }

                if (searchButton.inBounds(position.x, position.y)) {
                    if (!(currentButtonSelection == nullptr)) {
                        currentButtonSelection->changeState();
                    }
                    currentSelection = SEARCH;
                }

                if (position.x >= 200) {
                    tile* selectedTile = tiles->tileInCoordinate(position.x, position.y, TILE_SIZE);
                    if (currentSelection == START_TILE && selectedTile->getColor() == BLANK_TILE_COLOR) {
                        selectedTile->setColor(START_TILE_COLOR);
                        if (startTile != nullptr) {
                            startTile->setColor(BLANK_TILE_COLOR);
                        }
                        startTile = selectedTile;
                    } else if (currentSelection == GOAL_TILE && selectedTile->getColor() == BLANK_TILE_COLOR) {
                        selectedTile->setColor(GOAL_TILE_COLOR);
                        if (goalTile != nullptr) {
                            goalTile->setColor(BLANK_TILE_COLOR);
                        }
                        goalTile = selectedTile;
                    } else if (currentSelection == BLOCKER_TILE && selectedTile->getColor() == BLANK_TILE_COLOR) {
                        selectedTile->setColor(BLOCKER_TILE_COLOR);
                    } else if (currentSelection == ERASE) {
                        if (selectedTile == startTile) {
                            selectedTile->setColor(BLANK_TILE_COLOR);
                            startTile == nullptr;
                        } else if (selectedTile == goalTile) {
                            selectedTile->setColor(BLANK_TILE_COLOR);
                            goalTile = nullptr;
                        } else {
                            selectedTile->setColor(BLANK_TILE_COLOR);
                        }
                    }
                }
            }

        }

        vector<sf::RectangleShape> displayButtons;
        displayButtons.push_back(startTileButton.getButton());
        displayButtons.push_back(goalTileButton.getButton());
        displayButtons.push_back(blockerTileButton.getButton());
        displayButtons.push_back(randomBlockerButton.getButton());
        displayButtons.push_back(eraseButton.getButton());
        displayButtons.push_back(clearButton.getButton());
        displayButtons.push_back(searchButton.getButton());

        vector<sf::Text> buttonText;
        buttonText.push_back(startTileButton.getText(ARIAL_FONT, BLACK, FONT_SIZE));
        buttonText.push_back(goalTileButton.getText(ARIAL_FONT, BLACK, FONT_SIZE));
        buttonText.push_back(blockerTileButton.getText(ARIAL_FONT, BLACK, FONT_SIZE));
        buttonText.push_back(randomBlockerButton.getText(ARIAL_FONT, BLACK, FONT_SIZE));
        buttonText.push_back(eraseButton.getText(ARIAL_FONT, BLACK, FONT_SIZE));
        buttonText.push_back(clearButton.getText(ARIAL_FONT, BLACK, FONT_SIZE));
        buttonText.push_back(searchButton.getText(ARIAL_FONT, BLUE, FONT_SIZE));

        window.clear(WHITE);

        for (int i = 0; i < displayButtons.size(); i++) {
            window.draw(displayButtons.at(i));
        }

        for (int i = 0; i < buttonText.size(); i++) {
            window.draw(buttonText.at(i));
        }


        if (currentSelection != SEARCH) {
            tiles->drawTiles(window);
            window.display();
        } else {
            if (startTile != nullptr && goalTile != nullptr) {
                
                node* finalNode = algorithmHandler.Astar(window, startTile, goalTile);
                if (finalNode != nullptr) {
                    algorithmHandler.displayPath(window, finalNode);
                } else {
                    algorithmHandler.displayFail(window);
                    startTile->setColor(START_TILE_COLOR);
                    goalTile->setColor(GOAL_TILE_COLOR);
                    window.display();
                }

                startTile = nullptr;
                goalTile = nullptr;

                for (int i = 0; i < buttons.size(); i++) {
                    buttons.at(i).setColor(WHITE);
                    window.draw(buttons.at(i).getButton());
                    window.draw(buttonText.at(i));
                }
                window.clear(WHITE);
                window.display();
                currentSelection = NO_SELECTION;
                currentButtonSelection = nullptr;
            }
            
        }

    }

    return 0;
}