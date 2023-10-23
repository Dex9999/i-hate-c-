#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Edit filesystem");

    sf::Texture texture;
    if (!texture.loadFromFile("document.png")) {
        // Handle the error if the image can't be loaded
        return EXIT_FAILURE;
    }

    sf::RectangleShape button(sf::Vector2f(215, 50));
    button.setPosition(100, 150);
    button.setFillColor(sf::Color::Green);

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Font not found!" << std::endl;
        return 1;
    }

    // Create button text
    sf::Text buttonText("Create File", font, 24);
    buttonText.setPosition(120, 160);
    buttonText.setFillColor(sf::Color::White);

    std::filesystem::path sourceFile("file.txt");
    std::filesystem::path destinationFolder("test");

    if (std::filesystem::exists(sourceFile)) {
        try {
            std::filesystem::create_directory(destinationFolder);
            std::filesystem::rename(sourceFile, destinationFolder / sourceFile.filename());
            std::cout << "File moved successfully." << std::endl;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
            // Handle the error or display a message to the user
        }
    } else {
        std::cout << "Source file does not exist." << std::endl;
        // Handle the error or display a message to the user
    }

    // Create a sprite and set its texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.scale(0.10f,0.10f);
    sprite.setPosition(window.getSize().x/2,window.getSize().y/2);

    bool clicked = false;

	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
                // Check if the mouse click is within the button's bounds
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::FloatRect buttonBounds = button.getGlobalBounds();

                    if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePosition)) && clicked == false) {
                        // Button clicked
                        std::ofstream file("file.txt");
                        if (file.is_open()) {
                            file << "Hello, World!";
                            file.close();
                            std::cout << "File created successfully." << std::endl;
                            clicked = true;
                            button.setFillColor(sf::Color::Red);
                        } else {
                            std::cerr << "Failed to create the file." << std::endl;
                        }
                    }
                }
            }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);
        window.draw(button);
        window.draw(buttonText);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
