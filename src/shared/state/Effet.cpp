#include "../state.h"
#include <iostream>

using namespace std;
namespace state {

    Effet::Effet(){}

    Effet::Effet (ID_Type_effet type_effet, int EffetDuree, int NiveauEffet){
        this->Type_Effet = type_effet;

        if(NiveauEffet < 0){
            this->NiveauEffet = 0;
        }
        else{
            this->NiveauEffet = NiveauEffet;
        }
        
        if(EffetDuree < 1){
            this->EffetDuree = 1;
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

        if(EffetDuree < 1){
            this->EffetDuree = 1;
        }
        else{
            this->EffetDuree = EffetDuree;
        }
        
    }

    int Effet::getNiveauEffet() const{
        return NiveauEffet;
    }

    void Effet::setNiveauEffet(int NiveauEffet){
        if(NiveauEffet < 0){
            this->NiveauEffet = 0;
        }
        else{
            this->NiveauEffet = NiveauEffet;
        }
    }

}