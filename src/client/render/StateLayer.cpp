#include "../render.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <unistd.h>
#include <queue>

using namespace std;
using namespace state;
namespace render{

void StateLayer::initLayer (state::State& state){
    render::LoadLayer LoadMap;
    LoadMap.loadTextures(state, tile[0]->getTexture(), sf::Vector2u(tile[0]->getCellWidth(), tile[0]->getCellHeight()), state.getMap().size(), state.getMap()[0].size());
    std::unique_ptr<LoadLayer> ptrLoadMap(new LoadLayer(LoadMap));
    
    render::LoadLayer Personnages;
    Personnages.loadPersonnage(state, tile[1]->getTexture(), sf::Vector2u(tile[1]->getCellWidth(), tile[1]->getCellHeight()), state.getPersonnage().size(),1);
    std::unique_ptr<LoadLayer> ptrPersonnage(new LoadLayer(Personnages));


    if (layer.size() != 0)
    {
        while (layer.size() != 0)
        {
            layer.pop_back();
        }
    }

    layer.push_back(move(ptrLoadMap));
    layer.push_back(move(ptrPersonnage));
}

StateLayer::StateLayer (state::State& state, sf::RenderWindow& window) : window(window), currentState(state)
{
    std::unique_ptr<Tile> tileMap(new Tile(TileID::MAP,32,32));
    tile.push_back(move(tileMap));
    
    std::unique_ptr<Tile> tilesetCharacters(new Tile(TileID::CHARACTER, 32,32));
    tile.push_back(move(tilesetCharacters));



    
}

const std::vector<std::unique_ptr<Tile>>& StateLayer::getTile () const{
    //std::vector<std::unique_ptr<Tile>>& refTile = tile;
    
    return tile;
}

const std::vector<std::unique_ptr<LoadLayer>>& StateLayer::getLayer () const{
    //std::vector<std::unique_ptr<LoadLayer>>& refLoadLayer = layer;
    return layer;

}

void StateLayer::draw (sf::RenderWindow& window){
    window.clear();
    // draw mapcells
    window.draw(layer[0]->quads,&(layer[0]->texture));
    
    // draw characters
    window.draw(layer[1]->quads,&(layer[1]->texture));

       
    for(auto& d : drawables){
        window.draw(d);
    }

    window.display();
}

};
