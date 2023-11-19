#include <SFML/Graphics.hpp>


int main() {

    int SCREEN_WIDTH = 1200;
    int SCREEN_HEIGHT = 800;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SEARCH VISUALIZER");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}