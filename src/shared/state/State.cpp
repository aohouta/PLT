#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>

using namespace std;
namespace state{

std::vector<std::vector<std::unique_ptr<Map>>>& State::getMap (){
    return map;
    
}
void State::initMap (){
    std::string mapResource = "res/MapTest.txt";
    unsigned int i = 0, j = 0, k = 0;

    // mapping (this will be dependent on the choosed resource)
    // dictionary to signalize the type of each tileset by his id
    // (tile id defined by the position of the tile in de resource, we dont define it)
    std::map<int, ID_MType> mapp_spaces;
    
    mapp_spaces[137] = GROUND;
    mapp_spaces[176] = WATER;
   
    
    
    std::ifstream file(mapResource, ios::in);
    int map_tile[25 * 20];

    //this way we read the txt file.
    std::string content, line, tilecode;
    if (!file)
        return;
    while (getline(file, line))
    {
        line += ",";
        content += line;
    }
    cout << "--- file read succesfully ---" << endl;
    file.close();

    // from string to stream
    std::stringstream contentStream(content);
    cout << "--- from string to stream succesfully ---" << endl;

    // delimiting by comma
    while (std::getline(contentStream, tilecode, ','))
    {
        map_tile[i] = std::stoi(tilecode);
        i++;
    }
    cout << "--- building map_tile array succesfully ---" << endl;

    for (i = 0; i < 20; ++i)
    {
        std::vector<std::unique_ptr<Map>> newline;
        for (j = 0; j < 25; ++j)
        {
            cout << map_tile[k] << ",";
            if (map_tile[k])
            {
                if (mapp_spaces.find(map_tile[k]) != mapp_spaces.end())
                {
                    std::unique_ptr<Cell> spc(new Cell(mapp_spaces[map_tile[k]], j, i, map_tile[k]));
                    newline.push_back(move(spc));
                }
                else
                {
                    std::unique_ptr<Cell> spc(new Cell(mapp_spaces[map_tile[8]], j, i, map_tile[8]));
                    newline.push_back(move(spc));
                }
            }
            k++;
        }
        cout << endl;
        map.push_back(move(newline));
    }
    cout << "--- map created succesfully ---" << endl;
    return;
}

State::State (std::string mode){
    this-> mode = mode;
    std::cout << "Creating a state object in >>>" + mode + "<<< mode\n";
    action = IDLE;
    std::vector<std::unique_ptr<Personnage>> Personnages;
}

std::vector<std::unique_ptr<Personnage>> &State::getPersonnage()
{
    return Personnages;
}

void State::initPersonnage (ID_PType PType,int x, int y){
    

    std::unique_ptr<Personnage> ptrC1(new Personnage(PType));
    ptrC1->setPosition({x,y});
    Personnages.push_back(move(ptrC1));


    
    
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

}
