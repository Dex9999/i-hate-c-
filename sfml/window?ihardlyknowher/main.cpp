#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1, 1), "Pong!");

    sf::RenderWindow ball(sf::VideoMode(400, 200), "boing");
    sf::Color red(0xBF1304FF);
    sf::Color white(0xFFFFFFFF);
    //ball.setFillColor(red);
    ball.setPosition(sf::Vector2i(screen.width/2-37,screen.height/2-25));

    //ballpos floats
    float x = 0.0f;  // Initial x position
    float y = 0.0f;  // Initial y position

    float dx = 2.0f; // Horizontal speed
    float dy = 2.0f; // Vertical speed

    sf::Image icon;
    if (icon.loadFromFile("icon.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    sf::RenderWindow p1(sf::VideoMode(20, 125), "p1");
    //sf::RectangleShape p1;
    //p1.setSize(sf::Vector2f(20, 125));
    //p1.setFillColor(white);
    //p1.setOrigin(5, 2.5);
    p1.setPosition(sf::Vector2i(30,20));

    // sf::RectangleShape p2;
    // p2.setSize(sf::Vector2f(20, 125));
    // p2.setFillColor(white);
    // p2.setOrigin(5, 2.5);
    // p2.setPosition(window.getSize().x-30,window.getSize().y-125-20);

    long long int score1 = 0;
    long long int score2 = 0;
    long long int rally = 0;

    bool p1hit = false;

    sf::Vector2f velocity(0.35, 0.35);
    sf::Vector2i ballPosition = ball.getPosition();
    sf::Vector2i p1Position = p1.getPosition();

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ballPosition = ball.getPosition();
        p1Position = p1.getPosition();

        //update ball pos
        x += dx;
        y += dy;

        // boundary bounce
        //x reset as they're points
        if (x < 0 || x + ball.getSize().x > screen.width) {
            dx = -dx; // Reverse horizontal direction on collision

            // rally = 0;

            // velocity.x = -velocity.x;
            // ball.setPosition(sf::Vector2i(screen.width/2,window.getSize().y/2));
        }
        if (y < 0 || y + ball.getSize().y > screen.height) {
            dy = -dy; // Reverse vertical direction on collision
            // velocity.y = -velocity.y;
        }


        //movement
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && p1.getPosition().y>0+15){
            p1Position.y -= 1;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && p1.getPosition().y<window.getSize().y-150){
            p1Position.y += 1;
        }

        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && p2.getPosition().y>0+15){
        //     p2.move(0,-1);
        // } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && p2.getPosition().y<window.getSize().y-150){
        //     p2.move(0,1);
        // }
        if(ballPosition.x - p1Position.x == 0 && ballPosition.y - p1Position.y <= 100){
            p1hit = true;
        } else {
            p1hit = false;
        }

        if (p1hit) {
            velocity.x = -velocity.x;

            // calculate where from center the ball hit
            float relativeIntersectY = (p1.getPosition().y + p1.getSize().y / 2) - ball.getPosition().y;

            // normalize between -1 and 1
            float normalizedRelativeIntersectY = relativeIntersectY / (p1.getSize().y / 2);

            // bounce angle based on the normalized relative position
            float bounceAngle = normalizedRelativeIntersectY * 90.0f;

            // y velocity
            float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
            float angleRadians = bounceAngle * 3.1415926535897932384626433832795028841971693993751f / 180.f;
            float dy = -speed * std::sin(angleRadians);
            velocity.y = dy;

            ++rally;
        }

        // if (ball.getGlobalBounds().intersects(p2.getGlobalBounds())) {
        //     velocity.x = -velocity.x;

        //     // calculate where from center the ball hit
        //     float relativeIntersectY = (p2.getPosition().y + p2.getSize().y / 2) - ball.getPosition().y;

        //     // normalize between -1 and 1
        //     float normalizedRelativeIntersectY = relativeIntersectY / (p2.getSize().y / 2);

        //     // bounce angle based on the normalized relative position
        //     float bounceAngle = normalizedRelativeIntersectY * 90.0f;

        //     // y velocity
        //     float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        //     float angleRadians = bounceAngle * 3.1415926535897932384626433832795028841971693993751f / 180.f;
        //     float dy = -speed * std::sin(angleRadians);
        //     velocity.y = dy;

        //     ++rally;
        // }

        //rallyText.setString(std::to_string(rally));

        // ballPosition.x += velocity.x;
        // ballPosition.y += velocity.y;

        // ball.setPosition(sf::Vector2i(ballPosition));
        sf::Vector2i ballPosition = ball.getPosition();
        ballPosition.x += velocity.x;
        ballPosition.y += velocity.y;


        // Check for collisions with screen boundaries
        if (ballPosition.x > screen.width || ballPosition.x < 0)
        {
            // Reverse the X velocity when hitting left or right screen boundary
            velocity.x = -velocity.x;
        }

        if (ballPosition.y > screen.height || ballPosition.y < 0)
        {
            // Reverse the Y velocity when hitting top or bottom screen boundary
            velocity.y = -velocity.y;
        }

        ball.setPosition(sf::Vector2i(static_cast<int>(x), static_cast<int>(y)));

        ball.clear();
        ball.display();
        p1.setPosition(p1Position);


        p1.display();

        //fix score offset
        // p1score.setOrigin(p2score.getLocalBounds().left + 100, 0);
        // p1score.setPosition(250, 15);
        // p2score.setOrigin(p2score.getLocalBounds().left + 100, 0);
        // p2score.setPosition(window.getSize().x-50, 15);

        // Clear screen
        window.clear();

        // window.draw(p1score);
        // window.draw(p2score);
        // window.draw(p2);



        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
