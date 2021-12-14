#include "Cell.h"

namespace state{

Cell::Cell (ID_MType id, int newX, int newY, int tileCode){
    this->MType = id;
    this->position.setX(newX);
    this->position.setY(newY);
    this->tileCode = tileCode;
}


int Cell::isOccupied(){
    return occupation;
}


}
