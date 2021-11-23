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
    std::vector<int> temp;


    if(argc >= 2){
        if(argv[1] == hi){
            cout << "Bonjour le monde !" << endl;
        }
        else if(argv[1] == stat){
            cout << "Pas encore de test :/" << endl;
        }
        else if (strcmp(argv[1], "render") == 0)
        {
            cout << "--- Render ---" << endl;
            State state{"render"};
            state.initMap();
            sf::RenderWindow window(sf::VideoMode(state.getMap()[0].size() * 32 + 256, state.getMap().size() * 32 + 32, 32), "map");
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
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
    cout << temp[1];
    return 0;
}

