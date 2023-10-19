#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int main()
{
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1, 1), "Pong!");
    window.setPosition(sf::Vector2i(screen.width,screen.height));

    sf::RenderWindow ball(sf::VideoMode(40, 25), "boing");
    sf::Color red(0xBF1304FF);
    sf::Color white(0xFFFFFFFF);
    // ball.setFillColor(red);
    ball.setPosition(sf::Vector2i(screen.width / 2 - 37, screen.height / 2 - 25));

    // Ball position floats
    float x = screen.width / 2 - 37;  // Initial x position
    float y = screen.height / 2 - 25;  // Initial y position

    float dx = 1.5f; // Horizontal speed
    float dy = 1.5f; // Vertical speed

    sf::RenderWindow p1(sf::VideoMode(20, 125), "p1");
    p1.setPosition(sf::Vector2i(30, screen.height / 2 - p1.getSize().y/2));

    sf::RenderWindow p2(sf::VideoMode(20, 125), "p2");
    p2.setPosition(sf::Vector2i(screen.width - 30, screen.height / 2 - 62.5));

    sf::RenderWindow rallyWindow(sf::VideoMode(225, 150), "Rally:", sf::Style::Titlebar | sf::Style::Close);
    rallyWindow.setPosition(sf::Vector2i(screen.width/2 - rallyWindow.getSize().x/2, 30));

    sf::RenderWindow p1ScoreWindow(sf::VideoMode(190, 150), "", sf::Style::Titlebar | sf::Style::Close);
    p1ScoreWindow.setPosition(sf::Vector2i(screen.width/4 - p1ScoreWindow.getSize().x/2, 60));
    sf::RenderWindow p2ScoreWindow(sf::VideoMode(190, 150), "", sf::Style::Titlebar | sf::Style::Close);
    p2ScoreWindow.setPosition(sf::Vector2i((screen.width/4)*3 - p2ScoreWindow.getSize().x/2, 60));


    sf::Image icon;
    if (icon.loadFromFile("icon.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        p1.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        p2.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        ball.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    //scoring
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text p1score("0", font);
    p1score.setCharacterSize(100);
    p1score.setFillColor(sf::Color::White);
    p1score.setStyle(sf::Text::Bold);
    p1score.setOrigin(p1score.getLocalBounds().left + 100, 0);
    p1score.setPosition(p1ScoreWindow.getSize().x/2 + 34, 15);

    sf::Text p2score("0", font);
    p2score.setCharacterSize(100);
    p2score.setFillColor(sf::Color::White);
    p2score.setStyle(sf::Text::Bold);
    p2score.setOrigin(p2score.getLocalBounds().left + 100, 0);
    p2score.setPosition(p2ScoreWindow.getSize().x/2 + 34, 15);

    sf::Text rallyText("0", font);
    rallyText.setCharacterSize(100);
    rallyText.setFillColor(sf::Color::White);
    rallyText.setStyle(sf::Text::Bold);
    rallyText.setOrigin(rallyText.getLocalBounds().left + 50, 0);
    rallyText.setPosition(rallyWindow.getSize().x/2 + 22, 15);
    sf::Clock rallyCooldown;
    const sf::Time rallyCooldownTime = sf::seconds(1.0f);


    long long int score1 = 0;
    long long int score2 = 0;
    long long int rally = 0;

    sf::Vector2f velocity(0.35, 0.35);
    sf::Vector2i ballPosition = ball.getPosition();
    sf::Vector2i p1Position = p1.getPosition();
    sf::Vector2i p2Position = p2.getPosition();

    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Event ballevent;
        while (ball.pollEvent(ballevent)) {
            if (ballevent.type == sf::Event::Closed)
                ball.close();
        }
        sf::Event p1event;
        while (p1.pollEvent(p1event)) {
            if (p1event.type == sf::Event::Closed)
                p1.close();
        }
        sf::Event p2event;
        while (p2.pollEvent(p2event)) {
            if (p2event.type == sf::Event::Closed)
                p2.close();
        }
        sf::Event rallyevent;
        while (rallyWindow.pollEvent(rallyevent)) {
            if (rallyevent.type == sf::Event::Closed)
                rallyWindow.close();
        }
        sf::Event pscoreevent;
        while (p1ScoreWindow.pollEvent(pscoreevent)) {
            if (pscoreevent.type == sf::Event::Closed)
                p1ScoreWindow.close();
        }
        sf::Event p2scoreevent;
        while (p2ScoreWindow.pollEvent(p2scoreevent)) {
            if (p2scoreevent.type == sf::Event::Closed)
                p2ScoreWindow.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            ball.close();
            window.close();
            p1.close();
            p2.close();
            rallyWindow.close();
            p1ScoreWindow.close();
            p2ScoreWindow.close();
        }
        ballPosition = ball.getPosition();
        p1Position = p1.getPosition();
        p2Position = p2.getPosition();

        // Update ball position
        x += dx;
        y += dy;

        // Boundary bounce
        if (x < 0 ) {
            p1score.setString(std::to_string(++score1));
            rally = 0;

            x = screen.width / 2 - 37;  // Initial x position
            y = screen.height / 2 - 25;  // Initial y position
            dx = -dx; // Reverse horizontal direction on collision
        }
        if(x + ball.getSize().x > screen.width){
            p2score.setString(std::to_string(++score2));
            rally = 0;

            x = screen.width / 2 - 37;  // Initial x position
            y = screen.height / 2 - 25;  // Initial y position
            dx = -dx; // Reverse horizontal direction on collision
        }
        if (y < 0 || y + ball.getSize().y > screen.height - 60) {
            dy = -dy; // Reverse vertical direction on collision
        }

        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && p1.getPosition().y > 0 + 15) {
            p1Position.y -= 4;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && p1.getPosition().y < screen.height - 150) {
            p1Position.y += 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && p2.getPosition().y > 0 + 15) {
            p2Position.y -= 4;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && p2.getPosition().y < screen.height - 150) {
            p2Position.y += 4;
        }

        sf::FloatRect p1Hitbox(p1.getPosition().x, p1.getPosition().y, p1.getSize().x, p1.getSize().y);
        sf::FloatRect p2Hitbox(p2.getPosition().x, p2.getPosition().y, p2.getSize().x, p2.getSize().y);
        sf::FloatRect ballHitbox(ball.getPosition().x, ball.getPosition().y, ball.getSize().x, ball.getSize().y);

        if (ballHitbox.intersects(p1Hitbox)) {
            // Calculate where from center the ball hit
            float relativeIntersectY = (p1.getPosition().y + p1.getSize().y / 2) - (ball.getPosition().y + ball.getSize().y / 2);

            // Normalize between -1 and 1
            float normalizedRelativeIntersectY = relativeIntersectY / (p1.getSize().y / 2);

            // Calculate the bounce angle based on the normalized relative position
            float bounceAngle = normalizedRelativeIntersectY * 60.0f; // Adjust the bounce angle as needed

            // Convert bounce angle to radians
            float bounceAngleRadians = bounceAngle * 3.14159265359 / 180.0;

            // Update the direction of the ball
            dx = velocity.x * cos(bounceAngleRadians);
            dy = velocity.y * sin(bounceAngleRadians);

            if (rallyCooldown.getElapsedTime() > rallyCooldownTime) {

                ++rally;
                rallyCooldown.restart();
            }
        }
        if (ballHitbox.intersects(p2Hitbox)) {
            // Calculate where from the center the ball hit
            float relativeIntersectY = (p2.getPosition().y + p2.getSize().y / 2) - (ball.getPosition().y + ball.getSize().y / 2);

            // Normalize between -1 and 1
            float normalizedRelativeIntersectY = relativeIntersectY / (p2.getSize().y / 2);

            // Calculate the bounce angle based on the normalized relative position
            float bounceAngle = normalizedRelativeIntersectY * 60.0f; // Adjust the bounce angle as needed

            // Convert bounce angle to radians
            float bounceAngleRadians = bounceAngle * 3.14159265359 / 180.0;

            // Update the direction of the ball
            dx = -velocity.x * cos(bounceAngleRadians);
            dy = velocity.y * sin(bounceAngleRadians);

            if (rallyCooldown.getElapsedTime() > rallyCooldownTime) {

                ++rally;
                rallyCooldown.restart();
            }
        }

        rallyText.setString(std::to_string(rally));


        rallyWindow.clear();
        rallyWindow.draw(rallyText);
        rallyWindow.display();

        p1ScoreWindow.clear();
        p1ScoreWindow.draw(p1score);
        p1ScoreWindow.display();

        p2ScoreWindow.clear();
        p2ScoreWindow.draw(p2score);
        p2ScoreWindow.display();

        // Clear the screen
        window.clear();

        // Update the window
        window.display();
        ball.setPosition(sf::Vector2i(x, y));
        ball.clear();
        //ball.display();
        p1.setPosition(p1Position);
        //p1.display();
        p2.setPosition(p2Position);
        //p2.display();

    }

    return EXIT_SUCCESS;
}
