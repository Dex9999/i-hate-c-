#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // time makes everything complication :sob:
    sf::Clock clock;
    sf::Time elapsed;
    sf::Color lightblue(0x00fff7ff);

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

    int onScreen = 0;
    sf::CircleShape bullets[3];
    sf::Vector2f bulletVelocities[3];
    for (int i = 0; i < 3; i++)
    {
        bullets[i].setRadius(10.f);
        bullets[i].setFillColor(sf::Color::Yellow);
        bullets[i].setOrigin(10.f, 10.f);
        bullets[i].setPosition(shape.getPosition().x, shape.getPosition().y);
    }
    

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
        // bool canDash = false;

        if(elapsed.asMilliseconds() > 3000){
        // bool canDash = true;
        shape.setFillColor(sf::Color::Green);
        } else{
        shape.setFillColor(lightblue);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
            if(onScreen < 3){
                float bulletSpeed = 5.0f; // Adjust this value as needed
                float bulletAngle = (shape.getRotation() - 90.f) * (3.14159265359f / 180.f); // Convert to radians and adjust for SFML's starting rotation
                sf::Vector2f bulletVelocity(std::cos(bulletAngle) * bulletSpeed, std::sin(bulletAngle) * bulletSpeed);

                // Set bullet velocity and position
                bulletVelocities[onScreen] = bulletVelocity;
                bullets[onScreen].setPosition(shape.getPosition());
                onScreen++;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)){

            if(elapsed.asMilliseconds() > 3000){

            if (posX - deltaX*1000 >= 0.f && posX - deltaX*1000 <= window.getSize().x &&
                posY - deltaY*1000 >= 0.f && posY - deltaY*1000 <= window.getSize().y)
            {
                shape.move(-deltaX*1000, -deltaY*1000);
                arrow.move(-deltaX*1000, -deltaY*1000);
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

        sf::Vector2f position = shape.getPosition();
        sf::Vector2f enemypos = enemy.getPosition();

        // hitboxes, maybe make circles later
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
            text.setString(std::to_string(position.x) + ", " + std::to_string(position.y)+"\n"+std::to_string(enemypos.x) + ", " + std::to_string(enemypos.y));
        }
        enemy.move(0.0001*(position.x - enemypos.x), 0.0001*(position.y - enemypos.y));

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

                // stall for 3 secs so it's not program close jumpscare
                if (elapsed.asMilliseconds() >= 2250)
                {
                    window.close(); // Close the window after 3 seconds
                }
            }
        }
    }

    return 0;
}

