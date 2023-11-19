#include <SFML/Graphics.hpp>
#include <iostream>

#include "tile.h"
#include "button.h"

using namespace std;

int main() {

    sf::Font ARIAL_FONT;
    if (!ARIAL_FONT.loadFromFile("./assets/arial.ttf")) {
        printf("Unable to load font, exiting...");
        exit(-1);
    }


    int SCREEN_WIDTH = 1200;
    int SCREEN_HEIGHT = 800;

    int BUTTON_HEIGHT = 30;
    int BUTTON_WIDTH = 150;

    int FONT_SIZE = 15;

    sf::Color WHITE = sf::Color(255, 255, 255);
    sf::Color GRAY = sf::Color(128, 128, 128);
    sf::Color BLACK = sf::Color(0,0,0);
    sf::Color BLUE = sf::Color::Blue;

    string START_TILE_TEXT = "Start Tile";
    string GOAL_TILE_TEXT = "Goal Tile";
    string BLOCKER_TILE_TEXT = "Blocker Tile";
    string RANDOM_BLOCKER_TEXT = "Random Blockers";
    string SEARCH_TEXT = "Search";

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SEARCH VISUALIZER");
    
    button* currentlySelected;
    button startTileButton(25, 300, BUTTON_WIDTH, BUTTON_HEIGHT, START_TILE_TEXT, WHITE, GRAY);
    button goalTileButton(25, 340, BUTTON_WIDTH, BUTTON_HEIGHT, GOAL_TILE_TEXT, WHITE, GRAY);
    button blockerTileButton(25, 380, BUTTON_WIDTH, BUTTON_HEIGHT, BLOCKER_TILE_TEXT, WHITE, GRAY);
    button randomBlockerButton(25, 420, BUTTON_WIDTH, BUTTON_HEIGHT, RANDOM_BLOCKER_TEXT, WHITE, GRAY);
    button searchButton(25, 460, BUTTON_WIDTH, BUTTON_HEIGHT, SEARCH_TEXT, WHITE, GRAY);

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
                    if (!(currentlySelected == nullptr)) {
                        currentlySelected->changeState();
                    }
                    currentlySelected = &startTileButton;
                }
                if (goalTileButton.inBounds(position.x, position.y)) {
                    goalTileButton.changeState();
                    if (!(currentlySelected == nullptr)) {
                        currentlySelected->changeState();
                    }
                    currentlySelected = &goalTileButton;
                }
                if (blockerTileButton.inBounds(position.x, position.y)) {
                    blockerTileButton.changeState();
                    if (!(currentlySelected == nullptr)) {
                        currentlySelected->changeState();
                    }
                    currentlySelected = &blockerTileButton;
                }
                if (randomBlockerButton.inBounds(position.x, position.y)) {
                    randomBlockerButton.changeState();
                }
                if (searchButton.inBounds(position.x, position.y)) {
                    searchButton.changeState();
                }
            }
        }

        sf::RectangleShape startTileButtonRect = startTileButton.getButton();
        sf::RectangleShape goalTileButtonRect = goalTileButton.getButton();
        sf::RectangleShape blockerTileButtonRect = blockerTileButton.getButton();
        sf::RectangleShape randomBlockerButtonRect = randomBlockerButton.getButton();
        sf::RectangleShape searchButtonRect = searchButton.getButton();

        sf::Text startTileText = startTileButton.getText(ARIAL_FONT, BLACK, FONT_SIZE);
        sf::Text goalTileText = goalTileButton.getText(ARIAL_FONT, BLACK, FONT_SIZE);
        sf::Text blockerTileText = blockerTileButton.getText(ARIAL_FONT, BLACK, FONT_SIZE);
        sf::Text randomBlockerText = randomBlockerButton.getText(ARIAL_FONT, BLACK, FONT_SIZE);
        sf::Text searchText = searchButton.getText(ARIAL_FONT, BLUE, FONT_SIZE);

        window.clear(WHITE);

        window.draw(startTileButtonRect);
        window.draw(goalTileButtonRect);
        window.draw(blockerTileButtonRect);
        window.draw(randomBlockerButtonRect);
        window.draw(searchButtonRect);

        window.draw(startTileText);
        window.draw(goalTileText);
        window.draw(blockerTileText);
        window.draw(randomBlockerText);
        window.draw(searchText);

        window.display();

    }

    return 0;
}