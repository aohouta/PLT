#include "Personnage.h"
#include <iostream>

using namespace std;
namespace state {

Personnage::Personnage(ID_PType PType){
    this->PType = PType;
    Position = {0,0};
    
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

ID_Orientation Personnage::getOrientation(){
    return Orientation;
}

vector<Effets> Personnage::getEffets(){
    return ListeEffet;
}

const std::array<int,2>& Personnage::getPosition() const{
    return Position;
}

void Personnage::setPosition(const std::array<int,2>& Position){
    this->Position = Position;
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
    

}