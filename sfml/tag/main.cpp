#include <SFML/Graphics.hpp>
const float gravity = 0.3f;
const float jumpStrength = 10.0f;
const float jumpDuration = 10.0f; 
int main()
{
    sf::RectangleShape p1(sf::Vector2f(80.f, 80.f));
    p1.setFillColor(sf::Color::Blue);
    p1.setOrigin(40.f, 40.f);
    p1.setPosition((p1.getPosition().x + p1.getOrigin().x), p1.getPosition().y + p1.getOrigin().y);

    sf::RectangleShape p2(sf::Vector2f(80.f, 80.f));
    p2.setFillColor(sf::Color::Red);
    p2.setOrigin(40.f, 40.f);
    p2.setPosition((p2.getPosition().x + p2.getOrigin().x), p2.getPosition().y + p2.getOrigin().y);
    sf::RenderWindow window(sf::VideoMode(1600, 900), "1v1 Tag");

    p1.setPosition(window.getSize().x / 4, window.getSize().y / 2);
    p2.setPosition(window.getSize().x / 1.25, window.getSize().y / 2);

    double speed = 2.5;
    sf::Vector2f p1Velocity(0.0, 0.0);
    sf::Vector2f p2Velocity(0.0, 0.0);
    bool p1Jumping = false;
    bool p2Jumping = false;
    float p1JumpTimer = 0.0f;
    float p2JumpTimer = 0.0f;
    

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }

         // Player 1 controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            p1Velocity.x = -speed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            p1Velocity.x = speed;
        }
        else
        {
            p1Velocity.x = 0.0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && p1.getPosition().y >= window.getSize().y - p1.getSize().y)
        {
            // Jump when on the ground
            p1Velocity.y = -jumpStrength;
            p1Jumping = true;
        }

        // Player 2 controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            p2Velocity.x = -speed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            p2Velocity.x = speed;
        }
        else
        {
            p2Velocity.x = 0.0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && p2.getPosition().y >= window.getSize().y - p2.getSize().y)
        {
            // Jump when on the ground
            p2Velocity.y = -jumpStrength;
            p2Jumping = true;        }

        // Simulate gravity
        if (p1Jumping)
        {
            p1JumpTimer++;
            if (p1JumpTimer >= jumpDuration)
            {
                p1Jumping = false;
                p1JumpTimer = 0.0f;
            }
        }
        else if (p1.getPosition().y < window.getSize().y - p1.getSize().y)
        {
            p1Velocity.y += gravity;
        }

        if (p2Jumping)
        {
            p2JumpTimer++;
            if (p2JumpTimer >= jumpDuration)
            {
                p2Jumping = false;
                p2JumpTimer = 0.0f;
            }
        }
        else if (p2.getPosition().y < window.getSize().y - p2.getSize().y)
        {
            p2Velocity.y += gravity;
        }

        p1.move(p1Velocity);
        p2.move(p2Velocity);

        //boundaries
        if (p1.getPosition().x < 0)
        {
            p1.setPosition(0, p1.getPosition().y);
        }
        if (p1.getPosition().x + p1.getSize().x > window.getSize().x)
        {
            p1.setPosition(window.getSize().x - p1.getSize().x, p1.getPosition().y);
        }

        if (p2.getPosition().x < 0)
        {
            p2.setPosition(0, p2.getPosition().y);
        }
        if (p2.getPosition().x + p2.getSize().x > window.getSize().x)
        {
            p2.setPosition(window.getSize().x - p2.getSize().x, p2.getPosition().y);
        }

        if (p1.getPosition().y + p1.getSize().y > window.getSize().y)
        {
            p1.setPosition(p1.getPosition().x, window.getSize().y - p1.getSize().y);
        }

        if (p2.getPosition().y + p2.getSize().y > window.getSize().y)
        {
            p2.setPosition(p2.getPosition().x, window.getSize().y - p2.getSize().y);
        }


        if (p1.getPosition().y + p1.getSize().y > window.getSize().y)
        {
            p1.setPosition(p1.getPosition().x, window.getSize().y - p1.getSize().y);
            p1Jumping = false; // Reset jumping state when landing
        }

        if (p2.getPosition().y + p2.getSize().y > window.getSize().y)
        {
            p2.setPosition(p2.getPosition().x, window.getSize().y - p2.getSize().y);
            p2Jumping = false; // Reset jumping state when landing
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(p1);
        window.draw(p2);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
