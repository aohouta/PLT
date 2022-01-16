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

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;

void RandomAI::run(state::State& state)
{
    /*int randomPerso = selectPersonnage(state);
    Personnage &Perso = *state.getPersonnages()[randomPerso];
    state.activePlayer = state.getPersonnages()[randomPerso];
    */
    while(state.activePlayer == nullptr){;}
    shared_ptr<Personnage> Perso = state.activePlayer;
    cout << "Le personnage selectionné est ... " << Perso->getNom() <<" !\n" << endl;
    
    int randomCommand = rand()%2;
    
    if (randomCommand == 0){ //move
        ID_Action Action = MOVING;
        Perso->setAction(Action) ;
        ID_Orientation Orientation = Perso->getOrientation();
        
        int randX = rand()%state.map.layout.size();
        int randY = rand()%state.map.layout[0].size();
        
        cout << Perso->getNom() << " s'apprête à avancer à la position -> ("<< randX << "," << randY <<")...\n"<< endl;
        MoveCommand move(*state.map.layout[randX][randY]);
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
