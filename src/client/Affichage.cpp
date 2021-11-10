

#include <SFML/Graphics.hpp>

void afficheState(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "UAGT", sf::Style::Default);
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
    }
}