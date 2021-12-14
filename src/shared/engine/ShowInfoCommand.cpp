#include "ShowInfoCommand.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace engine{
    ShowInfoCommand::ShowInfoCommand(state::Cell TargetCell){
        this->TargetCell = TargetCell;
    }
    int ShowInfoCommand::Execute(){
        int occupation = TargetCell.getOccupation();
        if(occupation > 0){
            if(occupation == 1){
                //TODO show information on loot, not yet implemented
            }
            else if(occupation == 2) {
                Personnage PersoInfo = TargetCell.getPersonnage();
                //Display information of targeted character
            }
        }
    }

}