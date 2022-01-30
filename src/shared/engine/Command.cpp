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


int Command::save(const std::string& CommandName, state::Cell& Target){
    int x = Target.getPosition().getX();
    int y = Target.getPosition().getX();
    std::ofstream out;
    //out.open("CommandSave.json", std::ios::app);
    out.open("replay.txt", std::ios::app);
    json j ={
        {"Command", CommandName},
        {"x", x},
        {"y",y}
    };
    out << std::setw(4) << j << std::endl;
    return 0;
}


}