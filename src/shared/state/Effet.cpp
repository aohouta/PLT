#include "../state.h"
#include <iostream>

using namespace std;
namespace state {

    int lowestEffectLevel = 0;
    int lowestEffectDuration = 1;

    /*Effet::Effet(){}

    Effet::Effet (ID_Type_effet type_effet, int EffetDuree, int NiveauEffet){
        this->Type_Effet = type_effet;

        if(NiveauEffet < lowestEffectLevel){
            this->NiveauEffet = lowestEffectLevel;
        }
        else{
            this->NiveauEffet = NiveauEffet;
        }

        if(EffetDuree < lowestEffectDuration){
            this->EffetDuree = lowestEffectDuration;
        }
        else{
            this->EffetDuree = EffetDuree;
        }

    }

    ID_Type_effet Effet::getType_Effet() const{
        return Type_Effet;
    }

    void Effet::setType_Effet(ID_Type_effet Type_Effet){
        this->Type_Effet = Type_Effet;
    }

    int Effet::getEffetDuree() const{
        return EffetDuree;
    }

    void Effet::setEffetDuree(int EffetDuree){

        if(EffetDuree < lowestEffectDuration){
            this->EffetDuree = lowestEffectDuration;
        }
        else{
            this->EffetDuree = EffetDuree;
        }
        
    }

    int Effet::getNiveauEffet() const{
        return NiveauEffet;
    }

    void Effet::setNiveauEffet(int NiveauEffet){
        if(NiveauEffet < lowestEffectLevel){
            this->NiveauEffet = lowestEffectLevel;
        }
        else{
            this->NiveauEffet = NiveauEffet;
        }
    }*/

}