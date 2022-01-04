#include "Engine.h"
#include <thread>
#include <unistd.h>

using namespace std;

namespace engine{
    void Engine::Start(state::State& state){
        inc = thread(&Engine::Increment, this, state);
    }
    void Engine::Increment(state::State& state){
        while(1){
            if(state.activePlayer == nullptr){
                int vitMax = 100;
                for(auto& perso : state.getPersonnages()){
                    perso->VitessePos += perso->getVIT();
                    if(perso->VitessePos > vitMax){
                        vitMax = perso->VitessePos;
                        auto active = perso;
                        state.activePlayer = active;
                    }
                }
            }
            sleep(1);
        }
    }
    void Engine::EndTurn(state::State& state){
        state.activePlayer = nullptr;
    }
    void Engine::Stop(){
        inc.join();
    }
}