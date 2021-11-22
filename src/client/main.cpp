#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "../shared/state.h"

using namespace std;
using namespace state;

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
            StateLayer layer(state, window);
            layer.initLayer(state);
        
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                // render
                layer.draw(window);
            }
            return 0;
        }
            
        }
    cout << temp[1];
    return 0;
}
}
