//
//  RandomAI.cpp
//  
//
//  Created by abdel houta on 23/12/2021.
//

#include "../ai.h"
#include "engine.h"
#include "state.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <queue>

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;

void HeuristicAI::run(engine::Engine &engine,state::State& state)
{
    updateMapNodes(state);
    cout << "Le personnage sélectionné est ... " << state.activePlayer->getNom() <<" de l'équipe "<< state.activePlayer->getID_Invocateur()<<" !" << endl;
    
    cout << "La cible est ... " << selectTarget(state)->getNom() <<" de l'équipe "<< selectTarget(state)->getID_Invocateur()<< " !" << endl;
    
    Node cible{selectTarget(state)->getPosition().getX(),selectTarget(state)->getPosition().getY(),0,true};
    Node player{state.activePlayer->getPosition().getX(),state.activePlayer->getPosition().getY(),0,true};
    for (auto &node : nodes){
        if (node.getX() == selectTarget(state)->getPosition().getX() && node.getY() == selectTarget(state)->getPosition().getY() ) cible = node;
        if (node.getX() == state.activePlayer->getPosition().getX() && node.getY() == state.activePlayer->getPosition().getY() ) player = node;
    }
    
    cout << "player : "<< player.getX() <<","<< player.getY() <<endl;
    cout << "cible : "<< cible.getX() <<","<< cible.getY() <<endl;
    int distance = abs(player.getX() - cible.getX()) + abs(player.getY() - cible.getY());
    //if (distance <= 1 ) //attack range
    if (distance <= state.activePlayer->getBasicRange())
    {
        cout << state.activePlayer->getNom() <<" de l'équipe "<< state.activePlayer->getID_Invocateur()<<" s'apprête à attaquer la cible ! \n"<< endl;
        ID_Action Action = ATTACKING;
        state.activePlayer->setAction(Action);
        AttackCommand atck(*state.map.layout[selectTarget(state)->getPosition().getX()][selectTarget(state)->getPosition().getY()]);
        atck.Execute(state);
    }
    else{
        Node destination = cible;
        int minimalDist = abs(destination.getX() - state.activePlayer->getPosition().getX()) + abs(destination.getY() - state.activePlayer->getPosition().getY());
        for (auto &voisin : player.alentours){
            
            int dist = abs(destination.getX() - voisin.getX()) + abs(destination.getY() - voisin.getY());
            int range = abs(voisin.getX() - state.activePlayer->getPosition().getX()) + abs(voisin.getY() - state.activePlayer->getPosition().getY());
            if (dist < minimalDist && range <= state.activePlayer->getMOB() ){
                minimalDist = dist;
                cible = voisin;
            }
        }
        cout << " dist optimal = " << minimalDist << endl;
        cout << state.activePlayer->getNom() <<" de l'équipe "<< state.activePlayer->getID_Invocateur()<< " s'apprête à avancer à la position -> ("<< cible.getX() << "," << cible.getY() <<")...\n"<< endl;
        ID_Action Action = MOVING;
        state.activePlayer->setAction(Action) ;
        MoveCommand move(*state.map.layout[cible.getX()][cible.getY()]);
        move.Execute(state);

        //to optimise
        //if in range after move
        cout << "player : "<< player.getX() <<","<< player.getY() <<endl;
        cout << "cible : "<< cible.getX() <<","<< cible.getY() <<endl;
        

        if (minimalDist <= state.activePlayer->getBasicRange())
        {
            cout << state.activePlayer->getNom() <<" de l'équipe "<< state.activePlayer->getID_Invocateur()<<" s'apprête à attaquer la cible ! \n"<< endl;
            ID_Action Action = ATTACKING;
            state.activePlayer->setAction(Action);
            AttackCommand atck(*state.map.layout[selectTarget(state)->getPosition().getX()][selectTarget(state)->getPosition().getY()]);
            atck.Execute(state);
        }
    }
    
    
    
    
    cout << "Fin de l'action.\n" << endl;
    

    
}

shared_ptr<state::Personnage> HeuristicAI::selectTarget(state::State& state){
    
    shared_ptr<state::Personnage> ennemiPerso;
    int minimalDist = 45;
   
    for(auto &perso : state.getPersonnages()){
        if (perso->getID_Invocateur() != state.activePlayer->getID_Invocateur() && perso->getEtatPerso() != Mort){
            if (perso->getPType() == Mage) ennemiPerso = perso;
            else if (perso->getPV() == 0.3*perso->getPVmax()) ennemiPerso = perso;
            else if (perso->getDEF() <= state.activePlayer->getATK()) ennemiPerso = perso;
            int distance = abs(state.activePlayer->getPosition().getX() - perso->getPosition().getX()) + abs(state.activePlayer->getPosition().getY() - perso->getPosition().getY());
            if( distance < minimalDist){
                minimalDist = distance;
                ennemiPerso = perso;
            }
        }
        
    }
    return ennemiPerso;
}

