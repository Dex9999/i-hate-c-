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
    sf::Texture ftexture;
    if (!ftexture.loadFromFile("folder.png")) {
        // Handle the error if the image can't be loaded
        return EXIT_FAILURE;
    }



    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Font not found!" << std::endl;
        return 1;
    }

    // Create button text
    sf::Text buttonText("+", font, 24);
    buttonText.setPosition(120, 160);
    buttonText.setFillColor(sf::Color::White);

    sf::RectangleShape button(sf::Vector2f(buttonText.getGlobalBounds().width*2, buttonText.getGlobalBounds().height*2));
    button.setPosition(buttonText.getPosition().x-(buttonText.getGlobalBounds().width/2), buttonText.getPosition().y-(buttonText.getGlobalBounds().height/3));
    button.setFillColor(sf::Color::Green);

    std::filesystem::path sourceFile("file.txt");
    std::filesystem::path destinationFolder("test");

    // Create a sprite and set its texture
    sf::Sprite doc;
    doc.setTexture(texture);
    doc.scale(0.10f,0.10f);
    doc.setPosition(window.getSize().x/2,window.getSize().y/2);

    sf::Sprite folder;
    folder.setTexture(ftexture);
    folder.scale(0.10f,0.10f);
    folder.setPosition(window.getSize().x/2+200,window.getSize().y/2);

    bool clicked = false;
    bool docDraw = true;
    // for dragging
    bool isDragging = false;
    sf::Vector2f offset;

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
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::FloatRect buttonBounds = button.getGlobalBounds();
        sf::FloatRect docBounds = doc.getGlobalBounds();
        sf::FloatRect folderBounds = folder.getGlobalBounds();

        if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {


                    if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePosition)) && !clicked) {
                        // Button clicked
                        std::ofstream file("file.txt");
                        if (file.is_open()) {
                            file << "Hello, World!";
                            file.close();
                            std::cout << "File created successfully." << std::endl;
                            clicked = true;
                            button.setFillColor(sf::Color::Red);
                        } else {
                            std::cout << "Failed to create the file.";
                        }
                    }

                    if (docBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                        // Mouse is pressed on the document; start dragging
                        isDragging = true;
                        offset = doc.getPosition() - static_cast<sf::Vector2f>(mousePosition);
                    }
                }

            } else if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        isDragging = false;
                    }
                }

            if (event.type == sf::Event::MouseMoved) {
                    if (isDragging) {
                        // Mouse is being dragged; move the document
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                        doc.setPosition(static_cast<sf::Vector2f>(mousePosition) + offset);
                    }
            } else if (folderBounds.intersects(docBounds)) {
                std::cout << "Moved file!";

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

                docDraw = false;
                doc.setPosition(window.getSize().x / 2, window.getSize().y / 2);
            } else if (docBounds.contains(static_cast<sf::Vector2f>(mousePosition)) && !clicked) {
                doc.setPosition(window.getSize().x / 2, window.getSize().y / 2);
            }

        // Clear screen
        window.clear();

        // Draw the sprite
        if(docDraw)
            window.draw(doc);

        window.draw(folder);
        window.draw(button);
        window.draw(buttonText);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
