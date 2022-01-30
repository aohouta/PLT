#include "Command.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../json.hpp"

using json = nlohmann::json;

using namespace std;



namespace engine{


int Command::save(const std::string& CommandName, state::Cell& Target, state::State& state){
    int x = Target.getPosition().getX();
    int y = Target.getPosition().getY();



    // Not optimal at all but working !
    //save last json
    ifstream i("replay.txt");
    json replay,header;
    i >> replay;
    vector<json> listePerso = replay["PersonnagesList"];
    vector<json> listeCommand = replay["CommandList"];

    //remove it
    remove("replay.txt");

    
    //create new with new command
    std::ofstream out;
   
    json j ={
        {"Command", CommandName},
        {"x", x},
        {"y",y},
        {"Type", state.activePlayer->getPType()},
        {"Team", state.activePlayer->getID_Invocateur()}
    };

    listeCommand.push_back(j);

    out.open("replay.txt", std::ios::app);
    header["PersonnagesList"] = listePerso;
    header["CommandList"] = listeCommand;
    out << std::setw(4) << header << std::endl;

    return 0;
}


}