#include <string>
#include "../render.h"
#include <iostream>

namespace render{

Tile::Tile (TileID tileID,  int Width, int Height){
    this->tileID = tileID;
    this->Width = Width;
    this->Height = Height;
    
    if (tileID == TileID::CHARACTER){
        resourceFile = "../../../res/mage.png";
    }
    
    else if (tileID == TileID::HUD){
        resourceFile = "../../../res/HUD.png";
    }
    
    else if (tileID == TileID::MAP){
        resourceFile = "../../../res/Isometric_MedievalFantasy_Tiles.png";
    }
    
    if (!textureTile.loadFromFile(resourceFile)){
        std::cout <<"\n FAILED \n";
    }
    
}

const std::string Tile::getImageFile (){
    return resourceFile;
}

int const Tile::getCellWidth (){
    return Width;
}

int const Tile::getCellHeight (){
    return Height;
}

int const Tile::getTileID (){
    return tileID;
}

sf::Texture& Tile::getTexture (){
    
    sf::Texture& refTexture = textureTile;
    return refTexture;
    
}

};
