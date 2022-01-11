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

    switch (Target->getOrientation())
    {
        case state::Face:
            vectTarY = -1;
        case state::Front:
            vectTarY = 1;
        case state::Left:
            vectTarX = -1;
        case state::Right:
            vectTarX = 1;
        default :
            cout << "Ceci n'est pas censé apparaitre \n";
            return 1;
            break;
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

}
