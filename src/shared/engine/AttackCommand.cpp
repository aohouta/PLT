#include "AttackCommand.h"
#include <stdio.h>

using namespace std;

namespace Engine{
    AttackCommand::AttackCommand(state::Cell TargetCell){
        This->TargetCell = TargetCell;
        Attacker = getActivePlayer();
    }
    AttackCommand::Execute(state::State& state){
        int CellOccupation = TargetCell.isOccupied
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