#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // time makes everything complication :sob:
    sf::Clock clock;
    sf::Time elapsed;

    bool dead = false;
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "DRIVE RICKY DRIVE", sf::Style::Fullscreen);
    // sf::RenderWindow window(sf::VideoMode(1000, 1000), "lolz");
    sf::CircleShape shape(40.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(40.f, 40.f);
    shape.setPosition(shape.getPosition().x + shape.getOrigin().x, shape.getPosition().y + shape.getOrigin().y);

    sf::CircleShape enemy(40.f);
    enemy.setFillColor(sf::Color::Red);
    enemy.setOrigin(40.f, 40.f);
    enemy.setPosition(enemy.getPosition().x + enemy.getOrigin().x, enemy.getPosition().y + enemy.getOrigin().y);
    enemy.move(100, 100);

    bool right = true;
    sf::ConvexShape arrow;
    arrow.setPointCount(3);
    arrow.setPoint(0, sf::Vector2f(0.f, 20.f));    // Top point
    arrow.setPoint(1, sf::Vector2f(-15.f, -20.f)); // Bottom-left point
    arrow.setPoint(2, sf::Vector2f(15.f, -20.f));  // Bottom-right point
    arrow.setFillColor(sf::Color::Red);
    arrow.setPosition(shape.getPosition().x, shape.getPosition().y);

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
    // make point up and start in center
    shape.rotate(180);
    arrow.rotate(180);

    shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    arrow.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
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

        float speed = 0.25;

        float facing = shape.getRotation();
        float radians = (facing - 90.f) * (3.14159265359f / 180.f); // Convert to radians and adjust for SFML's starting rotation

        // Calculate movement in the direction of rotation
        float deltaX = std::cos(radians) * speed;
        float deltaY = std::sin(radians) * speed;
        sf::FloatRect shapeBounds = shape.getGlobalBounds();

        //cur time for sprint
        elapsed = clock.getElapsedTime();

        // Tank drive

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            if (posX + deltaX >= 0.f && posX + deltaX <= window.getSize().x &&
                posY + deltaY >= 0.f && posY + deltaY <= window.getSize().y)
            {
                shape.move(deltaX, deltaY);
                arrow.move(deltaX, deltaY);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            if (posX - deltaX >= 0.f && posX - deltaX <= window.getSize().x &&
                posY - deltaY >= 0.f && posY - deltaY <= window.getSize().y)
            {
                shape.move(-deltaX, -deltaY);
                arrow.move(-deltaX, -deltaY);
            }
        }
        // space to dash
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){

            if(elapsed.asMilliseconds() > 5000){

            if (posX - deltaX*1500 >= 0.f && posX - deltaX*1500 <= window.getSize().x &&
                posY - deltaY*1500 >= 0.f && posY - deltaY*1500 <= window.getSize().y)
            {
                shape.move(-deltaX*1500, -deltaY*1500);
                arrow.move(-deltaX*1500, -deltaY*1500);
            }
            shape.setFillColor(sf::Color::Yellow);
            clock.restart();
            } else{
            shape.setFillColor(sf::Color::Green);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            shape.rotate(-speed / 2);
            arrow.rotate(-speed / 2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            shape.rotate(speed / 2);
            arrow.rotate(speed / 2);
        }

        // Strafing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            if (posX - deltaY >= 0.f && posX - deltaY <= window.getSize().x &&
                posY + deltaX >= 0.f && posY + deltaX <= window.getSize().y)
            {
                shape.move(-deltaY, deltaX);
                arrow.move(-deltaY, deltaX);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if (posX + deltaY >= 0.f && posX + deltaY <= window.getSize().x &&
                posY - deltaX >= 0.f && posY - deltaX <= window.getSize().y)
            {
                shape.move(deltaY, -deltaX);
                arrow.move(deltaY, -deltaX);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            if (posX - deltaX >= 0.f && posX - deltaX <= window.getSize().x &&
                posY - deltaY >= 0.f && posY - deltaY <= window.getSize().y)
            {
                shape.move(-deltaX, -deltaY);
                arrow.move(-deltaX, -deltaY);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            if (posX + deltaX >= 0.f && posX + deltaX <= window.getSize().x &&
                posY + deltaY >= 0.f && posY + deltaY <= window.getSize().y)
            {
                shape.move(deltaX, deltaY);
                arrow.move(deltaX, deltaY);
            }
        }

        posX = shape.getPosition().x;
        posY = shape.getPosition().y;



        sf::FloatRect rect1 = shape.getGlobalBounds();
        sf::FloatRect rect2 = enemy.getGlobalBounds();

        if (rect1.intersects(rect2))
        {
            dead = true;
        }

        if (dead)
        {
            text.setString("You died!");
            shape.setFillColor(sf::Color::Blue);
            arrow.setFillColor(sf::Color::Blue);
        }
        else
        {
            text.setString(std::to_string(static_cast<float>(elapsed.asMilliseconds())));
        }

        window.clear();
        window.draw(shape);
        window.draw(arrow);
        window.draw(enemy);
        window.draw(text);
        window.display();
        if (dead)
        {
            clock.restart();
            while (true)
            {
                elapsed = clock.getElapsedTime();

                // stall for 3 secs so its not program close jumpscare
                if (elapsed.asMilliseconds() >= 2250)
                {
                    window.close(); // Close the window after 3 seconds
                }
            }
        }
    }

    return 0;
}
