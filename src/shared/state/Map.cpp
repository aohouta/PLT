#include "Map.h"

namespace state{

Map::Map(){}


int Map::getTileCode() const{
    return tileCode;
}



void Map::setTileCode(int tileCode){
    this->tileCode = tileCode;
    
}

}
