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
        string CommandName ("Moved");
        Command::save(CommandName,TargetCell, state);
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
                cout << "Moved to X:"<< Perso->getPosition().getX() << " Y: " << Perso->getPosition().getY() << endl ;
                return 1;
            }
            else {
                cout << "Can't move because too far\n";
            }
        }
        else {
            cout << "You can't do that someone is already here\n";
        }

        return 0;
    }
    bool MoveCommand::Pathfinding(){
        auto posCell = TargetCell.getPosition();
        auto posPerso = Perso->getPosition();
        int dist = abs(posCell.getX()-posPerso.getX())+abs(posCell.getY()-posPerso.getY());
        if(dist <= Perso->getMOB() ){return true;}
        else{return false;}
    }
}
