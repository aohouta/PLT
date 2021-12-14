#include "MoveCommand.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


namespace engine{
    MoveCommand::MoveCommand(state::Cell TargetCell){
        this->TargetCell = TargetCell;
        perso = state::Etat::getActivePlayer();
    }
    int MoveCommand::Execute(state::Etat& state){
        int occupation = TargetCell.isOccupied();
        if(occupation = 0){
            if(pathfinding()){
                perso.setPosition(TargetCell.getPosition());
                return 1;
            }
            else {
                cout << "Too far\n";
            }
        }
        else {
            cout << "You can't do that\n";
        }
        return 0;
    }
    bool MoveCommand::Pathfinding(){
        int posCell[] = TargetCell.getPosition();
        int posPerso[] = Perso.getPosition();
        int dist = abs(posCell[0]-posPerso[0])+abs(posCell[1]-posPerso[1]);
        return dist>Perso.getMOB();
    }
}