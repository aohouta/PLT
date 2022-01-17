#include "Engine.h"
#include <stdio.h>
#include <iostream>



using namespace std;



namespace engine{

    void Engine::UpdateEffet(shared_ptr<state::Personnage> target){

        vector<state::Effet> newListeEffet = target->getListeEffet();
        size_t i = 0;

        while( i < newListeEffet.size() ){

            newListeEffet[i].setEffetDuree(newListeEffet[i].getEffetDuree() - 1);
            //when EffetDuree reach 0, the effect end
            if(newListeEffet[i].getEffetDuree() <= 0){
                newListeEffet.erase(newListeEffet.begin()+i);
            }
            else {
                i++;
            }
        }

        target->setListeEffet(newListeEffet);
    }

}