#include "Engine.h"
#include <thread>
#include <unistd.h>

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
            if(state->activePlayer == nullptr){
                int vitMax = 100;
                for(auto& perso : state->getPersonnages()){
                    perso->VitessePos += perso->getVIT();
                    if(perso->VitessePos > vitMax){
                        vitMax = perso->VitessePos;
                        state->activePlayer = perso;
                    }
                }
            }
            sleep(1);
        }
    }
    void Engine::EndTurn(){
        state->activePlayer = nullptr;
    }
    void Engine::Stop(){
        inc.join();
    }
}