#include <sfml/Graphics/Color.hpp>

class tile {

    private:
        int x;
        int y;
        int width;
        int height;
        sf::Color color;
    
    public:
        // Constructors
        tile(int x, int y, int width, int height, sf::Color color);
        // Getters
        sf::Color getColor();
        // Setters
        void setColor(sf::Color color);
        // Misc

};