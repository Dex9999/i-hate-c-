#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "lolz");
    sf::CircleShape shape(40.f);
    shape.setFillColor(sf::Color::Green);

    bool right = true;
    float posX = shape.getPosition().x;
    float posY = shape.getPosition().y;

    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text text("Hello there!", font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + 100, 0);
    text.setPosition(200, 200);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // if (right && pos > 400)
        // {
        //     right = false;
        // }
        // else if (!right && pos < 0)
        // {
        //     right = true;
        // }
        
        // if (right)
        // {
        //     shape.move(1.f, 0.f);
        // }
        // else
        // {
        //     shape.move(-1.f, 0.f);
        // }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && posY < 420)
        {
            shape.move(0.f, 1.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && posY > 0)
        {
            shape.move(0.f, -1.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && posX > 0)
        {
            shape.rotate(-10.0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && posX < 420)
        {
            shape.move(10.0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && posY < 420)
        {
            shape.move(0.f, 1.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && posY > 0)
        {
            shape.move(0.f, -1.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && posX > 0)
        {
            shape.move(-1.f, 0.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && posX < 420)
        {
            shape.move(1.f, 0.f);
        }

        posX = shape.getPosition().x;
        posY = shape.getPosition().y;

        text.setString(std::to_string(static_cast<int>(posX)));


        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }

    return 0;
}
