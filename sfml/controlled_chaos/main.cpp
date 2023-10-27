#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Reeeee");

    //sfml only supports up to 8 controllers
    for(int i = 0; i < 8; ++i){
        //if(sf::Joystick::isConnected(i))
        std::cout << "Controller " << i+1 << ": " << (sf::Joystick::isConnected(i) ? "connected": "not connected") << "\n";
        std::cout << (sf::Joystick::getButtonCount(i) == 0 ? "" : std::to_string(sf::Joystick::getButtonCount(i))) << (sf::Joystick::getButtonCount(i) == 0 ? "" : " buttons are detected.\n");
        std::cout << (sf::Joystick::hasAxis(i, sf::Joystick::X) ? "X, " : "") << (sf::Joystick::hasAxis(i, sf::Joystick::Y) ? "Y, " : "") << (sf::Joystick::hasAxis(i, sf::Joystick::Z) ? "Z, " : "");
        std::cout << (sf::Joystick::hasAxis(i, sf::Joystick::R) ? "R, " : "") << (sf::Joystick::hasAxis(i, sf::Joystick::U) ? "U, " : "") << (sf::Joystick::hasAxis(i, sf::Joystick::V) ? "V, " : "");
        std::cout << " axes found\n";
    }
    // Is button #2 pressed on joystick #0?
    bool pressed = sf::Joystick::isButtonPressed(0, 2);

    // What's the current position of the Y axis on joystick #0?
    float position = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

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
