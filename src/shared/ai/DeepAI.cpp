#include "DeepAI.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "engine.h"
#include "state.h"

using namespace std;
using namespace engine;
using namespace state;

namespace ai {
    void DeepAI::run(state::State& state){
        while(state.activePlayer == nullptr){;}
        auto player = state.activePlayer;
        for(auto& perso : state.getPersonnages()){
            if(perso->getID_Invocateur() != player->getID_Invocateur()){
                enemies.push_back(perso);
            }
        }
        int playerCount = enemies.size();
        //SaveState rollback(state);
        State tempstate{"dump"};
        tempstate = state;
        for(auto& perso : enemies){
            NearestPos(perso, player);
            MoveCommand mouve(*tempstate.map.layout[coord[0]][coord[1]]);
            mouve.Execute(tempstate);
            if(CheckForRange(perso, player)){
                AttackCommand atak(*tempstate.map.layout[perso->getPosition().getX()][perso->getPosition().getY()]);
                atak.Execute(tempstate);
            }
            HeuristicAI hai;
            Engine tempNgine(tempstate);
            tempNgine.Start(0);
            hai.initMapNode(tempstate);
            int timout = 0;
            while((tempstate.getPersonnages().size()>=state.getPersonnages().size())  && timout < 5){
                while(tempstate.activePlayer == nullptr){;}
                hai.run(tempNgine,tempstate);
                tempNgine.EndTurn();
                timout++;
            }
            tempstate.gameOver=true;
            tempNgine.Stop();
            int newplcnt = 0;
            for(auto& perso : tempstate.getPersonnages()){
                if(perso->getID_Invocateur() != player->getID_Invocateur()){
                    newplcnt++;
                }
            }   
            if(tempstate.getPersonnages().size()==state.getPersonnages().size()){
                score.push_back(0);
            }
            else if(playerCount>newplcnt){
                score.push_back(1);
            }
            else {
                score.push_back(-1);
            }
        }
        int choice = 0;
        int cScore = -1;
        for(int i = 0; i<score.size();i++){
            if(score[i]>cScore){
                cScore = score[i];
                choice = i;
            }
        }
        NearestPos(enemies[choice], player);
        MoveCommand mouve(*state.map.layout[coord[0]][coord[1]]);
        mouve.Execute(state);
        AttackCommand atak(*state.map.layout[enemies[choice]->getPosition().getX()][enemies[choice]->getPosition().getY()]);
        atak.Execute(state);
        enemies.clear();
        score.clear();
    }
    int DeepAI::CheckForRange(std::shared_ptr<state::Personnage> perso, std::shared_ptr<state::Personnage> player){
        int dist = abs(perso->getPosition().getX() - player->getPosition().getX()) + abs(perso->getPosition().getY() - player->getPosition().getY());
        if(dist < player->getBasicRange()){return 1;}
        return 0;
    }
    void DeepAI::NearestPos(std::shared_ptr<state::Personnage> perso, std::shared_ptr<state::Personnage> player){
        cout << player->getMOB();
        int dist = abs(perso->getPosition().getX() - player->getPosition().getX()) + abs(perso->getPosition().getY() - player->getPosition().getY());
        for(int x = -(player->getMOB());x++;x<=(player->getMOB())){
            for(int y = -(player->getMOB());y++;y<=(player->getMOB())){
                if((x+y)<player->getMOB()){
                    int newx = player->getPosition().getX() + x;
                    int newy = player->getPosition().getY() + y;
                    int tempdist = abs(perso->getPosition().getX() - newx) + abs(perso->getPosition().getY() - newy);
                    if((0<tempdist) && (tempdist<=dist)){
                        coord[0] = newx;
                        coord[1] = newy;
                    }
                }
            }
        }
    }
}