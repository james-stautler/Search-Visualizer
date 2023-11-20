#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace std;

class button {
    private:
        int x;
        int y;
        int width;
        int height;
        string text;
        sf::Color offColor;
        sf::Color onColor;
        sf::Color currColor;
        bool state;

    public:
        button(int x, int y, int width, int height, string text, sf::Color offColor, sf::Color onColor);
        
        void changeState();
        void setText(string text);
        void setColor(sf::Color color);
        
        bool getState();
        
        bool inBounds(int x, int y);
        sf::RectangleShape getButton();
        sf::Text getText(sf::Font &font, sf::Color color, int fontSize);
        
};

#endif