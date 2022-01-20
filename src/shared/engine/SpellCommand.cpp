#include "SpellCommand.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;



namespace engine{

    void SpellCommand::AddEffect(state::Effet effet,shared_ptr<state::Personnage> target){

    vector<state::Effet> newListeEffet = target->getListeEffet();
    newListeEffet.push_back(effet);
    target->setListeEffet( newListeEffet );

    }   

    void SpellCommand::AddMultipleEffect(std::vector<state::Effet> listeEffet,shared_ptr<state::Personnage> target){

    for(size_t i = 0;i<listeEffet.size(); i++){
        AddEffect(listeEffet[i], target);
    }
    }

    SpellCommand::SpellCommand(state::Cell& TargetCell){
        this->TargetCell = TargetCell;
    }

    bool SpellCommand::InRangeSpell(state::Cell& TargetCell,state::Sort& spell){
        int Range = abs(Caster->getPosition().getX() - TargetCell.getPosition().getX()) + abs(Caster->getPosition().getY() - TargetCell.getPosition().getY());
        if(spell.getRange()>= Range){
            return true;
        }
        else{ return false; }
    }

    int SpellCommand::Execute(state::State& state, state::Sort& spell){

        //set active player as caster
        auto& Caster = state.activePlayer;

        //check if caster have enought mana
        if(Caster->getMana() < spell.getCout()){
            cout << "OOPS ! pas assé de mana \n";
            return 1;
        }

        //Check if caster have enought range
        if(InRangeSpell(TargetCell, spell) == false) {
            cout << "Hors de portée \n";
            return 1;
        }



        //Check Target Cell occupation in spell zone
        for(size_t i = 0; i < spell.getZone().size(); i++){

        
            shared_ptr<state::Personnage> Target;
            int CellOccupation = 0;
            state::Position TargetPos(TargetCell.getPosition().getX()+spell.getZone()[i].getX(),TargetCell.getPosition().getY()+spell.getZone()[i].getY());

            

            for(auto& perso : state.getPersonnages()){
    
                if(perso->getPosition().Compare(TargetPos)){
                    Target = perso;
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
                cout << "Attaque un joueur, PV avant : "<< Target->getPV() << endl;
                
                //if esquive = réussi cout << "Loupé ahah"
                //else

                //Basic Spell function, can be customize later

                int BaseATK = Caster->getTotalAttack();
                int BaseMAG = Caster->getTotalMag(); 
                int BaseDEF = Target->getTotalDef();
                int BaseRM = Target->getTotalRM(); 


                float BasePhyDmg = spell.getDmgPhysique()*BaseATK*(1-(BaseDEF/100));
                float BaseMagDmg = spell.getDmgMagique()*BaseMAG*(1-(BaseRM/100));

                //sans crit

                float TotalDmg = BaseMagDmg + BasePhyDmg;


                


                //avec crit
                //float TotalDmg = BaseDmg * OrientationMult(Attacker,Target) //* (IsCrit()*(MultCrit-1)+1);

                //Set Target Effect



                //Set Target new HP
                Target->setPV(Target->getPV() - static_cast<int>(TotalDmg) + spell.getQtSoin() );

                AddMultipleEffect(spell.getEffetSort(), Target);

                cout << "PV après : " << Target->getPV() << endl;
                if(Target->getPV() == 0){
                    Target->setEtatPerso(state::Mort);
                    cout << Target->getNom() << " est mort\n";
                }

            }
                break;
            default:
                cout << "Ceci n'est pas censé apparaitre \n";
                return 1;
                break;
            }
        }    
        Caster->setActionLeft(Caster->getActionLeft()-1);
        Caster->setMana(Caster->getMana() - spell.getCout());
        return 0;
    }
}