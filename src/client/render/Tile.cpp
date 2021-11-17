#include "Tile.h"
#include "TileID.h"

namespace render{

Tile::Tile (TileID tileID, int x, int y, int Width, int Height){
    this->tileID = tileID;
    this->x = x;
    this->y = y;
    this->Width = Width;
    this->Height = Height;
    
}

const std::string Tile::getImageFile (){
    return "lalala";
}

int const Tile::getCellWidth (){
    return 1;
}

int const Tile::getCellHeight (){
    return 1;
}

int const Tile::getTileID (){
    return 1;
}

};
