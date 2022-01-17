#include "Joueur.h"
#include <iostream>
namespace state {


Joueur::Joueur (std::string NomJoueur, ID_PlayerType PlayerType, int ID){
    this->PlayerType = PlayerType;
    this->NomJoueur = NomJoueur;
    this->ID = ID;
}

Joueur::Joueur (){}

ID_PlayerType Joueur::getPlayerType() const{
    return PlayerType;
    
}

void Joueur::setPlayerType(ID_PlayerType PlayerType){
    this->PlayerType = PlayerType;
    
}

ID_GameStatus Joueur::getGameStatus() const{
    return GameStatus;
    

}

void Joueur::setGameStatus(ID_GameStatus GameStatus){
    this->GameStatus = GameStatus;
    
}

const std::vector<Personnage>& Joueur::getPersonnages() const{
    return  Personnages;
}

void Joueur::setPersonnages(const std::vector<Personnage>& Personnages){
    this->Personnages = Personnages;
}

const std::string& Joueur::getNomJoueur() const{
    return NomJoueur;
}

void Joueur::setNomJoueur(const std::string& NouveauNom){
    this->NomJoueur = NouveauNom;
}

int Joueur::getID() const{
    return ID;
}
void Joueur::setID(int ID){
    this-> ID= ID;
}

}


