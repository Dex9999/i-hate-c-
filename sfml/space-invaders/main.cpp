#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <sstream>

void moveAliens(std::vector<sf::Sprite>&, int, sf::Vector2f&, sf::RenderWindow&);
void animateAliens(std::vector<sf::Sprite>&,std::vector<sf::IntRect>&);
void moveShip(sf::Sprite&, sf::RenderWindow&);
void ohShoot(sf::Sprite &ship, sf::Sprite &bullet, std::vector<sf::Sprite> &enemyArray,std::vector<sf::IntRect>&,sf::Sound&,sf::Sound&);

bool bounce = false;
bool shot = false;
int score = 0;
bool dead = false;

int main() {
    sf::SoundBuffer buffer;
    sf::Sound explode;

    if(!buffer.loadFromFile("explosion.wav"))
        return -1;
    explode.setBuffer(buffer);
    //explode.play();
    sf::SoundBuffer ebuffer;
    sf::Sound shoot;
    if(!ebuffer.loadFromFile("laserShoot.wav"))
        return -1;
    shoot.setBuffer(ebuffer);
    //shoot.play();
    sf::SoundBuffer wbuffer;
    sf::Sound win;
    if(!wbuffer.loadFromFile("win.wav"))
        return -1;
    win.setBuffer(wbuffer);

    sf::SoundBuffer lbuffer;
    sf::Sound lose;
    if(!lbuffer.loadFromFile("lose.wav"))
        return -1;
    lose.setBuffer(lbuffer);
    bool loseSoundPlayed = false;
    bool winSoundPlayed = false;

    sf::RenderWindow window(sf::VideoMode(600, 650), "Sprites!");
    sf::Clock clock;
    sf::Event event;
    sf::Texture texture;
    texture.loadFromFile("spritesheet.png");
    std::vector<sf::IntRect> textureRectArray;
    std::vector<sf::Sprite> enemyArray;
    sf::Sprite ship;
    ship.setTexture(texture);
    ship.setTextureRect(sf::IntRect(115,63,11,8));
    ship.setOrigin(10/2,7/2.0);
    ship.setPosition(window.getSize().x/2,window.getSize().y-30);
    ship.scale(2,2);
    sf::Sprite bullet;
    bullet.setTexture(texture);
    bullet.setTextureRect(sf::IntRect(120,54,1,5));
    bullet.setPosition(10,10);
    bullet.scale(3,3);
    std::stringstream ss;
    /*
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
    */
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text p1score("0", font);
    p1score.setCharacterSize(50);
    p1score.setFillColor(sf::Color::White);
    p1score.setStyle(sf::Text::Bold);
    p1score.setOrigin(p1score.getLocalBounds().left + 100, 0);
    p1score.setPosition(250, 15);

    int currEnemy = 0;
    sf::IntRect tex;
    for(int i = 0; i<11; ++i) {
        for(int j = 0; j<5; ++j) {
            sf::Sprite indEnemy;
            indEnemy.setTexture(texture);
            indEnemy.setScale(2,2);
            switch(j) {
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
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::EventType::Closed)
                window.close();
        }

        moveShip(ship,window);
        ohShoot(ship,bullet,enemyArray, textureRectArray, explode, shoot);
        moveAliens(enemyArray,enemyArray.size(), velocity, window);


        ss << score*100;
        p1score.setString(ss.str());
        ss.str("");

        p1score.setOrigin(p1score.getLocalBounds().left + 100, 0);
        score==0?p1score.setPosition(window.getSize().x, 15):p1score.setPosition(window.getSize().x-50, 15);

        window.clear();
        elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds() >= 0.5) {
            clock.restart();
            animateAliens(enemyArray,textureRectArray);
        }
        for(int i = 0; i < enemyArray.size(); ++i) {
            enemyArray[i].setTextureRect(textureRectArray[i]);
            window.draw(enemyArray[i]);
        }
        if(score >= 55 ||dead){
            dead ? p1score.setString("You Lost!") : p1score.setString("You Win!");
            p1score.setPosition(window.getSize().x/2,window.getSize().y/2);
            window.draw(p1score);
            if (dead) {
                if(!loseSoundPlayed){
                    lose.play();
                    loseSoundPlayed = true;
                }
                window.display();
                clock.restart();
                sf::Time elapsedTime(clock.getElapsedTime());
                while (elapsedTime.asSeconds() < 6.0) {
                    elapsedTime = clock.getElapsedTime();
                }
                window.close();
            } else if (!dead) {
                if(!winSoundPlayed){
                    win.play();
                    winSoundPlayed = true;
                }
                window.display();
                clock.restart();
                sf::Time elapsedTime(clock.getElapsedTime());
                while (elapsedTime.asSeconds() < 6.0) {
                    elapsedTime = clock.getElapsedTime();
                }
                window.close();
            }

            window.close();
        } else{
            window.draw(ship);
            if(shot) {
                window.draw(bullet);
            }
            window.draw(p1score);
            window.display();
        }

    }
}

