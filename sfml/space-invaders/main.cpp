#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <sstream>

void moveAliens(std::vector<sf::Sprite>&, int, sf::Vector2f&, sf::RenderWindow&);
void animateAliens(std::vector<sf::Sprite>&,std::vector<sf::IntRect>&);
void moveShip(sf::Sprite&, sf::RenderWindow&);
void ohShoot(sf::Sprite&, sf::Sprite&, std::vector<sf::Sprite>&,std::vector<sf::IntRect>&,sf::Sound&,sf::Sound&);

bool bounce = false;
bool shot = false;
int score = 0;
bool dead = false;

bool fatFire = false;
sf::Clock bulletClock;
bool pierce = false;
sf::Clock pClock;
sf::Vector2f velocity(0.035,0);
bool slow = true;
sf::Clock sClock;

int main() {
    //music is same among rounds
    sf::Music music;
    if (!music.openFromFile("music.wav"))
        return -1;
    music.setLoop(true);
    music.play();

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



    sf::RenderWindow window(sf::VideoMode(600, 650), "Space Invader? I Hardly Know Her!");
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

        //proof of concept
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && !fatFire) {
            fatFire = true;
            bullet.setScale(24,8);
            bulletClock.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && !pierce) {
            pierce = true;
            pClock.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !slow) {
            if (velocity.x > 0) {
                velocity.x -= 0.07;
            } else if (velocity.x < 0) {
                velocity.x += 0.07;
            }

            slow = true;
            sClock.restart();
        }

        if (sClock.getElapsedTime().asSeconds() >= 0.25 && slow) {
            if (velocity.x > 0) {
                velocity.x += 0.07;
            } else if (velocity.x < 0) {
                velocity.x -= 0.07;
            }

            slow = false;
        }


        p1score.setOrigin(p1score.getLocalBounds().left + 100, 0);
        score==0?p1score.setPosition(window.getSize().x, 15):p1score.setPosition(window.getSize().x-50, 15);
        score>=100?p1score.setPosition(window.getSize().x-100, 15):p1score.setPosition(window.getSize().x-50, 15);
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
        if(score >= 165 ||dead){
            music.stop();
            ss << score*100;
            dead ? p1score.setString("   You Lost!\nFinal Score:\n"+ss.str()) : p1score.setString("You Win!");
            ss.str("");
            dead ? p1score.setPosition(window.getSize().x/2-50,window.getSize().y/2-50) : p1score.setPosition(window.getSize().x/2,window.getSize().y/2);

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
        if((enemyArray[i].getPosition().y>=window.getSize().y-50) && enemyArray[i].getRotation() != 1){
            dead = true;
        }
    }
}

void moveShip(sf::Sprite &ship, sf::RenderWindow &window) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && ship.getPosition().x>0+12) {
        ship.move(-0.25,0);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && ship.getPosition().x<window.getSize().x-15) {
        ship.move(0.25,0);
    }
}
int hit = 0;
void ohShoot(sf::Sprite &ship, sf::Sprite &bullet, std::vector<sf::Sprite> &enemyArray,std::vector<sf::IntRect> &textureRectArray,sf::Sound &explode,sf::Sound &shoot) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if(!shot) {
            shot = true;
            shoot.play();
            bullet.setPosition(ship.getPosition());

            if(bulletClock.getElapsedTime().asSeconds() > 3 && fatFire == true){
                bullet.setScale(6,3);
                fatFire = false;
            } else if (!fatFire){
                bulletClock.restart();
            }
            if(pClock.getElapsedTime().asSeconds() > 3 && pierce == true){
                pierce = false;
            } else if (!pierce){
                pClock.restart();
            }
        }
    }
    if(shot) {
        if(bullet.getPosition().y<0) {
            shot = false;
        } else {
            bullet.move(0,-0.5);
        }
    }

    for(int i = 0; i < enemyArray.size(); ++i) {

        if(enemyArray[i].getGlobalBounds().intersects(bullet.getGlobalBounds()) && shot && enemyArray[i].getRotation() != 1) {
            //sf::Sprite blank;
            enemyArray[i].setRotation(1);
            explode.play();
            /*
            (0)(5)(10)(15)(20)
            (1)(6)(11)(16)(21)
            (2)(7)(12)(17)(22)
            (3)(8)(13)(18)(23)
            (4)(9)(14)(19)(24)
            */
            if(i%5 == 0)
                score+=5;
            if(i%5 == 1)
                score+=4;
            if(i%5 == 2)
                score+=3;
            if(i%5 == 3)
                score+=2;
            if(i%5 == 4)
                score+=1;

            if(textureRectArray[i].top == 9 || textureRectArray[i].top == 45) {
                enemyArray[i].setTextureRect(sf::IntRect(103,textureRectArray[i].top-9,8,8));
                textureRectArray[i] = sf::IntRect(103,textureRectArray[i].top-9,8,8);
            } else {
                enemyArray[i].setTextureRect(sf::IntRect(103,textureRectArray[i].top,8,8));
                textureRectArray[i] = sf::IntRect(103,textureRectArray[i].top,8,8);
            }
            //enemyArray[i] = blank;
            if(fatFire){
                if(i == enemyArray.size()-1){
                shot = !shot;
                }
            } else if (pierce){
                hit++;
                if(hit >= 2 || i == enemyArray.size()-1){ // Modify condition to check if the bullet pierced 2 aliens
                    shot = !shot;
                    hit = 0;
                }
            } else {
                shot = !shot;
            }
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

