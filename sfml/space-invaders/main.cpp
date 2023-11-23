#include "SFML/Graphics.hpp"
#include <vector>
int main(){
  sf::RenderWindow window(sf::VideoMode(600, 650), "Sprites!");
  sf::Clock clock;

  sf::Event event;
  sf::Texture texture;
  texture.loadFromFile("spritesheet.png");

  std::vector<sf::IntRect> textureRectArray;
  std::vector<sf::Sprite> enemyArray;

  sf::Sprite greenNeutral(texture,sf::IntRect(0,0,8,8));
  sf::Sprite greenOpen(texture,sf::IntRect(9,0,8,8));
  sf::Sprite greenDeath(texture,sf::IntRect(103,0,8,8));

  sf::Sprite greenLNeutral(texture,sf::IntRect(0,9,8,8));
  sf::Sprite greenLOpen(texture,sf::IntRect(9,9,8,8));

  sf::Sprite blueNeutral(texture,sf::IntRect(0,36,8,8));
  sf::Sprite blueOpen(texture,sf::IntRect(9,36,8,8));
  sf::Sprite blueDeath(texture,sf::IntRect(103,36,8,8));

  sf::Sprite fatBlueNeutral(texture,sf::IntRect(0,45,8,8));
  sf::Sprite fatBlueOpen(texture,sf::IntRect(9,45,8,8));
  sf::Sprite fatBlueDeath(texture,sf::IntRect(103,36,8,8));

  sf::Sprite pinkNeutral(texture,sf::IntRect(0,72,8,8));
  sf::Sprite pinkOpen(texture,sf::IntRect(9,72,8,8));
  sf::Sprite pinkDeath(texture,sf::IntRect(103,72,8,8));



  greenNeutral.setPosition(100,100);
  greenOpen.setPosition(100,100);
  greenDeath.setPosition(100,100);
  greenNeutral.scale(5,5);
  greenOpen.scale(5,5);
  greenDeath.scale(5,5);

  int currEnemy = 0;
  sf::IntRect tex;

  for(int i = 0; i<11; ++i){
    for(int j = 0; j<5; ++j){
        sf::Sprite indEnemy;

        indEnemy.setTexture(texture);
        indEnemy.setScale(2,2);
        switch(j){
            case 0:
            tex = sf::IntRect(0,0,8,8);
              break;
            case 1:
            tex = sf::IntRect(0,9,8,8);
              break;
            case 2:
            tex = sf::IntRect(0,36,8,8);
              break;
              break;
            case 3:
            tex = sf::IntRect(0,45,8,8);
              break;
            case 4:
            tex = sf::IntRect(0,72,8,8);
              break;
        }
        textureRectArray.push_back(tex);
        indEnemy.setTextureRect(tex);
        indEnemy.setPosition(i*20+100, j*20);
        enemyArray.push_back(indEnemy);
    }
  }

  //it's a 8x8 grid
//  for(texture->getSize().x/;)
  sf::Time elapsed;
  int seconds = 0;
  sf::Vector2f velocity(0.25,0);

  bool bounce = false;


  while (window.isOpen()){
    while (window.pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
        window.close();
    }


    for(int i = 0; i < enemyArray.size(); ++i){
        enemyArray[i].move(velocity.x,velocity.y);

        if(enemyArray[i].getPosition().x > window.getSize().x-15 || enemyArray[i].getPosition().x < 0){
            bounce = 1;
        }

        if(bounce){
            bounce = 0;

            velocity.x *= -1.01;
            for(auto& i: enemyArray){
                i.move(0,15);
            }
        }
     }

    window.clear();

    elapsed = clock.getElapsedTime();
    // force int conversion to floor
    seconds = elapsed.asSeconds();
    if (seconds == 0){
        window.draw(blueNeutral);
    } else if(seconds == 1){
        window.draw(blueOpen);
    } else if (seconds >= 2){
        window.draw(blueDeath);
    }
    if(seconds == 3){
        clock.restart();
    }

    for(int i = 0; i < enemyArray.size(); ++i){
        enemyArray[i].setTextureRect(textureRectArray[i]);
        window.draw(enemyArray[i]);
    }

    window.display();
  }
}
