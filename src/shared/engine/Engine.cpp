#include "Engine.h"
#include <thread>
#include <unistd.h>
#include <iostream>

using namespace std;

namespace engine{
    Engine::Engine(state::State& state){
        this->state = &state;
    }
    void Engine::Start(int time){
        timing = time;
        inc = thread(&Engine::Increment, this);
    }
    void Engine::Increment(){
        while(!state->gameOver){
            stateMute.lock();
            if(state->activePlayer == nullptr){
                int vitMax = 100;
                for(auto& perso : state->getPersonnages()){
                    cout << "name = " << perso->getNom() << " de l'équipe " <<  perso->getID_Invocateur() << " Vitesse actuelle =" << perso->VitessePos << endl ;
                    if(perso->VitessePos >= vitMax){
                        vitMax = perso->VitessePos;
                        state->activePlayer = perso;
                        //Start turn
                    }
                    if(state->activePlayer == nullptr){
                        perso->VitessePos += perso->getVIT();
                    }
                }
                cout << endl;
            }
            stateMute.unlock();
            sleep(timing);
        }
    }
    void Engine::EndTurn(){
        state->activePlayer->VitessePos = 0;
        state->activePlayer = nullptr;
    }
    void Engine::Stop(){
        inc.join();
    }

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