#include "Engine.h"
#include <thread>
#include <unistd.h>
#include <iostream>

using namespace std;

namespace engine{
    Engine::Engine(state::State& state){
        this->state = &state;
    }
    void Engine::Start(){
        inc = thread(&Engine::Increment, this);
    }
    void Engine::Increment(){
        while(!state->gameOver){
            stateMute.lock();
            if(state->activePlayer == nullptr){
                int vitMax = 100;
                for(auto& perso : state->getPersonnages()){
                    perso->VitessePos += perso->getVIT();
                    cout << "name = " << perso->getPType() << "Vitesse actuelle =" << perso->VitessePos << endl ;
                    if(perso->VitessePos >= vitMax){
                        vitMax = perso->VitessePos;
                        state->activePlayer = perso;
                    }
                }
                cout << endl;
            }
            if(!(state->activePlayer == nullptr)) {
                state->activePlayer->VitessePos = 0;
            }
            stateMute.unlock();
            sleep(1);
        }
    }
    void Engine::EndTurn(){
        state->activePlayer = nullptr;
        int vitMax = 100;
        for(auto& perso : state->getPersonnages()){
            cout << "name = " << perso->getPType() << "Vitesse actuelle =" << perso->VitessePos << endl;
            if(perso->VitessePos >= vitMax){
                vitMax = perso->VitessePos;
                state->activePlayer = perso;
            }
        }
    }
    void Engine::Stop(){
        inc.join();
    }
}