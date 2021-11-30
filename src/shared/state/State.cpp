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
    
    mapp_spaces[118] = Lowland;
    mapp_spaces[119] = Lowland;
    mapp_spaces[120] = Lowland;
    mapp_spaces[141] = Lowland;
    mapp_spaces[142] = Lowland;
    mapp_spaces[143] = Lowland;
    mapp_spaces[164] = Lowland;
    mapp_spaces[165] = Lowland;
    mapp_spaces[166] = Lowland;
    mapp_spaces[520] = Lowland;
    mapp_spaces[566] = Lowland;
    mapp_spaces[39] = Mountain;
    mapp_spaces[40] = Mountain;
    mapp_spaces[43] = Mountain;
    mapp_spaces[44] = Mountain;
    mapp_spaces[31] = Mountain; // actually is wood
    mapp_spaces[54] = Mountain; // actually is wood
    mapp_spaces[55] = Mountain; // actually is wood
    mapp_spaces[77] = Mountain; // actually is wood
    mapp_spaces[496] = Forest;
    mapp_spaces[497] = Forest;
    
    
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
                    std::unique_ptr<Cell> spc(new Cell(mapp_spaces[map_tile[118]], j, i, map_tile[118]));
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
}

std::vector<std::unique_ptr<Personnage>> &State::getPersonnage()
{
    vector<unique_ptr<Personnage>> &refPersonnages = Personnages;
    return refPersonnages;
}

}
