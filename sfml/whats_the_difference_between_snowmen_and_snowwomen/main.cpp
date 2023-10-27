// SNOWBALLS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

int main()
{
    int numOfBalls = 1000;
    int randPos = 0;
    int randPosY = 0;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SNOWBALLS!!!");

    long long tim = time(NULL);
    srand(tim);

    sf::CircleShape circleArray[numOfBalls];
    float speedArray[numOfBalls];

    for(int i = 0; i < numOfBalls; ++i){
        randPos = rand() % (window.getSize().x-10);
        randPosY = rand() % (window.getSize().y-10);
        circleArray[i].setPosition(randPos,randPosY);
        circleArray[i].setRadius(4);
        //confetti
        //circleArray[i].setFillColor(sf::Color (rand() % 255 + 0,rand() % 255 + 0,rand() % 255 + 0));

        speedArray[i] = (rand() % 10 + 1)/10.f;
    }

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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }

        // Clear screen
        window.clear();

        for(int j = 0; j < numOfBalls; ++j){
            if(circleArray[j].getPosition().y > window.getSize().y){
                randPos = rand() % (window.getSize().x-10);
                speedArray[j] = (rand() % 10 + 1)/10.f;
                //circleArray[j].setFillColor(sf::Color (rand() % 255 + 0,rand() % 255 + 0,rand() % 255 + 0));
                circleArray[j].setPosition(randPos, 0-10);
            }
            circleArray[j].setRadius((circleArray[j].getPosition().y - window.getSize().y)/20);
            circleArray[j].move(0,speedArray[j]);
            window.draw(circleArray[j]);
        }

        // Draw the sprite
        //window.draw();

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
