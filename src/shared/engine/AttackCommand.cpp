#include "AttackCommand.h"
#include <stdio.h>
#include <iostream>

using namespace std;

namespace engine{
    AttackCommand::AttackCommand(state::Cell& TargetCell){
        this->TargetCell = TargetCell;
    }
    int AttackCommand::Execute(state::State& state){
        auto& Attacker = state.activePlayer;
        shared_ptr<state::Personnage> Defender;
        int CellOccupation = 0;
        for(auto& perso : state.getPersonnages()){
            if(perso->getPosition().Compare(TargetCell.getPosition())){
                Defender = perso;
                CellOccupation = 2;
            }
        }
        switch (CellOccupation)
        {
        case 0:
            cout << "Brasse de l'air\n";
            break;
        case 1:
            cout << "Tape un mur\n";
            break;
        case 2:
            cout << "Attaque un joueur, PV avant : "<< Defender->getPV() << endl;
            Defender->setPV(Defender->getPV()-Attacker->getATK()-Attacker->getATK()*Defender->getDEF());
            cout << "PV après : " << Defender->getPV() << endl;
            if(Defender->getPV() == 0){
                Defender->setEtatPerso(state::Mort);
                cout << Defender->getNom() << " est mort\n";
            }
            break;
        default:
            cout << "Ceci n'est pas censé apparaitre \n";
            return 1;
            break;
        }
        return 0;
    }
}
