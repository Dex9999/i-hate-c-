#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 400), "REACTANGLE??!");

    sf::RectangleShape rect1;
    rect1.setSize(sf::Vector2f(40,20));
    rect1.setFillColor(sf::Color::Black);
    rect1.setOrigin(rect1.getSize().x/2,rect1.getSize().y/2);
    rect1.setPosition(window.getSize().x/2,50);
    sf::Vector2f velocity(0,5);

    sf::RectangleShape rect2;
    rect2.setSize(sf::Vector2f(20,40));
    rect2.setFillColor(sf::Color::Blue);
    rect2.setOrigin(rect2.getSize().x/2,rect2.getSize().y/2);
    rect2.setPosition(window.getSize().x-50,window.getSize().y/2);
    sf::Vector2f velocity2(5,0);

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

        if(rect1.getPosition().y > window.getSize().y || rect1.getPosition().y < 0){
            velocity.y *= -1;
        } else if(rect1.getPosition().x > window.getSize().x || rect1.getPosition().x < 0){
            velocity.x *= -1;
        }

        if(rect2.getPosition().x > window.getSize().x || rect2.getPosition().x < 0){
            velocity2.x *= -1;
        } else if(rect2.getPosition().y > window.getSize().y || rect2.getPosition().y < 0){
            velocity2.y *= -1;
        }

        if(rect1.getGlobalBounds().intersects(rect2.getGlobalBounds())){
            if(velocity.x > 0){
                    velocity.y = velocity.x;
                    velocity.x = 0;
            } else if (velocity.x < 0){
                    velocity.y = velocity.x;
                    velocity.x = 0;
            } else if (velocity.y > 0){
                    velocity.x = velocity.y;
                    velocity.y = 0;
            } else if (velocity.y < 0){
                    velocity.x = velocity.y;
                    velocity.y = 0;
            }

            if(velocity2.x > 0){
                    velocity2.y = velocity2.x;
                    velocity2.x = 0;
            } else if (velocity2.x < 0){
                    velocity2.y = velocity2.x;
                    velocity2.x = 0;
            } else if(velocity2.y > 0){
                    velocity2.x = velocity2.y;
                    velocity2.y = 0;
            } else if (velocity2.y < 0){
                    velocity2.x = velocity2.y;
                    velocity2.y = 0;
            }
        }

        rect1.move(velocity.x,velocity.y);
        rect2.move(velocity2.x,velocity2.y);

        window.clear(sf::Color::White);

        window.draw(rect1);
        window.draw(rect2);

        window.display();
    }

    return EXIT_SUCCESS;
}
