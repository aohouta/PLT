#include "ShowInfoCommand.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace engine{
    ShowInfoCommand::ShowInfoCommand(state::Cell& TargetCell){
        this->TargetCell = TargetCell;
    }
    int ShowInfoCommand::Execute(state::State& state){
        state::Personnage selected;
        int occupation = 0;
        for(auto& perso : state.getPersonnages()){
            if(perso->getPosition().Compare(TargetCell.getPosition())){
                selected = *perso;
                occupation = 2;
            }
        }
        if(occupation > 0){
            if(occupation == 1){
                //TODO show information on loot, not yet implemented
            }
            else if(occupation == 2) {
                //Display information of targeted character
            }
        }
        return 1;
    }

}