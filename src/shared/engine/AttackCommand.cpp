#include "AttackCommand.h"
#include <stdio.h>
#include <iostream>

using namespace std;

namespace engine{
    AttackCommand::AttackCommand(state::Cell TargetCell){
        this->TargetCell = TargetCell;
    }
    int AttackCommand::Execute(state::Etat& state){
        Attacker = state.getActivePlayer();
        int CellOccupation = TargetCell.isOccupied();
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
            state::Personnage Defender;
            Defender = TargetCell.getPersonnage();
            Defender.setPV(Attacker.getATK()-Attacker.getATK()*Defender.getDEF());
            break;
        default:
            cout << "Ceci n'est pas censé apparaitre \n";
            break;
        }
    }
}