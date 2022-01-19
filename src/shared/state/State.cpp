#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>

using namespace std;
namespace state{


State::State (std::string mode){
    mode = mode;
    std::cout << "Creating a state object in >>>" + mode + "<<< mode\n";
    //std::vector<std::unique_ptr<Personnage>> Personnages;
   
}

const std::vector<std::shared_ptr<Personnage>>&State::getPersonnages() const{

    return Personnages;
    
}

void State::initPersonnage (ID_PType PType,int x, int y,int ID_Invocateur){
    
    if (PType = Guerrier){
        std::unique_ptr<Personnage> ptrC1(new Personnage("Ultimate Warrior of DOOM APOCALYPSE",PType,ID_Invocateur));
        ptrC1->setPosition({x,y});
        Personnages.push_back(move(ptrC1));
    }
    if (PType = Mage){
        std::unique_ptr<Personnage> ptrC1(new Personnage("Dark mage of the Lost Forest",PType,ID_Invocateur));
        ptrC1->setPosition({x,y});
        Personnages.push_back(move(ptrC1));
    }
    if (PType = Mage){
        std::unique_ptr<Personnage> ptrC1(new Personnage("Wild Archer of the Old Mountain",PType,ID_Invocateur));
        ptrC1->setPosition({x,y});
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

}
