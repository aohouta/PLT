#include "SpellCommand.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

namespace engine{
    SpellCommand::SpellCommand(state::Cell TargetCell){
        this->TargetCell = TargetCell;
        Attacker = getActivePlayer();
    }
    int AttackCommand::Execute(state::Etat& state){
        int CellOccupation = TargetCell.isOccupied();
        switch (CellOccupation)
        {
        case 0:
            cout << "Attaque le vide\n";
            break;
        case 1:
            cout << "Attaque un obstacle\n";
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