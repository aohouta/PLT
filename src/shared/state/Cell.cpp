#include "../state.h"

namespace state{

Cell::Cell (ID_MType id,  int newX, int newY, int tilecode){
    this->MType = id;
    this->position.setX(newX);
    this->position.setY(newY);
    this->tileCode = tilecode;
}


int Cell::isOccupied(){
    return occupation;
}


}
