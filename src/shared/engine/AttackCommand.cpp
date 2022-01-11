#include "AttackCommand.h"
#include <stdio.h>
#include <iostream>



using namespace std;



namespace engine{

    

    AttackCommand::AttackCommand(state::Cell& TargetCell){
            this->TargetCell = TargetCell;        
        
    }

    bool AttackCommand::InRange(state::Cell& TargetCell){
        int Range = abs(Caster->getPosition().getX() - TargetCell.getPosition().getX()) + abs(Caster->getPosition().getY() - TargetCell.getPosition().getY());
        if(Caster->getBasicRange()>= Range){
            return true;
        }
        else{ return false; }
    }

    int AttackCommand::Execute(state::State& state){

        //set active player as caster
        auto& Caster = state.activePlayer;

        //Check if caster have enought range
        if(InRange(TargetCell) == false) {
            cout << "Hors de portée \n";
            return 1;
        }

        //Check Target Cell occupation
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
        {
            //Target Cell is a Charater
            cout << "Un adversaire est présent !!"<<endl;
            cout << "Attaque un joueur, PV avant : "<< Defender->getPV() << endl;
            
            //if esquive = réussi cout << "Loupé ahah"
            //else

            int BaseATK = Caster->getTotalAttack();
            int BaseDEF = Caster->getTotalDef();
            float BaseDmg = BaseATK*(1-(BaseDEF/100));

            //sans crit
            float TotalDmg = BaseDmg * ActionCommand::OrientationMult(Caster,Defender);
            


            //avec crit
            //float TotalDmg = BaseDmg * OrientationMult(Attacker,Defender) //* (IsCrit()*(MultCrit-1)+1);

            
            Defender->setPV(Defender->getPV() - static_cast<int>(TotalDmg));

            

            cout << "PV après : " << Defender->getPV() << endl;
            if(Defender->getPV() == 0){
                Defender->setEtatPerso(state::Mort);
                cout << Defender->getNom() << " est mort\n";
            }

        }
            break;
        default:
            cout << "Ceci n'est pas censé apparaitre \n";
            return 1;
            break;
        }
        Caster->setActionLeft(Caster->getActionLeft()-1);
        return 0;
    }
}
