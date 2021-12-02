#include "Personnage.h"
#include <iostream>

using namespace std;
namespace state {

Personnage::Personnage(ID_PType PType){
    this->PType = PType;
    this->EtatPerso = ID_EtatPerso::Alive;
    this->position = {0,0};
    
    if(PType == Guerrier){
        this->PV = 90;
        this->ATK = 30;
        this->MAG = 30;
        this->RM = 50;
        this->DEF = 90;
        this->VIT = 90;
        this->MOB = 3;
        this->ESQ = 30;
    }
    else if(PType == Mage){
        this->PV = 50;
        this->ATK = 30;
        this-> MAG = 90;
        this-> RM = 90;
        this-> DEF = 30;
        this-> VIT = 50;
        this-> MOB = 5;
        this->ESQ = 50;
    }
    else if(PType == Archer){
        this-> PV = 30;
        this->ATK = 90;
        this->MAG = 50;
        this-> RM = 30;
        this-> DEF = 50;
        this-> VIT = 30;
        this-> MOB = 9;
        this-> ESQ = 90;
    }    
}

vector<int> Personnage::getStats(){
    return {PV, ATK, MAG, RM, DEF, VIT, MOB, ESQ};
}

ID_Orientation Personnage::getOrientation(){
    return Orientation;
}

vector<Effets> Personnage::getEffets(){
    return ListeEffet;
}

Position& Personnage::getPosition (){
    return position;
}

void Personnage::setPosition(const Position& position){
    this->position = position;
}

ID_PType Personnage::getPType() const{
    return PType;
}

void Personnage::setPType(ID_PType PType){
    this->PType = PType;
}

ID_EtatPerso Personnage::getEtatPerso() const{
    return EtatPerso;
}

void Personnage::setEtatPerso(ID_EtatPerso EtatPerso){
    this->EtatPerso = EtatPerso;
}

void Personnage::setOrientation(ID_Orientation Orientation){
    this->Orientation = Orientation;
}

const std::string& Personnage::getNom() const{
    return Nom;
}

void Personnage::setNom(const std::string& Nom){
    this->Nom = Nom;
}

int Personnage::getNbTours() const{
    return NbTours;
}

void Personnage::setNbTours(int NbTours){
    this->NbTours = NbTours;
}

int Personnage::getPV() const{
    return PV;
}

void Personnage::setPV(int PV){
    this->PV = PV;
}

int Personnage::getATK() const{
    return ATK;
}

void Personnage::setATK(int ATK){
    this->ATK = ATK;
}

int Personnage::getMAG() const{
    return MAG;
}

void Personnage::setMAG(int MAG){
    this->MAG = MAG;
}

int Personnage::getRM() const{
    return RM;
}
void Personnage::setRM(int RM){
    this->RM = RM;
}

int Personnage::getDEF() const{
    return DEF;
}

void Personnage::setDEF(int DEF){
    this->DEF = DEF;
}

int Personnage::getVIT() const{
    return VIT;
}

void Personnage::setVIT(int VIT){
    this->VIT = VIT;
}

int Personnage::getMOB() const{
    return MOB;
}

void Personnage::setMOB(int MOB){
    this->MOB = MOB;
}

int Personnage::getESQ() const{
    return ESQ;
}

void Personnage::setESQ(int ESQ){
    this->ESQ = ESQ;
}
const std::vector<Effets>& Personnage::getListeEffet() const{
    return ListeEffet;
}

void Personnage::setListeEffet(const std::vector<Effets>& ListeEffet){
    this->ListeEffet = ListeEffet;
}

const std::vector<Sorts>& Personnage::getListeSort() const{
    return ListeSort;
}

void Personnage::setListeSort(const std::vector<Sorts>& ListeSort){
    this->ListeSort = ListeSort;
}
/*Position &Personnage::getPosition(){
    Position &refPosition = position;
    return refPosition;
}*/

}
