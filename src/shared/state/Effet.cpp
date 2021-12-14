#include "Effet.h"
#include <iostream>

using namespace std;
namespace state {

    ID_Type_effet Effet::getEffet() const{
        return Effet;
    }

    void Effet::setEffet(ID_Type_effet Effet){
        this->Effet = Effet;
    }

    int Effet::getEffetDuree() const{
        return EffetDuree;
    }

    void Effet::setEffetDuree(int EffetDuree){
        this->EffetDuree = EffetDuree;
    }

    int Effet::getNiveauEffet() const{
        return NiveauEffet;
    }
    void Effet::setNiveauEffet(int NiveauEffet){
        this->NiveauEffet = NiveauEffet;
    }

}