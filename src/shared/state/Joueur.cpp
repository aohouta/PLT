#include "Joueur.h"
#include <iostream>
namespace state {


Joueur::Joueur (std::string NomJoueur, ID_PlayerType PlayerType){
    this->PlayerType = PlayerType;
    this->NomJoueur = NomJoueur;
}

Joueur::Joueur (){}

ID_PlayerType Joueur::getPlayerType() const{
    return PlayerType;
    
}

void Joueur::setPlayerType(ID_PlayerType PlayerType){
    PlayerType = PlayerType;
    
}

ID_GameStatus Joueur::getGameStatus() const{
    return GameStatus;
    

}

void Joueur::setGameStatus(ID_GameStatus GameStatus){
    GameStatus = GameStatus;
    
}

}


