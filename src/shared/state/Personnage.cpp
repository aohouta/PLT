#include "Personnage.h"
#include <iostream>

using namespace std;
namespace state {

Personnage::Personnage(std::string Nom, ID_PType PType, int ID_Invocateur){
    this->Nom = Nom;
    this->PType = PType;
    this->ID_Invocateur = ID_Invocateur;

    if(PType == Guerrier){
        PV = 90;
        PVmax = 90;
        ManaMax = 50;
        ATK = 30;
        MAG = 30;
        RM = 50;
        DEF = 90;
        VIT = 90;
        MOB = 3;
        MOBrestante = 3;
        ESQ = 30;
        
    }
    else if(PType == Mage){
        PV = 50;
        PVmax = 50;
        ManaMax = 100;
        ATK = 30;
        MAG = 90;
        RM = 90;
        DEF = 30;
        VIT = 50;
        MOB = 5;
        MOBrestante = 5;
        ESQ = 50;
    }
    else if(PType == Archer){
        PV = 30;
        PVmax = 30;
        ManaMax = 70;
        ATK = 90;
        MAG = 50;
        RM = 30;
        DEF = 50;
        VIT = 30;
        MOB = 9;
        MOBrestante = 9;
        ESQ = 90;

    }    
}

vector<int> Personnage::getStats(){
    return {PV,PVmax ,Mana, ManaMax, ATK, MAG, RM, DEF, VIT, MOB, ESQ};
}

ID_Orientation Personnage::getOrientation(){
    return Orientation;
}

vector<Effet> Personnage::getEffets(){
    return ListeEffet;
}

const Position& Personnage::getPosition() const {
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

ID_Action Personnage::getAction() const{
    return Action;
}

void Personnage::setAction(ID_Action Action){
    this->Action = Action;
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

void Personnage::setPV(int pV){
    int pvMax = this->getPVmax();
    if (pV <= 0){ //Healt can't go lower than 0
        PV = 0;
    }
    else if (pV < pvMax ){ //Healt can't go higher than PVmax
        PV = pV;
    }
    else{
        PV = PVmax;
    }
}

int Personnage::getPVmax() const{
   return PVmax; 
}

void Personnage::setPVmax(int pVmax){
    if (pVmax <= 1){ //Max Healt can't go lower than 1
        PVmax = 1;
        PV = 1;
    }
    else{
        PVmax = pVmax;
        if(pVmax < this->getPV()){
            PV = pVmax;
        }
    }
}

int Personnage::getMana() const{
    return Mana;
}

void Personnage::setMana(int mana){
    if (mana <= 0){ // Current Mana can't go lower than 0
        Mana = 0; 
    }
    else if (mana < this->getManaMax()){
        Mana = mana;
    }
    else{ // Current Mana can't exceed Max Mana
        Mana = this->getManaMax();
    }
}

int Personnage::getManaMax() const{
    return ManaMax;
}

void Personnage::setManaMax(int manaMax){
    if (manaMax <= 1){ // Max Mana can't go lower than 1
        ManaMax = 1;
        Mana = 1;
    }
    else{
        ManaMax = manaMax;
        if(ManaMax < this->getMana()){
            Mana = ManaMax;
        }
    }
}


int Personnage::getATK() const{
    return ATK;
}

// no stats can go lower than 0 !

void Personnage::setATK(int aTK){
    if(aTK<0){
        ATK = 0;
    }
    else {
        ATK = aTK;
    }
}

int Personnage::getMAG() const{
    return MAG;
}

void Personnage::setMAG(int mAG){
    if(mAG<0){
        MAG = 0;
    }
    else {
        MAG = mAG;
    }
}

int Personnage::getRM() const{
    return RM;
}
void Personnage::setRM(int rM){
    if(rM<0){
        RM = 0;
    }
    else {
       RM = rM;
    }
}

int Personnage::getDEF() const{
    return DEF;
}

void Personnage::setDEF(int dEF){
    if(dEF<0){
        DEF = 0;
    }
    else {
       DEF = dEF;
    }
}

int Personnage::getVIT() const{
    return VIT;
}

void Personnage::setVIT(int vIT){
    if(vIT<0){
        VIT = 0;
    }
    else {
        VIT = vIT;
    }
}

int Personnage::getMOB() const{
    return MOB;
}

void Personnage::setMOB(int mOB){
    if(mOB<0){
        MOB = 0;
    }
    else {
        MOB = mOB;
    }
}

int Personnage::getMOBrestante() const{
    return this->MOBrestante;
}

void Personnage::setMOBrestante(int mOBrestante){
    if (mOBrestante < 0){
        MOBrestante = 0;
    }
    else if (mOBrestante > this->getMOB()){
        MOBrestante = this->getMOB();
    }
    else {
        MOBrestante = mOBrestante;
    }
}

int Personnage::getESQ() const{
    return ESQ;
}

void Personnage::setESQ(int eSQ){
    if (eSQ < 0){
        ESQ = 0;
    }
    else if (eSQ > 100){
        ESQ = 100;
    }
    else {
        ESQ = eSQ;
    }
}
const std::vector<Effet>& Personnage::getListeEffet() const{
    return ListeEffet;
}

void Personnage::setListeEffet(const std::vector<Effet>& ListeEffet){
    this->ListeEffet = ListeEffet;
}

const std::vector<Sort>& Personnage::getListeSort() const{
    return ListeSort;
}

void Personnage::setListeSort(const std::vector<Sort>& ListeSort){
    this->ListeSort = ListeSort;
}
int Personnage::getID_Invocateur() const{
    return ID_Invocateur;
}
void Personnage::setID_Invocateur(int ID_Invocateur){
    this->ID_Invocateur=ID_Invocateur;
}

/*Position &Personnage::getPosition(){
    Position &refPosition = position;
    return refPosition;

}*/

Personnage::Personnage(){}

}
