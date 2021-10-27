#include "Personnage.h"
#include <iostream>

using namespace std;
namespace state {

vector<int> Personnage::getStats(){
    cout << "fromage\n";
    vector<int> fze = {4,2};
    return fze;
}

Personnage::Personnage(ID_PType PType){
    this->PType = PType;
}

Personnage::~Personnage(){
    
}

}