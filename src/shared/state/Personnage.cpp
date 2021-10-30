#include "Personnage.h"
#include <iostream>

using namespace std;
namespace state {

Personnage::Personnage(ID_PType PType){
    this->PType = PType;
    if(PType == Guerrier){
        PV = 90;
        ATK = 30;
        MAG = 30;
        RM = 50;
        DEF = 90;
        VIT = 90;
        MOB = 3;
        ESQ = 30;
    }
    else if(PType == Mage){
        PV = 50;
        ATK = 30;
        MAG = 90;
        RM = 90;
        DEF = 30;
        VIT = 50;
        MOB = 5;
        ESQ = 50;
    }
    else if(PType == Archer){
        PV = 30;
        ATK = 90;
        MAG = 50;
        RM = 30;
        DEF = 50;
        VIT = 30;
        MOB = 9;
        ESQ = 90;
    }    
}

vector<int> Personnage::getStats(){
    return {PV, ATK, MAG, RM, DEF, VIT, MOB, ESQ};
}

vector<int> Personnage::getPosition(){
    return Position;
}

ID_Orientation Personnage::getOrientation(){
    return Orientation;
}

vector<Effets> Personnage::getEffets(){
    return ListeEffet;
}

void Personnage::setPosition(int x, int y){
    Position[0] = x;
    Position[1] = y;
}

}