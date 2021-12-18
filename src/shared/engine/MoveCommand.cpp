#include "MoveCommand.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


namespace engine{
    MoveCommand::MoveCommand(state::Cell& TargetCell){
        this->TargetCell = TargetCell;
    }
    int MoveCommand::Execute(state::State& state){
        Perso = state.activePlayer;
        int occupation = 0;
        for(auto& personn : state.getPersonnages()){
            if(personn->getPosition().Compare(TargetCell.getPosition())){
                occupation = 1;
            }
        }
        if(occupation == 0){
            if(Pathfinding()){
                Perso->setPosition(TargetCell.getPosition());
                cout << "Moved";
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
        auto posCell = TargetCell.getPosition();
        auto posPerso = Perso->getPosition();
        int dist = abs(posCell.getX()-posPerso.getX())+abs(posCell.getY()-posPerso.getY());
        return dist<Perso->getMOB();
    }
}