bool HeuristicAI::initMapNode(state::State& state){
    cout << "Initialisation des nodes" << endl;
    int k = 0;
    for(unsigned int i = 0; i < state.map.layout.size(); i++){
        for(unsigned j = 0; j < state.map.layout[i].size(); j++){
            nodes.push_back(Node{state.map.layout[i][j]->getPosition().getX(),
                state.map.layout[i][j]->getPosition().getY(), k, false, 0});
            int CellOccupation = 0;
            for(auto& perso : state.getPersonnages()){
                if(perso->getPosition().Compare(state.map.layout[i][j]->getPosition())) CellOccupation = 1;
                
            }
            if(CellOccupation != 0) nodes.back().setOccupied(true);
            k++;
        }
    }
    //calcule des voisins
    cout << "Initialisation des voisins" << endl;
    bool valid;
    int tailleMapX = static_cast<int>(state.map.layout.size());
    int tailleMapY = static_cast<int>(state.map.layout[0].size());
    cout << "Initialisation des voisins 2" << endl;
    for (auto &node : nodes){
        if (node.getOccupied() == true){
            for (auto &node2 : nodes){
                valid = true;
                // if ( node2.getOccupied() != true && abs(node.getX() - node2.getX()) + abs(node.getY() - node2.getY()) <= 2 ){
                valid = abs(node.getX() - node2.getX()) + abs(node.getY() - node2.getY()) <= state.getPersonnages()[0]->getMOB();
                //check if in map
                if (node2.getX() >= tailleMapX || node2.getX() < 0){
                    valid = false;
                }
                if (node2.getY() >= tailleMapY || node2.getY() < 0){
                    valid = false;
                }
                

                if ( node2.getOccupied() != true && valid == true  ){
                    cout << "distance : " << abs(node.getX() - node2.getX()) + abs(node.getY() - node2.getY()) << endl;
                    node.alentours.push_back(node2);
                }
            }
        }
    }
    
}

void HeuristicAI::updateMapNodes(state::State& state){
    int tailleMapX = static_cast<int>(state.map.layout.size());
    int tailleMapY = static_cast<int>(state.map.layout[0].size());
    for(auto &node : nodes){
        node.setOccupied(false);
        int i = 0;
        for(auto &perso : state.getPersonnages()){
            if(perso->getPosition().getX() == node.getX() && perso->getPosition().getY() == node.getY()){
                
                node.setOccupied(true);
                bool valid;
                for (auto &node2 : nodes){
                     valid = true;
                    // if ( node2.getOccupied() != true && abs(node.getX() - node2.getX()) + abs(node.getY() - node2.getY()) <= 2 ){
                    valid = abs(node.getX() - node2.getX()) + abs(node.getY() - node2.getY()) <= state.getPersonnages()[i]->getMOB();
                    //check if in map
                    if (node2.getX() >= tailleMapX || node2.getX() < 0){
                        valid = false;
                    }
                    if (node2.getY() >= tailleMapY || node2.getY() < 0){
                        valid = false;
                    }
                    if ( node2.getOccupied() != true && valid ==true ) node.alentours.push_back(node2);
                }
            }
            i++;
        }
        for(int i= 0; i< node.alentours.size();i++){
            if (node.alentours[i].getOccupied() == true) node.alentours.erase(node.alentours.begin()+i,node.alentours.begin()+i+1);
        }
        
    }
}
/*
struct ComparePoids {
    bool operator ()( const Node& a, const Node& b) const
    { return a.getPoids() < b.getPoids() ;}
    
};

std::list<Node> HeuristicAI::shortestPath (Node& depart, Node& finish){
    //dijkstra
    
    
    //set poids aux nodes
    for(auto &node : nodes){
        cout << "Poids de la Node "<< "("<< node.getX() <<","<< node.getY()<<") "<<": "<< node.getPoids() << endl;
    }
    depart.setPoids(0);
    
    //traitement
    bool found = false;
    vector<Node> chemin;
    priority_queue <Node,vector<Node>,ComparePoids> ouvert ;
    ouvert.push(depart);
    
    while(!ouvert.empty()){
        auto p = ouvert.top();
        int poids = p.getPoids();
        ouvert.pop();
        
        //changement de poids
        if (p.getX() == finish.getX() && p.getY() == finish.getY()) {
            found = true;
        }
        for (auto &voisin : p.getAlentours() ){
            int newpoids = poids + p.distance(voisin);
            if (newpoids < voisin.getPoids()) voisin.setPoids(newpoids);
        }
    }

}
*/
std::vector<Node> const & HeuristicAI::getNodes() const{
    return nodes;
}

void HeuristicAI::setNodes(const std::vector<Node>& node){
    this-> nodes = node;
}

