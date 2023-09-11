#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Proof of Concept!");
	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text text("Hello there!", font);
	text.setCharacterSize(70);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	//text.setPosition(50,0);
	sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, 0);
    text.setPosition(window.getSize().x / 2, 0);
	sf::Texture texture;
	texture.loadFromFile("bb.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	//sprite.setPosition(50,100);;
	sprite.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 3);
    sprite.setPosition(window.getSize().x / 2, window.getSize().y / 3);

  while (window.isOpen())
  {

    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    window.draw(text);
		window.draw(sprite);
    window.display();

  }

  return 0;
}
