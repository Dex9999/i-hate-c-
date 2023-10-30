#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
//maybe make simon says, or controller typing esque game warioware
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Reeeee");
    std::stringstream ss;
    int buttPressed = 0;
    int currController = 0;
    int totalControllers = 0;

    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text text("...", font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(window.getSize().x/2,10);

    sf::Text joyText("...", font);
    joyText.setCharacterSize(30);
    joyText.setStyle(sf::Text::Bold);
    joyText.setFillColor(sf::Color::White);
    joyText.setPosition(10,10);

    sf::Text controllerText("...", font);
    controllerText.setCharacterSize(30);
    controllerText.setStyle(sf::Text::Bold);
    controllerText.setFillColor(sf::Color::White);
    controllerText.setString("              Player 0\n0 controller(s) connected!");

    float textWidth = controllerText.getGlobalBounds().width;
    float xPos = (window.getSize().x - textWidth) / 2.0f;
    controllerText.setPosition(xPos, window.getSize().y - 100);


    std::string axisLabels[] = {"X", "Y", "Z", "R", "U", "V", "D-PAD X","D-PAD Y","3?"};

    //sfml only supports up to 8 controllers
    for(int i = 0; i < 8; ++i){
        //if(sf::Joystick::isConnected(i))
        std::cout << "Controller " << i+1 << ": " << (sf::Joystick::isConnected(i) ? "connected": "not connected") << "\n";
        std::cout << (sf::Joystick::getButtonCount(i) == 0 ? 0 : sf::Joystick::getButtonCount(i)) << (sf::Joystick::getButtonCount(i) == 0 ? "" : " buttons are detected.\n");
        std::cout << (sf::Joystick::hasAxis(i, sf::Joystick::X) ? "X, " : "") << (sf::Joystick::hasAxis(i, sf::Joystick::Y) ? "Y, " : "") << (sf::Joystick::hasAxis(i, sf::Joystick::Z) ? "Z, " : "");
        std::cout << (sf::Joystick::hasAxis(i, sf::Joystick::R) ? "R, " : "") << (sf::Joystick::hasAxis(i, sf::Joystick::U) ? "U, " : "") << (sf::Joystick::hasAxis(i, sf::Joystick::V) ? "V, " : "");
        std::cout << " axes found\n";
        (sf::Joystick::isConnected(i) ? ++totalControllers : totalControllers);
    }
    std::cout << totalControllers;

    // Is button #2 pressed on joystick #0?
    //bool pressed = sf::Joystick::isButtonPressed(currController, 2);

    // What's the current position of the Y axis on joystick #0?
    //float position = sf::Joystick::getAxisPosition(currController, sf::Joystick::Y);

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
                    if (event.key.code == sf::Keyboard::Left)
                        if(sf::Joystick::isConnected(currController-1) && currController > 1){
                            --currController;
                        } else if (sf::Joystick::isConnected(totalControllers - 1)){
                            currController = totalControllers - 1;
                        } // i dont wanna loop if it's less than 8, deal with it
                    if (event.key.code == sf::Keyboard::Right)
                        if(sf::Joystick::isConnected(currController+1)){
                            ++currController;
                        } else if (sf::Joystick::isConnected(0)){
                            currController = 0;
                        } // else just chill ig idk what the user did :sob:
                    break;

                default:
                    break;
            }
        }

        sf::Joystick::update();

        // Check if a joystick is connected
        if (sf::Joystick::isConnected(currController)) {
            // Iterate through all the buttons and check their states
            for (unsigned int buttonIndex = 0; buttonIndex < sf::Joystick::getButtonCount(currController); ++buttonIndex) {
                bool buttonState = sf::Joystick::isButtonPressed(currController, buttonIndex);
                ss << "Button " << buttonIndex << ": " << (buttonState ? "true" : "false") << std::endl;
            }

            // Display the stringstream content
            text.setString(ss.str());

            ss.str("");

            for (unsigned int axisIndex = 0; axisIndex < sf::Joystick::AxisCount; ++axisIndex) {
                if (sf::Joystick::hasAxis(currController, static_cast<sf::Joystick::Axis>(axisIndex))) {
                    float position = sf::Joystick::getAxisPosition(currController, static_cast<sf::Joystick::Axis>(axisIndex));
                    ss << "Axis " << axisLabels[axisIndex] << ": " << position << std::endl;
                }
            }

            // Display the stringstream content
            joyText.setString(ss.str());

            ss.str("");
        }

        ss << "              Player " << currController+1 << "\n" << totalControllers << " controller(s) connected!";
        controllerText.setString(ss.str());

        window.clear();
        window.draw(text);
        window.draw(joyText);
        window.draw(controllerText);
        window.display();
        ss.str("");
    }

    return EXIT_SUCCESS;
}
