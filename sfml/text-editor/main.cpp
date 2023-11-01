#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Text Editor");
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10, 10);
    std::string inputText; // Store user's text input
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    // Handle backspace
                    if (!inputText.empty())
                    {
                        inputText.pop_back();
                    }
                }
                else
                {
                    // Append the character to inputText
                    inputText += static_cast<char>(event.text.unicode);
                }
                text.setString(inputText);
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
