#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "lolz");
    sf::CircleShape shape(40.f);
    shape.setFillColor(sf::Color::Green);

    bool right = true;
    sf::ConvexShape arrow;
    arrow.setPointCount(3);
    arrow.setPoint(0, sf::Vector2f(0.f, -40.f)); // Top point
    arrow.setPoint(1, sf::Vector2f(-30.f, 15.f)); // Bottom-left point
    arrow.setPoint(2, sf::Vector2f(15.f, 20.f)); // Bottom-right point
    arrow.setFillColor(sf::Color::Red);

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

        float speed = 1.f;

        float facing = shape.getRotation();
        float radians = (facing - 90.f) * (3.14159265359f / 180.f); // Convert to radians and adjust for SFML's starting rotation

        // Calculate movement in the direction of rotation
        float deltaX = std::cos(radians) * speed;
        float deltaY = std::sin(radians) * speed;
        sf::FloatRect shapeBounds = shape.getGlobalBounds();

        // Tank drive
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && posY < 420)
        {
            shape.move(deltaX, deltaY);
            arrow.move(deltaX, deltaY);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && posX > 0)
        {
            shape.rotate(-speed);
            arrow.rotate(-speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && posX < 420)
        {
            shape.rotate(speed);
            arrow.rotate(speed);
        }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && posY > 0)
        {
            shape.move(-deltaX, -deltaY);
            arrow.move(-deltaX, -deltaY);
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && posX > 0)
        {
            shape.rotate(-speed);
            arrow.rotate(-speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && posX < 420)
        {
            shape.rotate(speed);
            arrow.rotate(speed);
        }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && posX > 0)
        {
            shape.rotate(-speed);
            arrow.rotate(-speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && posX < 420)
        {
            shape.rotate(speed);
            arrow.rotate(speed);
        }

        // Strafing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && posY < 420)
        {
            shape.move(-deltaY, deltaX);
            arrow.move(-deltaY, deltaX);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && posY > 0)
        {
            shape.move(deltaY, -deltaX);
            arrow.move(deltaY, -deltaX);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && posX > 0)
        {
            shape.move(-deltaX, -deltaY);
            arrow.move(-deltaX, -deltaY);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && posX < 420)
        {
            shape.move(deltaX, deltaY);
            arrow.move(deltaX, deltaY);
        }

        posX = shape.getPosition().x;
        posY = shape.getPosition().y;

        text.setString(std::to_string(static_cast<float>(facing)));


        window.clear();
        window.draw(shape);
        window.draw(arrow);
        window.draw(text);
        window.display();
    }

    return 0;
}
