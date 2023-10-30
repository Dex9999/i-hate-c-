#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <filesystem>
int main()
{
    int currBrick = 0;
    int randomImage = 0;
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Bricks");

    //load silly photos
    std::vector<sf::Texture> images;
    std::vector<std::filesystem::path> directories;
    directories.push_back(std::filesystem::path(getenv("HOME")) / "Documents");
    directories.push_back(std::filesystem::path(getenv("HOME")) / "Downloads");

    for (const std::filesystem::path& dirPath : directories) {
        for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
            std::filesystem::path filePath = entry.path();

            if (std::filesystem::is_regular_file(filePath)) {
                std::string fileName = filePath.filename().string();
                std::string fileExtension = filePath.extension().string();

                // if valid texture image type
                if (fileExtension == ".jpg" || fileExtension == ".gif" || fileExtension == ".png" ||
                    fileExtension == ".bmp" || fileExtension == ".tga" || fileExtension == ".psd" ||
                    fileExtension == ".hdr" || fileExtension == ".pic" || fileExtension == ".pnm") {
                    if(rand() % 100 <= 5){
                        sf::Texture texture;
                        texture.loadFromFile(dirPath / fileName);
                        std::cout << "Loaded " << fileName << " from " << dirPath << "\n";
                        images.push_back(texture);
                    }
                }
            }
        }
    }

    sf::RectangleShape brick[50];
    int brickDmg[50];

    sf::RectangleShape block;

    for (int j = 0; j < 5; ++j)
    {
        for (int i = 0; i < 10; ++i)
        {
            currBrick = i+j*10;

            brick[currBrick].setSize(sf::Vector2f(70, 70));
            brick[currBrick].setPosition(i*80+5, j*70+window.getSize().y/4);


            randomImage = rand() % images.size();
            brick[currBrick].setTexture(&images[randomImage]);

            //[currBrick].setFillColor(sf::Color (rand() % 255 + 0,rand() % 255 + 0,rand() % 255 + 0));
            switch (j)
            {
                case 0:
                    brick[currBrick].setFillColor(sf::Color::Red);
                    brickDmg[currBrick] = 5;
                    break;
                case 1:
                    brick[currBrick].setFillColor(sf::Color (255, 150, 0));
                    brickDmg[currBrick] = 4;
                    break;
                case 2:
                    brick[currBrick].setFillColor(sf::Color::Yellow);
                    brickDmg[currBrick] = 3;
                    break;
                case 3:
                    brick[currBrick].setFillColor(sf::Color::Green);
                    brickDmg[currBrick] = 2;
                    break;
                case 4:
                    brick[currBrick].setFillColor(sf::Color::Blue);
                    brickDmg[currBrick] = 1;
                    break;
                default:
                    break;
            }
        }
    }



    sf::RectangleShape p1;
    p1.setSize(sf::Vector2f(125, 20));
    p1.setFillColor(sf::Color::White);
    p1.setOrigin(5, 2.5);
    p1.setPosition(window.getSize().x/2,window.getSize().y-20);

    sf::Color white(0xFFFFFFFF);
    sf::CircleShape ball(15.0);
    ball.setFillColor(white);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setPosition(window.getSize().x/2,window.getSize().y-550);

    sf::Vector2f velocity(0.35, 0.35);


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

        if(ball.getPosition().x > window.getSize().x - 25 || ball.getPosition().x < 0 + 25)
        {
            velocity.x = -velocity.x;
        }

        if(ball.getPosition().y > window.getSize().y - 25)
        {
            // lose a life
            velocity.y = -velocity.y;
            //ball.setPosition(window.getSize().x/2,window.getSize().y/2);
        }
        else if (ball.getPosition().y < 0 + 25)
        {
            velocity.y = -velocity.y;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && p1.getPosition().x>0+15)
        {
            p1.move(-1,0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && p1.getPosition().x<window.getSize().x-150)
        {
            p1.move(1,0);
        }

        for(int k = 0; k<51; ++k)
        {
            if(k==50)
            {
                block = p1;
            }
            else
            {
                block = brick[k];
            }
            if (ball.getGlobalBounds().intersects(block.getGlobalBounds()))
            {
                if(k<51)
                {


                    switch (brickDmg[k]) {
                        case 0:
                            break;
                        case 1:
                            brick[k].setPosition(0-100,0-100);
                            brickDmg[k] = 0;
                            break;
                        case 2:
                            brick[k].setFillColor(sf::Color::Blue);
                            brickDmg[k] = 1;
                            break;
                        case 3:
                            brick[k].setFillColor(sf::Color::Green);
                            brickDmg[k] = 2;
                            break;
                        case 4:
                            brick[k].setFillColor(sf::Color::Yellow);
                            brickDmg[k] = 3;
                            break;
                        case 5:
                            brick[k].setFillColor(sf::Color (255, 150, 0));
                            brickDmg[k] = 4;
                            break;
                        default:
                            break;
                    }
                }

                //bounce code
                velocity.y = -velocity.y;
                // calculate where from center the ball hit
                float relativeIntersectX = (block.getPosition().x + block.getSize().x / 2) - ball.getPosition().x;

                // normalize between -1 and 1
                float normalizedRelativeIntersectX = relativeIntersectX / (block.getSize().x / 2);

                // bounce angle based on the normalized relative position
                float bounceAngle = normalizedRelativeIntersectX * 90.f;

                // x velocity
                float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
                float angleRadians = bounceAngle * 3.1415926535897932384626433832795028841971693993751f / 180.f;
                velocity.x = -speed * std::sin(angleRadians);

            }

        }

        sf::Vector2f ballPosition = ball.getPosition();
        ballPosition.x += velocity.x;
        ballPosition.y += velocity.y;
        ball.setPosition(ballPosition);

        window.clear();
        for (int i = 0; i < 50; ++i)
        {
            window.draw(brick[i]);
        }
        window.draw(ball);
        window.draw(p1);
        window.display();
    }

    return EXIT_SUCCESS;
}
