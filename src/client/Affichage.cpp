
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
    sprite.scale(4,4);
    sprite.setColor(sf::Color::Magenta);
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        sf::CircleShape shape(50.f);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(10.f, 50.f);
        sprite.setTextureRect(sf::IntRect(92, 18, 13, 22));
        sprite.setPosition(20, 30);
        window.draw(shape);
        window.draw(sprite);
        window.display();
    }
}

void drawMap(sf::RenderWindow window){
    sf::Sprite spriteV2;
    sf::Texture textureV2;
    if (!textureV2.loadFromFile("res/Isometric_MedievalFantasy_Tiles.png")){
        std::cout << "\nOOPSIE DOOPSIE may biggie\n";
    }
}