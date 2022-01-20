
#include "Position.h"



using namespace std;

namespace state{

Position::Position(int x, int y){
    this->x=x;
    this->y=y;
}

int Position::getX() const{
    return this->x;
}

int Position::getY() const{
    return this->y;
}

void Position::setX(int newX){
    this->x = newX;
}

void Position::setY(int newY){
    this->y = newY;
}

bool Position::Compare (const Position& position) const{
    if(this->x == position.getX() && this->y == position.getY()){
        return true;
    }
    else {return false;}
}

};
