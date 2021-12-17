#include "AttackCommand.h"
#include <stdio.h>
#include <iostream>

using namespace std;

namespace engine{
    AttackCommand::AttackCommand(state::Cell& TargetCell){
        this->TargetCell = TargetCell;
    }
    int AttackCommand::Execute(state::State& state){
        Attacker = state.activePlayer;
        state::Personnage Defender;
        for(auto& perso : state.getPersonnages()){
            if(perso->getPosition().Compare(TargetCell.getPosition())){
                Defender = *perso;
            }
        }
        int CellOccupation = 0;
        switch (CellOccupation)
        {
        case 0:
            cout << "Brasse de l'air\n";
            break;
        case 1:
            cout << "Tape un mur\n";
            break;
        case 2:
            cout << "Attaque un joueur\n";
            Defender.setPV(Attacker.getATK()-Attacker.getATK()*Defender.getDEF());
            break;
        default:
            cout << "Ceci n'est pas censé apparaitre \n";
            return 1;
            break;
        }
        return 0;
    }
}