#include <SFML/Graphics.hpp>
int arrLength = 25;
void randomFillColour(sf::RectangleShape &rect) {
    rect.setFillColor(sf::Color(rand() % 255 + 0,rand() % 255 + 0,rand() % 255 + 0));
}
void bounce(sf::RectangleShape rectArr[], sf::Vector2f rectSpeedArr[], sf::RenderWindow &window) {
    for(int i = 0; i<arrLength; ++i) {
        rectArr[i].move(rectSpeedArr[i].x,0);
        if(rectArr[i].getPosition().x > window.getSize().x-10||rectArr[i].getPosition().x < 0) {
            rectSpeedArr[i].x *= -1;
            randomFillColour(rectArr[i]);
            rectArr[i].move(0,rectSpeedArr[i].y);
        }
        if(rectArr[i].getPosition().y > window.getSize().y-10||rectArr[i].getPosition().y < 0) {
            rectSpeedArr[i].y *= -1;
            randomFillColour(rectArr[i]);
            rectArr[i].move(0,rectSpeedArr[i].y);
        }
    }
}
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::RectangleShape rectArr[arrLength];
    sf::Vector2f rectSpeedArr[arrLength];
    int currRect = 0;
    for(int i = 0; i<5; ++i) {
        for(int j = 0; j<5; ++j) {
            currRect = i+j*5;
            rectArr[currRect].setSize(sf::Vector2f(25.f,25.f));
            rectArr[currRect].setFillColor(sf::Color::White);
            rectArr[currRect].setOrigin(25/2.f,25/2.f);
            rectArr[currRect].setPosition((i*30)+20,(j*30)+20);
            randomFillColour(rectArr[currRect]);
            rectSpeedArr[currRect] = sf::Vector2f(0.5,15);
        }
    }

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        bounce(rectArr, rectSpeedArr, window);

        window.clear();
        for(int i = 0; i<arrLength; ++i) {
            window.draw(rectArr[i]);
        }
        window.display();
    }
    return EXIT_SUCCESS;
}
