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



void RandomAI::run(state::State& state){

    while(state.activePlayer == nullptr){;}

    //set active player to be driven by RandomAI
    shared_ptr<Personnage> Perso = state.activePlayer;
    cout << "Le personnage selectionné est ... " << Perso->getNom() <<" de l'équipe " << Perso->getID_Invocateur() <<" !\n" << endl;

    int random;
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator        
    uniform_int_distribution<> distr(0,4); // define the range
    random = distr(gen);
    switch (random)
    {
        case 0: //do nothing
            cout << "Le personnage ne fait rien, quel flemmard !\n" << endl;
            break;
        case 1: //just attacking
            randomAtk(state);
            break;
        case 2: //just moving
            randomMov(state);
            break;
         case 3: //att + mov
            randomAtk(state);
            randomMov(state);
            break;
         case 4: //mov + att
            randomMov(state);
            randomAtk(state);
            break;
        default :
            cout << "Ceci n'est pas censé apparaite !\n" << endl;

    }
}

void RandomAI::randomAtk(state::State& state) {

    //get map size
    int tailleMapX = static_cast<int>(state.map.layout.size());
    int tailleMapY = static_cast<int>(state.map.layout[0].size());


    //set active player to be driven by RandomAI
    shared_ptr<Personnage> Perso = state.activePlayer;
    
    //get pos of active player
    int posX = Perso->getPosition().getX();
    int posY = Perso->getPosition().getY();
    
    
        //set action as acttacking
        ID_Action Action = ATTACKING;
        Perso->setAction(Action);
        //preparing random
        int randX, randY, atkRange,targetX,targetY, range;
        int offLimit = 0;
        atkRange = Perso->getBasicRange();
        random_device rd; // obtain a random number from hardware
        mt19937 gen(rd()); // seed the generator        
        uniform_int_distribution<> distr(-atkRange, atkRange); // define the range
        
            do{
                offLimit = 0;
                randX = distr(gen);
                randY = distr(gen);

                targetX = randX + posX;
                targetY = randY + posY;

                //check if in map
                if (targetX >= tailleMapX || targetX < 0 ){
                    offLimit = 1;
                }
                if (targetY >= tailleMapY || targetY < 0){
                    offLimit = 1;
                }
                if (randX + randY ==0){ //SUICIDE isn't allowed!
                    offLimit = 1;
                }

                range = abs(targetX-posX)+abs(targetY-posY);
                cout << "tente d'attaquer à " << range << endl;

            }while(range > atkRange || offLimit == 1);
            


        Position targetCell(targetX,targetY);       
        cout << Perso->getNom() << " s'apprête à attaquer la case à la position -> (" << targetX << "," << targetY <<") depuis sa position ("<< posX << "," << posY <<")...\n"<< endl;
        AttackCommand atck(*state.map.layout[targetX][targetY]);
        atck.Execute(state);
        cout << "Fin d'action.\n"<< endl;
        //set action IDLE
        Perso->setAction(IDLE) ;
    

}

void RandomAI::randomMov(state::State& state) {

    //get map size
    int tailleMapX = static_cast<int>(state.map.layout.size());
    int tailleMapY = static_cast<int>(state.map.layout[0].size());




    //set active player to be driven by RandomAI
    shared_ptr<Personnage> Perso = state.activePlayer;
    
    
    //get pos of active player
    int posX = Perso->getPosition().getX();
    int posY = Perso->getPosition().getY();

        //set action moving
        ID_Action Action = MOVING;
        Perso->setAction(Action) ;    
        //preparing random
        int randX, randY, mob,occupation,newX,newY, range;
        mob = Perso->getMOB();
        random_device rd; // obtain a random number from hardware
        mt19937 gen(rd()); // seed the generator
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

            }while(range > mob);
            


            Position newPos(newX,newY);
            //check if the cell is free
            for(auto& personn : state.getPersonnages()){
                if(personn->getPosition().Compare(newPos)){
                    occupation = 1;
                }
            }
            

        } while ( occupation == 1 ); //need check if the position is empty or not 


        cout << Perso->getNom() << " bouge de -> ("<< posX << "," << posY <<")...\n"<< endl;
        cout << "soit un déplacement de " << abs(newX-posX)+abs(newY-posY) <<endl;
        cout << Perso->getNom() << " s'apprête à avancer à la position -> ("<< newX << "," << newY <<")...\n"<< endl;
        MoveCommand move(*state.map.layout[newX][newY]);
        move.Execute(state);
        cout << "Fin de l'action.\n" << endl;
        //set action IDLE
        Perso->setAction(IDLE) ;
    
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
