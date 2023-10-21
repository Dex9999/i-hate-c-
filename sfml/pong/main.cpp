#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>
//for context windows hates to_string

int main()
{
    //system specific speeds so i dont change every time
    #ifdef _WIN32
    sf::Vector2f velocity(0.15, 0.15);
    float paddleSpeed = 0.25;
    #elif defined(__linux__)
    sf::Vector2f velocity(0.35, 0.35);
    float paddleSpeed = 1;
    #endif

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong!");

    sf::Color white(0xFFFFFFFF);
    sf::CircleShape ball(25.0);
    ball.setFillColor(white);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setPosition(window.getSize().x/2,window.getSize().y/2);

    sf::Image icon;
    if (icon.loadFromFile("icon.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    //sf::Texture ballTexture;
    //if (ballTexture.loadFromFile("pong.png")) {
    //    ball.setTexture(&ballTexture);
    //}

    sf::RectangleShape p1;
    p1.setSize(sf::Vector2f(20, 125));
    p1.setFillColor(white);
    p1.setOrigin(5, 2.5);
    p1.setPosition(30,20);

    sf::RectangleShape p2;
    p2.setSize(sf::Vector2f(20, 125));
    p2.setFillColor(white);
    p2.setOrigin(5, 2.5);
    p2.setPosition(window.getSize().x-30,window.getSize().y-125-20);

    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text p1score("0", font);
    p1score.setCharacterSize(100);
    p1score.setFillColor(sf::Color::White);
    p1score.setStyle(sf::Text::Bold);
    p1score.setOrigin(p1score.getLocalBounds().left + 100, 0);
    p1score.setPosition(250, 15);

    sf::Text p2score("0", font);
    p2score.setCharacterSize(100);
    p2score.setFillColor(sf::Color::White);
    p2score.setStyle(sf::Text::Bold);
    p2score.setOrigin(p2score.getLocalBounds().left + 100, 0);
    p2score.setPosition(window.getSize().x-50, 15);
    sf::Text rallyText("0", font);
        rallyText.setCharacterSize(150);
        rallyText.setFillColor(sf::Color::White);
        rallyText.setStyle(sf::Text::Bold);
        rallyText.setOrigin(rallyText.getLocalBounds().left + 100, 0);
        rallyText.setPosition(window.getSize().x/2+100, 15);

        sf::Text label("Rally:", font);
        label.setCharacterSize(30);
        label.setFillColor(sf::Color::White);
        //label.setStyle(sf::Text::Bold);
        label.setOrigin(label.getLocalBounds().left + 100, 0);
        label.setPosition(window.getSize().x/2+95, 5);
        long long int score1 = 0;
                long long int score2 = 0;
                long long int rally = 0;
                sf::Clock rallyClock;

                while (window.isOpen())
                {

                    std::stringstream ss;

                    // Process events
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }

                    // boundary bounce
                    //x reset as they're points
                    if(ball.getPosition().x > window.getSize().x - 25){
                        //flip velocity x
                        ss << ++score1;
                        p1score.setString(ss.str());
                        ss.str("");

                        //linux vv
                        //p1score.setString(std::to_string(++score1));
                        rally = 0;
                        velocity.x = -velocity.x;
                        ball.setPosition(window.getSize().x/2,window.getSize().y/2);
                    } else if (ball.getPosition().x < 0 + 25){
                        ss << ++score2;
                        p2score.setString(ss.str());
                        ss.str("");
                        //p2score.setString(std::to_string(++score2));
                        rally = 0;
                        velocity.x = -velocity.x;

                        ball.setPosition(window.getSize().x/2,window.getSize().y/2);
                    }

                    if(ball.getPosition().y > window.getSize().y - 25){
                        //flip velocity y
                        velocity.y = -velocity.y;
                    } else if (ball.getPosition().y < 0 + 25){
                        velocity.y = -velocity.y;
                    }

                    //movement
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && p1.getPosition().y>0+15){
                        p1.move(0,-paddleSpeed);
                    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && p1.getPosition().y<window.getSize().y-150){
                        p1.move(0,paddleSpeed);
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && p2.getPosition().y>0+15){
                        p2.move(0,-paddleSpeed);
                    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && p2.getPosition().y<window.getSize().y-150){
                        p2.move(0,paddleSpeed);
                    }

                    if (ball.getGlobalBounds().intersects(p1.getGlobalBounds())) {
                        velocity.x = -velocity.x;

                        // calculate where from center the ball hit
                        float relativeIntersectY = (p1.getPosition().y + p1.getSize().y / 2) - ball.getPosition().y;

                        // normalize between -1 and 1
                        float normalizedRelativeIntersectY = relativeIntersectY / (p1.getSize().y / 2);

                        // bounce angle based on the normalized relative position
                        float bounceAngle = normalizedRelativeIntersectY * 90.f;

                        // y velocity
                        float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
                        float angleRadians = bounceAngle * 3.1415926535897932384626433832795028841971693993751f / 180.f;
                        velocity.y = -speed * std::sin(angleRadians);

                        if (rallyClock.getElapsedTime().asSeconds() >= 0.5) {
                            ++rally;
                            rallyClock.restart();
                        }
                    }

                    if (ball.getGlobalBounds().intersects(p2.getGlobalBounds())) {
                        velocity.x = -velocity.x;

                        // calculate where from center the ball hit
                        float relativeIntersectY = (p2.getPosition().y + p2.getSize().y / 2) - ball.getPosition().y;

                        // normalize between -1 and 1
                        float normalizedRelativeIntersectY = relativeIntersectY / (p2.getSize().y / 2);

                        // bounce angle based on the normalized relative position
                        float bounceAngle = normalizedRelativeIntersectY * 90.0f;

                        // y velocity
                        float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
                        float angleRadians = bounceAngle * 3.1415926535897932384626433832795028841971693993751f / 180.f;
                        velocity.y = -speed * std::sin(angleRadians);

                        if (rallyClock.getElapsedTime().asSeconds() >= 0.5) {
                            ++rally;
                            rallyClock.restart();
                        }
                    }

                    ss << rally;
                    rallyText.setString(ss.str());
                    ss.str("");
                    //rallyText.setString(std::to_string(rally));



                    //fix score offset
                    p1score.setOrigin(p2score.getLocalBounds().left + 100, 0);
                    p1score.setPosition(250, 15);
                    p2score.setOrigin(p2score.getLocalBounds().left + 100, 0);
                    p2score.setPosition(window.getSize().x-50, 15);



                    // Clear screen
                    window.clear();
                    if(score1 == 11 || score2 == 11){
                        rallyText.setString("Game Over!");
                        rallyText.setCharacterSize(100);
                        rallyText.setPosition(window.getSize().x/2-125, window.getSize().y/2-150);
                        window.draw(rallyText);
                    } else{
                        //move the ball after all that phew
                        sf::Vector2f ballPosition = ball.getPosition();
                        ballPosition.x += velocity.x;
                        ballPosition.y += velocity.y;
                        ball.setPosition(ballPosition);
                        window.draw(p1score);
                        window.draw(p2score);
                        window.draw(rallyText);
                        window.draw(label);
                        window.draw(ball);
                        window.draw(p1);
                        window.draw(p2);
                    }

                    // Update the window
                    window.display();
                }

                return EXIT_SUCCESS;
            }
