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
#include "../shared/engine.h"
#include "../shared/ai.h"

using namespace std;
using namespace state;
using namespace render;
using namespace engine;

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
        /*else if(argv[1] == rend){
            afficheState();
        }*/
        else if (strcmp(argv[1], "render") == 0)
        {
            cout << "--- Render ---" << endl;
            State state{"render"};
            state.map.initMap();
            state.initPersonnage(Mage,2,2);
            state.initPersonnage(Archer,5,5);
            state.initPersonnage(Guerrier,5,6);
            state.initPersonnage(Mage,6,5);
            state.initPersonnage(Archer,10,2);
            Position newPosition;
            newPosition.setX(10);
            newPosition.setY(10);
            state.getPersonnages()[2]->setPosition(newPosition);
            sf::RenderWindow window(sf::VideoMode(state.map.layout[0].size() * 16 + 256, state.map.layout.size() * 16 + 32, 32), "map");
            //window.setSize(sf::Vector2u(2624, 1408));
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
        else if (strcmp(argv[1], "engine") == 0){
            State state{"render"};
            state.map.initMap();
            state.initPersonnage(Mage,2,2);
            state.initPersonnage(Archer,5,5);
            state.initPersonnage(Guerrier,5,6);
            state.initPersonnage(Mage,6,5);
            state.initPersonnage(Archer,10,2);
            //todo changer ordre position initperso
            sf::RenderWindow window(sf::VideoMode(state.map.layout[0].size() * 16 + 256, state.map.layout.size() * 16 + 32, 32), "map");
            //window.setSize(sf::Vector2u(2624, 1408));
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
            Slayer.initSprite();
            int commandCmpt = 0;
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                Slayer.draw(window);
                sleep(3);
                switch(commandCmpt){
                    case 0 : {MoveCommand premierMove(*state.map.layout[2][3]);
                        state.activePlayer = state.getPersonnages()[0];
                        premierMove.Execute(state);}
                    break;
                    case 1 : {AttackCommand premierAtk(*state.map.layout[5][5]);
                        premierAtk.Execute(state);}
                    break;
                    case 2 : {MoveCommand deuxiemeMove(*state.map.layout[8][8]);
                        state.activePlayer = state.getPersonnages()[2];
                        deuxiemeMove.Execute(state);}
                    break;
                    case 3 : {MoveCommand troisiemeMove(*state.map.layout[7][6]);
                        troisiemeMove.Execute(state);}
                    break;
                    case 4 : {AttackCommand deuxiemeAtk(*state.map.layout[3][3]);
                        deuxiemeAtk.Execute(state);}
                    break;
                    case 5 : {MoveCommand quatriemeMove(*state.map.layout[7][5]);
                        state.activePlayer = state.getPersonnages()[3];
                        quatriemeMove.Execute(state);}
                    break;
                    case 6 : {AttackCommand troisiemeAtk(*state.map.layout[2][10]);
                        troisiemeAtk.Execute(state);}
                    break;
                    default : cout << "fin de la démo\n";
                    break;
                }
                commandCmpt++;
                cout << "\n";
            }
        }
        else if (strcmp(argv[1], "randomAI") == 0){
            cout << "--- randomAI ---" << endl;
            engine::Engine ngine;
            State state{"render"};
            
            state.map.initMap();
            state.initPersonnage(Mage,2,2);
            state.initPersonnage(Archer,5,5);
            state.initPersonnage(Guerrier,5,6);
            state.initPersonnage(Mage,6,5);
            state.initPersonnage(Archer,10,2);
            //todo changer ordre position initperso
            sf::RenderWindow window(sf::VideoMode(state.map.layout[0].size() * 16 + 256, state.map.layout.size() * 16 + 32, 32), "map");
            //window.setSize(sf::Vector2u(2624, 1408));
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
            Slayer.initSprite();
            
            ai::RandomAI rai;
            
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                Slayer.draw(window);
                sleep(3);
                cout << "--- Selection du personnage aléatoirement ---"<< endl;
                rai.selectPersonnage(state);
                
                rai.run(ngine,state);
                
            }
                
            
            
        }
    }
    return 0;
}

