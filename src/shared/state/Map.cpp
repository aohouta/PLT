#include "Map.h"

namespace state{

int Map::getTileCode() {
    return tileCode;
}

void Map::setTileCode(int tileCode){
    this->tileCode = tileCode;
    
}
Position &Map::getPosition(){
    Position &refPosition = position;
    return refPosition;
}
}
