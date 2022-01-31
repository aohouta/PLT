#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>
#include <string.h>
#include "engine.h"

#include <stdio.h>
#include "../../json.hpp"

using namespace std;
using json = nlohmann::json;
using namespace engine;

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
    vector<json> listeCommand;
    for(auto& perso : Personnages){     
        json j ={
            {"Name", perso->getNom()},
            {"Type", perso->getPType()},
            {"Team", perso->getID_Invocateur()},
            {"x", perso->getPosition().getX()},
            {"y",perso->getPosition().getY()}
        };
        listePerso.push_back(j);
        
        //out << std::setw(4) << j << std::endl;
    }
    header["PersonnagesList"] = listePerso;
    header["CommandList"] = listeCommand;
    out << std::setw(4) << header << std::endl;
} 

void State::initFromReplay(const std::string replay){
    //init Personnage on map from replay.txt
    json r = json::parse(replay);
    for(size_t i = 0; i < r["PersonnagesList"].size(); i++){
        initPersonnage(r["PersonnagesList"][i]["Type"],r["PersonnagesList"][i]["x"],r["PersonnagesList"][i]["y"],r["PersonnagesList"][i]["Team"]);
    }

}
void State::Replay(const std::string& replay, int& i){
    //Replay turn of current active player
    cout << "Le personnage sélectionné est ... " << activePlayer->getNom() <<" de l'équipe "<< activePlayer->getID_Invocateur()<<" !" << endl;

    json r = json::parse(replay);
    string command = r["CommandList"][i]["Command"].get<std::string>();
    int x,y;
    x = r["CommandList"][i]["x"];
    y = r["CommandList"][i]["y"];
    cout << command << endl;

    if(command.compare("Moved") == 0){
        
        MoveCommand move(*map.layout[x][y]);
        move.Execute(*this);
        if (r["CommandList"][i+1]["Type"] == r["CommandList"][i]["Type"]  && r["CommandList"][i+1]["Team"] == r["CommandList"][i]["Team"]  ) {
            i=i+1;
            x = r["CommandList"][i]["x"];
            y = r["CommandList"][i]["y"];
            AttackCommand atck(*map.layout[x][y]);
            atck.Execute(*this);

        }
    }
    else if(command.compare("Attack") == 0){
        
        AttackCommand atck(*map.layout[x][y]);
        atck.Execute(*this);
        if (r["CommandList"][i+1]["Type"] == r["CommandList"][i]["Type"]  && r["CommandList"][i+1]["Team"] == r["CommandList"][i]["Team"]  ) {
            i=i+1;
            x = r["CommandList"][i]["x"];
            y = r["CommandList"][i]["y"];
            MoveCommand move(*map.layout[x][y]);
            move.Execute(*this);
        }
    }
    else if(command.compare("Do nothing") == 0){
        cout << "Le personnage ne fait rien ! flemmard va" << endl;
    }


}

}
