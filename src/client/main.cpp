#include <iostream>

#include <fstream>
#include <string.h>
#include <sstream>
#include <map>
#include <memory>
#include <unistd.h>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne


void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "Affichage.cpp"

#include "../shared/state.h"
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
    string hi = "hello";
    string stat = "state";


    if(argc >= 2){
        if(argv[1] == hi){
            cout << "Bonjour le monde !" << endl;
        }
        else if(argv[1] == stat){
            cout << "go faire make test" << endl;
        }
        else if(argv[1] == rend){
            afficheState();
        }
        else if (strcmp(argv[1], "render") == 0)
        {
            cout << "--- Render ---" << endl;
            State state{"render"};
            state.initMap();
            state.initPersonnage(Mage,42,42);
            state.initPersonnage(Archer,90,90);
            state.initPersonnage(Guerrier,300,160);
            state.initPersonnage(Mage,42,160);
            state.initPersonnage(Archer,350,80);
            Position newPosition;
            newPosition.setX(100);
            newPosition.setY(200);
            state.getPersonnages()[2]->setPosition(newPosition);
            sf::RenderWindow window(sf::VideoMode(state.getMap()[0].size() * 16 + 256, state.getMap().size() * 16 + 32, 32), "map");
            window.setSize(sf::Vector2u(2624, 1408));
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
            Slayer.initSprite();
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                // render
                Slayer.draw(window);
            }
            return 0;
        }
            
    }
    return 0;
}