void moveAliens(std::vector<sf::Sprite> &enemyArray, int length, sf::Vector2f &velocity, sf::RenderWindow &window) {
    for(int i = 0; i < enemyArray.size(); ++i) {
        enemyArray[i].move(velocity.x, velocity.y);
        //rotation 1 is my death remember thingy
        if((enemyArray[i].getPosition().x > window.getSize().x - 15|| enemyArray[i].getPosition().x < 0) && enemyArray[i].getRotation() != 1) {
            bounce = true;
        }
        if(bounce) {
            bounce = false;
            velocity.x *= -1.01;
            for(auto& i : enemyArray) {
                i.move(0, 15);
            }
        }
        if((enemyArray[i].getPosition().y>=window.getSize().y) && enemyArray[i].getRotation() != 1){
            dead = true;
        }
    }
}

void moveShip(sf::Sprite &ship, sf::RenderWindow &window) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && ship.getPosition().x>0+12) {
        ship.move(-1,0);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && ship.getPosition().x<window.getSize().x-15) {
        ship.move(1,0);
    }
}

void ohShoot(sf::Sprite &ship, sf::Sprite &bullet, std::vector<sf::Sprite> &enemyArray,std::vector<sf::IntRect> &textureRectArray,sf::Sound &explode,sf::Sound &shoot) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if(!shot) {
            shot = true;
            shoot.play();
            bullet.setPosition(ship.getPosition());
        }
    }
    if(shot) {
        if(bullet.getPosition().y<0) {
            shot = false;
        } else {
            bullet.move(0,-2);
        }
    }
    for(int i = 0; i < enemyArray.size(); ++i) {
        if(enemyArray[i].getGlobalBounds().intersects(bullet.getGlobalBounds()) && shot && enemyArray[i].getRotation() != 1) {
            //sf::Sprite blank;
            enemyArray[i].setRotation(1);
            explode.play();
            ++score;
            if(textureRectArray[i].top == 9 || textureRectArray[i].top == 45) {
                enemyArray[i].setTextureRect(sf::IntRect(103,textureRectArray[i].top-9,8,8));
                textureRectArray[i] = sf::IntRect(103,textureRectArray[i].top-9,8,8);
            } else {
                enemyArray[i].setTextureRect(sf::IntRect(103,textureRectArray[i].top,8,8));
                textureRectArray[i] = sf::IntRect(103,textureRectArray[i].top,8,8);
            }
            //enemyArray[i] = blank;
            shot = !shot;
        }
    }
}


void animateAliens(std::vector<sf::Sprite> &enemyArray,std::vector<sf::IntRect> &textureRectArray) {
    for(int i = 0; i<enemyArray.size(); ++i) {
        int newLeft;
        // I'm able to hardcode because the spritesheet is nicely proportional
        if(enemyArray[i].getRotation() == 1) {
            sf::Sprite blank;
            blank.setRotation(1);
            enemyArray[i] = blank;
        } else {
            if(textureRectArray[i].left != 0) {
                newLeft = 0;
            } else {
                newLeft = 9;
            }
        }
        enemyArray[i].setTextureRect(sf::IntRect(newLeft,textureRectArray[i].top,8,8));
        textureRectArray[i] = sf::IntRect(newLeft,textureRectArray[i].top,8,8);
    }
}

