#include "ActionCommand.h"
#include <stdio.h>
#include <iostream>

// A deplacer
#include <random>
#include <ctime>
#include<cmath>
#include <math.h>
//

using namespace std;
namespace engine{

// A deplacer
bool Dodge(state::Personnage& Target) {
  srand(time(nullptr));
  int RandNumb = rand() % 100 + 1;
  if(Target.getESQ() >= RandNumb) return true;
  else return false;

}

float ActionCommand::OrientationMult(std::shared_ptr<state::Personnage>& Attacker,std::shared_ptr<state::Personnage>& Target){

    int vectTarX = 0;
    int vectTarY = 0;

    if(Target->getOrientation() == state::Face) {
         vectTarY = -1;
    }
    else if(Target->getOrientation() == state::Front){
        vectTarY = 1;
    }
    else if(Target->getOrientation() == state::Left){
        vectTarX = -1;
    }
    else if(Target->getOrientation() == state::Right){
        vectTarX = 1;
    }
    else { 
        cout << "Ceci n'est pas censé apparaitre \n";
        return 1;
        }
    

    int vectPathX = Attacker->getPosition().getX()-Target->getPosition().getX();
    int vectPathY = Attacker->getPosition().getY()-Target->getPosition().getY();

    float angle = acos((vectTarX*vectPathX+vectTarY*vectPathY)/(sqrt(vectPathX*vectPathX+vectPathY*vectPathY)));

    if(angle <= M_PI/4){
        return 1;
    }
    else if(angle < (3*M_PI/4)){
        return 1.5;
    }
    else return 2;
}

const state::Cell& ActionCommand::getTargetCell() const{
    return TargetCell;
}
void ActionCommand::setTargetCell(const state::Cell& targetCell){
    this->TargetCell = targetCell;
}
const std::shared_ptr<state::Personnage>& ActionCommand::getCaster() const{
    return Caster;
}
void ActionCommand::setCaster(const std::shared_ptr<state::Personnage>& caster){
    this->Caster = caster;
}

}
