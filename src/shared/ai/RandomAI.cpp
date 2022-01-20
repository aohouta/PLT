//
//  RandomAI.cpp
//  
//
//  Created by abdel houta on 23/12/2021.
//

#include "../ai.h"
#include "engine.h"
#include "state.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <random>

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;

void RandomAI::run(state::State& state)
{
    int tailleMapX = static_cast<int>(state.map.layout.size());
    int tailleMapY = static_cast<int>(state.map.layout[0].size());


    /*int randomPerso = selectPersonnage(state);
    Personnage &Perso = *state.getPersonnages()[randomPerso];
    state.activePlayer = state.getPersonnages()[randomPerso];
    */
    while(state.activePlayer == nullptr){;}
    shared_ptr<Personnage> Perso = state.activePlayer;
    cout << "Le personnage selectionné est ... " << Perso->getNom() <<" !\n" << endl;
    
    //int randomCommand = rand()%2;
    int randomCommand = 0;
    
    if (randomCommand == 0){ //move
        ID_Action Action = MOVING;
        Perso->setAction(Action) ;
        ID_Orientation Orientation = Perso->getOrientation();
        int posX = Perso->getPosition().getX();
        int posY = Perso->getPosition().getY();

        
        

        //prot 1
        int randX, randY, mob,occupation,newX,newY, range;
        random_device rd; // obtain a random number from hardware
        mt19937 gen(rd()); // seed the generator
        mob = Perso->getMOB();
        uniform_int_distribution<> distr(-mob, mob); // define the range
        do{
            do{
                randX = distr(gen);
                randY = distr(gen);
                occupation = 0;
                newX = randX + posX;
                newY = randY + posY;

                //check if in map
                if (newX >= tailleMapX ){
                    newX = state.map.layout.size() -1;
                }
                else if (newX < 0){
                    newX = 0;
                }

                if (newY >= tailleMapY){
                    newY = state.map.layout.size() -1;
                }
                else if (newY < 0){
                    newY = 0;
                }

                range = abs(newX-posX)+abs(newY-posY);

            }while(range > Perso->getMOB());
            


            Position newPos(newX,newY);
            for(auto& personn : state.getPersonnages()){
                if(personn->getPosition().Compare(newPos)){
                    occupation = 1;
                }
            }
            

        } while ( occupation == 1 ); //need check if the position is empty or not 

        /*
        
        int randX = rand()%state.map.layout.size();
        int randY = rand()%state.map.layout[0].size();
        

        */
        cout << Perso->getNom() << " bouge de -> ("<< posX << "," << posY <<")...\n"<< endl;
        cout << "soit un déplacement de " << abs(newX-posX)+abs(newY-posY) <<endl;
        cout << Perso->getNom() << " s'apprête à avancer à la position -> ("<< newX << "," << newY <<")...\n"<< endl;
        MoveCommand move(*state.map.layout[newX][newY]);
        move.Execute(state);
        cout << "Fin de l'action.\n" << endl;
    }
    
    if (randomCommand == 1){ //atk
        ID_Action Action = ATTACKING;
        Perso->setAction(Action);
        int randX = rand()%state.map.layout.size();
        int randY = rand()%state.map.layout[0].size();
        
        cout << Perso->getNom() << " s'apprête à attaquer la case à la position -> (" << randX << "," << randY <<")...\n"<< endl;
        AttackCommand atck(*state.map.layout[randX][randY]);
        atck.Execute(state);
        cout << "Fin d'action.\n"<< endl;
    }
    
    //engine.Update();
}

/*int RandomAI::selectPersonnage (state::State& state){
    std::vector<int> Index;
    for(unsigned int i = 0; i < state.getPersonnages().size(); i++){
        Personnage &perso = *state.getPersonnages()[i];
        if(perso.getEtatPerso() != Mort  )
            Index.push_back(i);
    }
    int randomNumber = rand() % Index.size();
    return Index[randomNumber];
}*/
