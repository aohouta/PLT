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

void RandomAI::run(engine::Engine &engine,state::State& state)
{
    int randomPerso = selectPersonnage(state);
    Personnage &Perso = *state.getPersonnages()[randomPerso];
    state.activePlayer = state.getPersonnages()[randomPerso];
    
    int randomCommand = rand()%2;
    
    if (randomCommand == 0){ //move
        ID_Action Action = MOVING;
        Perso.setAction(Action) ;
        ID_Orientation Orientation = Perso.getOrientation();
        
        MoveCommand move(*state.map.layout[rand()%32][rand()%32]);
        int res = move.Execute(state);
        cout << res << endl;
    }
    
    if (randomCommand == 1){ //atk
        ID_Action Action = ATTACKING;
        Perso.setAction(Action);
        
        AttackCommand atck(*state.map.layout[rand()%32][rand()%32]);
        int res = atck.Execute(state);
        cout << res << endl;
    }
    
    engine.Update();
}

int RandomAI::selectPersonnage (state::State& state){
    std::vector<int> Index;

    for(unsigned int i = 0; i < state.getPersonnages().size(); i++){
        Personnage &perso = *state.getPersonnages()[i];
        if(perso.getEtatPerso() == Mort  )
            Index.push_back(i);
    }

    int randomNumber = rand() % Index.size();
    cout << "[";
    for(auto &index : Index){
        cout << index << ", ";
    }
    cout << "]" << endl;
    return Index[randomNumber];
}
