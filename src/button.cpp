#include "button.h"

int VERTICAL_TEXT_ADJUST = 3;

button::button(int x, int y, int width, int height, string text, sf::Color offColor, sf::Color onColor) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    this->offColor = offColor;
    this->onColor = onColor;
    this->currColor = offColor;
    this->state = false;
}

void button::changeState() {
    if (this->state == false) {
        this->state = true;
        this->currColor = this->onColor;
    } else {
        this->state = false;
        this->currColor = this->offColor;
    }
}

void button::setText(string text) {
    this->text = text;
}

bool button::getState() {
    return this->state;
}

bool button::inBounds(int x, int y) {
    if (x >= this->x && x <= (this->x + this->width)) {
        if (y >= this->y && y <= (this->y + this->height)) {
            return true;
        }
    }
    return false;
}

sf::RectangleShape button::getButton() {
    sf::RectangleShape rectangle(sf::Vector2f(this->width, this->height));
    rectangle.setPosition(sf::Vector2f(this->x, this->y));
    rectangle.setFillColor(this->currColor);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(sf::Color::Black);
    return rectangle;
}

sf::Text button::getText(sf::Font &font, sf::Color color, int fontSize) {
    sf::Text textOutput;
    textOutput.setFont(font);
    textOutput.setString(this->text);
    textOutput.setColor(color);
    textOutput.setCharacterSize(fontSize);
    
    sf::FloatRect bounds = textOutput.getGlobalBounds();

    int textWidth = this->text.size() * fontSize;

    int adjustedX = this->x + (this->width - bounds.width) / 2;
    int adjustedY = this->y + (this->height - bounds.height) / 2 - VERTICAL_TEXT_ADJUST;
    textOutput.setPosition(adjustedX, adjustedY);
    return textOutput;
}