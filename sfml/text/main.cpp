#include <SFML/Graphics.hpp>
#include <string>

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "text!!!");

    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text txt;
    txt.setFont(font);
    txt.setCharacterSize(100);
    txt.setFillColor(sf::Color::Green);
    txt.setPosition(app.getSize().x/2-50, app.getSize().y/2-45);
    txt.setStyle(sf::Text::Bold);

    sf::Clock clock;


    int num = 10;
    txt.setString(std::to_string(num));
	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        sf::Time elapsedTime(clock.getElapsedTime());

        if(num>0 && elapsedTime.asSeconds() >= 1.0){
            txt.setPosition(app.getSize().x/2-20, app.getSize().y/2-45);
            txt.setString(std::to_string(--num));
            clock.restart();
        }

        // Draw the sprite
        app.draw(txt);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
