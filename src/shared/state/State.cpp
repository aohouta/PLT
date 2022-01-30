#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>

#include <stdio.h>
#include "../../json.hpp"

using namespace std;
using json = nlohmann::json;

namespace state{


State::State (std::string mode){
    mode = mode;
    std::cout << "Creating a state object in >>>" + mode + "<<< mode\n";
    //std::vector<std::unique_ptr<Personnage>> Personnages;
   
}

State::State(){}


const std::vector<std::shared_ptr<Personnage>>&State::getPersonnages() const{

    return Personnages;
    
}

void State::initPersonnage (ID_PType PType,int x, int y,int ID_Invocateur){
    
    if (PType == Guerrier){
        std::shared_ptr<Personnage> ptrC1(new Personnage("Ultimate Warrior of DOOM APOCALYPSE",PType,ID_Invocateur));
        ptrC1->setPosition({x,y});
        ptrC1->setOrientation(Face);
        Personnages.push_back(move(ptrC1));
        
    }
    if (PType == Mage){
        std::shared_ptr<Personnage> ptrC1(new Personnage("Dark mage of the Lost Forest",PType,ID_Invocateur));
        ptrC1->setPosition({x,y});
        ptrC1->setOrientation(Face);
        Personnages.push_back(move(ptrC1));
        
    }
    if (PType == Archer){
        std::shared_ptr<Personnage> ptrC1(new Personnage("Wild Archer of the Old Mountain",PType,ID_Invocateur));
        ptrC1->setPosition({x,y});
        ptrC1->setOrientation(Face);
        Personnages.push_back(move(ptrC1));
        
    }
    

    
    
    return;
    //for (size_t i = 0; i < Personnages.size(); i++) Personnages[i]->setIndex(i);

    /*sf::Texture texturemage;
    
    if (!texture.loadFromFile("res/mage.png")){
            std::cout << "\nOOPSIE DOOPSIE\n";
        }
    
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(00, 00, 17, 32));
    sprite.setPosition(10,22);
    cout << "characters inits finished\n";
    return sprite;*/
    
}

void State::DeletePerso(int posInList){
    Personnages.erase(Personnages.begin() + posInList);
}

void State::SaveInitSate (){
    //remove("CommandSave.json");
    remove("replay.txt");
    std::ofstream out;
    //out.open("CommandSave.json", std::ios::app);
    out.open("replay.txt", std::ios::app);
    json header;
    vector<json> listePerso;
    for(auto& perso : Personnages){     
        json j ={
            {"Name", perso->getNom()},
            {"Team", perso->getID_Invocateur()},
            {"x", perso->getPosition().getX()},
            {"y",perso->getPosition().getY()}
        };
        listePerso.push_back(j);
        
        //out << std::setw(4) << j << std::endl;
    }
    header["PersonnagesList"] = listePerso;
    out << std::setw(4) << header << std::endl;
} 

}
