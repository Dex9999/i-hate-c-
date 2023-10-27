#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Reeeee");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
             switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;

                default:
                    break;
            }
        }

        window.clear();
        //window.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}
