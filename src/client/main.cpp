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
            /*state.initPersonnage(Mage,2,2,1);
            state.initPersonnage(Archer,5,5,1);
            state.initPersonnage(Guerrier,5,6,1);
            state.initPersonnage(Mage,6,5,2);
            state.initPersonnage(Archer,10,2,2);
            Position newPosition;
            newPosition.setX(10);
            newPosition.setY(10);
            state.getPersonnages()[2]->setPosition(newPosition);
            */
            state.initPersonnage(Mage,1,1,1);
            state.initPersonnage(Mage,1,3,1);
            state.initPersonnage(Mage,3,1,1);
            state.initPersonnage(Guerrier,5,5,1);
            state.initPersonnage(Guerrier,5,7,1);
            state.initPersonnage(Guerrier,7,5,1);

            state.initPersonnage(Archer,10,10,1);
            state.initPersonnage(Archer,12,10,1);
            state.initPersonnage(Archer,10,12,1);

            sf::RenderWindow window(sf::VideoMode(state.map.layout[0].size() * 16 + 256, state.map.layout.size() * 16 + 32, 32), "map");
            //window.setSize(sf::Vector2u(2624, 1408));
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
            cout << " ----- init sprite ------" << endl;
            Slayer.initSprite();
            cout << " ----- end init sprite ------" << endl;
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
            Engine ngine(state);
            state.map.initMap();
            state.initPersonnage(Mage,2,2,1);
            state.initPersonnage(Archer,5,5,1);
            state.initPersonnage(Guerrier,5,6,1);
            state.initPersonnage(Mage,6,5,2);
            state.initPersonnage(Archer,10,2,2);
            //todo changer ordre position initperso
            sf::RenderWindow window(sf::VideoMode(state.map.layout[0].size() * 16 + 256, state.map.layout.size() * 16 + 32, 32), "map");
            //window.setSize(sf::Vector2u(2624, 1408));
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
            Slayer.initSprite();
            int commandCmpt = 0;
            ngine.Start();
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                Slayer.draw(window);
                if(state.activePlayer == nullptr){
                    sleep(1);
                }
                else {
                    switch(commandCmpt){
                        case 0 : {MoveCommand premierMove(*state.map.layout[2][3]);
                            premierMove.Execute(state);}
                        break;
                        case 1 : {AttackCommand premierAtk(*state.map.layout[5][5]);
                            premierAtk.Execute(state);
                            ngine.EndTurn();}
                        break;
                        case 2 : {MoveCommand deuxiemeMove(*state.map.layout[8][8]);
                            deuxiemeMove.Execute(state);}
                        break;
                        case 3 : {MoveCommand troisiemeMove(*state.map.layout[7][6]);
                            troisiemeMove.Execute(state);}
                        break;
                        case 4 : {AttackCommand deuxiemeAtk(*state.map.layout[3][3]);
                            deuxiemeAtk.Execute(state);
                            ngine.EndTurn();}
                        break;
                        case 5 : {MoveCommand quatriemeMove(*state.map.layout[7][5]);
                            quatriemeMove.Execute(state);}
                        break;
                        case 6 : {AttackCommand troisiemeAtk(*state.map.layout[2][10]);
                            troisiemeAtk.Execute(state);
                            ngine.EndTurn();}
                        break;
                        default : cout << "fin de la démo\n"; state.gameOver = true; ngine.Stop();window.close();
                        break;
                    }
                    commandCmpt++;
                    cout << "\n";
                }
                sleep(1);
            }
        }
        else if (strcmp(argv[1], "randomAI") == 0){
            cout << "--- randomAI ---" << endl;
            State state{"render"};
            engine::Engine ngine(state);
            state.map.initMap();
            //team 1
            state.initPersonnage(Mage,1,11,1);
            state.initPersonnage(Archer,1,12,1);
            state.initPersonnage(Guerrier,1,13,1);
            //team 2
            state.initPersonnage(Mage,19,11,2);
            state.initPersonnage(Archer,19,12,2);
            state.initPersonnage(Guerrier,19,13,2);
            //todo changer ordre position initperso
            sf::RenderWindow window(sf::VideoMode(state.map.layout[0].size() * 16 + 256, state.map.layout.size() * 16 + 32, 32), "map");
            //window.setSize(sf::Vector2u(2624, 1408));
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
            Slayer.initSprite();
            
            ai::RandomAI rai;
            ngine.Start();
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed){
                        state.gameOver = true;
                        ngine.Stop();
                        window.close();
                    }
                }
                Slayer.draw(window);
                sleep(3);
                cout << "--- Selection du personnage ---"<< endl;
                rai.run(state);
                ngine.EndTurn();
            }
        }
        else if (strcmp(argv[1], "heuristicAI") == 0){
            cout << "--- heuristicAI ---" << endl;
            State state{"render"};
            engine::Engine ngine(state);
            state.map.initMap();
            state.initPersonnage(Mage,2,2,1);
            state.initPersonnage(Archer,5,5,1);
            state.initPersonnage(Guerrier,5,6,1);
            state.initPersonnage(Mage,6,5,2);
            state.initPersonnage(Archer,10,2,2);
            //todo changer ordre position initperso
            sf::RenderWindow window(sf::VideoMode(state.map.layout[0].size() * 16 + 256, state.map.layout.size() * 16 + 32, 32), "map");
            //window.setSize(sf::Vector2u(2624, 1408));
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
            Slayer.initSprite();
            
            ai::HeuristicAI hai;
            hai.initMapNode(state);
            ngine.Start();
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed){
                        state.gameOver = true;
                        ngine.Stop();
                        window.close();
                    }
                }
                Slayer.draw(window);
                sleep(3);
                hai.run(ngine,state);
                ngine.EndTurn();
            }
        }
        else if (strcmp(argv[1], "battle") == 0){

            cout << "--- Battle Random AI vs HeuristicAI ---" << endl;
            State state{"render"};
            engine::Engine ngine(state);
            state.map.initMap();

            //team 1
            cout << "Team 1 will be random AI" << endl;
            state.initPersonnage(Mage,1,11,1);
            state.initPersonnage(Archer,1,12,1);
            state.initPersonnage(Guerrier,1,13,1);
            //team 2
            cout << "Team 2 will be HeuristicAI" << endl;
            //state.initPersonnage(Mage,19,11,2);
            state.initPersonnage(Archer,19,12,2);
            //state.initPersonnage(Guerrier,19,13,2);

            //todo changer ordre position initperso
            sf::RenderWindow window(sf::VideoMode(state.map.layout[0].size() * 16 + 256, state.map.layout.size() * 16 + 32, 32), "map");
            //window.setSize(sf::Vector2u(2624, 1408));
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
            Slayer.initSprite();
            
            ai::RandomAI rai;
            ai::HeuristicAI hai;
            hai.initMapNode(state);

            ngine.Start();

            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed){
                        state.gameOver = true;
                        ngine.Stop();
                        window.close();
                    }
                }
                Slayer.draw(window);
                sleep(3);
                if(state.activePlayer->getID_Invocateur()==1){
                    cout << "- Random AI-"<< endl;
                    rai.run(state);
                }
                else{
                    cout << "-Heuristic AI-"<< endl;
                    hai.run(ngine,state);
                }

            

                
                ngine.EndTurn();
                
                
            }

        }
        else if (strcmp(argv[1], "rollback") == 0){
            cout << "--- rollback ---" << endl;
            State state{"render"};
            engine::Engine ngine(state);
            state.map.initMap();
            state.initPersonnage(Mage,2,2,1);
            state.initPersonnage(Archer,5,5,1);
            state.initPersonnage(Guerrier,5,6,1);
            state.initPersonnage(Mage,6,5,2);
            state.initPersonnage(Archer,10,2,2);
            //todo changer ordre position initperso
            sf::RenderWindow window(sf::VideoMode(state.map.layout[0].size() * 16 + 256, state.map.layout.size() * 16 + 32, 32), "map");
            //window.setSize(sf::Vector2u(2624, 1408));
            StateLayer Slayer(state, window);
            Slayer.initLayer(state);
            Slayer.initSprite();
            SaveState rollback(state);
            int timeRoll = 0;
            ai::HeuristicAI hai;
            hai.initMapNode(state);
            ngine.Start();
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed){
                        state.gameOver = true;
                        ngine.Stop();
                        window.close();
                    }
                }
                Slayer.draw(window);
                sleep(3);
                hai.run(ngine,state);
                ngine.EndTurn();
                if(timeRoll == 10){
                    cout << "Rolling BACK !!"<<endl;
                    state = rollback.LoadState();
                }
                else {timeRoll++;}
            }
        }
    }
    return 0;
}

