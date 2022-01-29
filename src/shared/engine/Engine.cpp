#include "Engine.h"
#include <thread>
#include <unistd.h>
#include <iostream>

using namespace std;



namespace engine{

    bool Engine::IsGameOver(state::State& state){
        int team1 = 0;
        int team2 = 0;
        for(auto &perso : state.getPersonnages()){
            if(perso->getID_Invocateur() == 1) {
                team1 = 1;
            }
            if(perso->getID_Invocateur() == 2) {
                team2 = 1;
            }
        }
        
        if (team1 == 0 && team2 == 0){ 
            cout << "négalité" << endl;
            //set state to over
            return true;}
        else if (team1 == 0){
            cout << "team 2 win" << endl;
            //set state to over
            return true;
        }
        else if (team2 == 0){
            cout << "team 1 win" << endl;
            //set state to over
            return true;
        }
        else {
            return false;
        }
        
    }

    Engine::Engine(state::State& state){
        this->state = &state;
    }
    
    void Engine::Start(int time){
        timing = time;
        inc = thread(&Engine::Increment, this);
    }
    
    void Engine::Increment(){
        /*
        while(!state->gameOver){
            stateMute.lock();
            if(state->activePlayer == nullptr){
                int vitMax = 100;
                for(auto& perso : state->getPersonnages()){
                    perso->VitessePos += perso->getVIT();
                    cout << "name = " << perso->getNom() << " de l'équipe " <<  perso->getID_Invocateur() << " Vitesse actuelle =" << perso->VitessePos << endl ;
                    if(perso->VitessePos >= vitMax){
                        vitMax = perso->VitessePos;
                        state->activePlayer = perso;
                        //Start turn
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
        */
       int vitMax = 0;
       int vitSeuil = 100;
       int i = 0;
       int j = 0;

       for(auto& perso : state->getPersonnages()){
           cout << "name = " << perso->getNom() << " de l'équipe " <<  perso->getID_Invocateur() << " Vitesse init =" << perso->VitessePos << endl ;

           if(perso->VitessePos >= vitMax){
               vitMax = perso->VitessePos;
               j = i;
           }
           i++;
       }
       
       //init
        while (vitMax < vitSeuil ) {      
            i = 0; 
                for(auto& perso : state->getPersonnages()){
                    perso->VitessePos += perso->getVIT();
                    cout << "name = " << perso->getNom() << " de l'équipe " <<  perso->getID_Invocateur() << " Vitesse actuelle =" << perso->VitessePos << endl ;
                    if(perso->VitessePos >= vitMax){
                        vitMax = perso->VitessePos;
                        j = i;
                    }
                    i++;
                }
        }

        cout << "name = " << state->getPersonnages()[j]->getNom() << " de l'équipe " <<  state->getPersonnages()[j]->getID_Invocateur() << " Vitesse actuelle =" << state->getPersonnages()[j]->VitessePos << endl ;
        state->activePlayer = state->getPersonnages()[j];
        state->activePlayer->VitessePos = 0;


                        
    }


    void Engine::EndTurn(){
        state->activePlayer = nullptr;
        int vitMax = 100;
        for(auto& perso : state->getPersonnages()){
            cout << "name = " << perso->getNom() << " de l'équipe " <<  perso->getID_Invocateur() << " Vitesse actuelle =" << perso->VitessePos << endl ;
            if(perso->VitessePos >= vitMax){
                vitMax = perso->VitessePos;
                state->activePlayer = perso;
            }
        }
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