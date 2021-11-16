
#include <iostream>
#include <SFML/Graphics.hpp>

void afficheState(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "UAGT", sf::Style::Default);
    sf::Texture texture;
    if (!texture.loadFromFile("res/archer.png")){
        std::cout << "\nOOPSIE DOOPSIE\n";
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    window.setMouseCursorVisible(false);
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        sf::CircleShape shape(50.f);
        shape.setFillColor(sf::Color(100, 250, 50));
        shape.setPosition(10.f, 50.f);
        sprite.setPosition(20, 30);
        window.draw(shape);
        window.draw(sprite);
        window.display();
    }
}