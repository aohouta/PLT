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

}

int HeuristicAI::selectPersonnage(state::State& state){
 
}

int HeuristicAI::selectTarget(state::State& state, int PersonnageIndex){
    
}

bool HeuristicAI::initMapNode(state::State& state){
    int k = 0;
    for(unsigned int i = 0; i < state.map.layout.size(); i++){
        for(unsigned j = 0; j < state.map.layout[i].size(); j++){
            nodes.push_back(Node{state.map.layout[i][j]->getPosition().getX(),
                state.map.layout[i][j]->getPosition().getY(), k, true, 0});
            int CellOccupation = 0;
            for(auto& perso : state.getPersonnages()){
                if(perso->getPosition().Compare(state.map.layout[i][j]->getPosition())) CellOccupation = 1;
                
            }
            if(CellOccupation != 0) nodes.back().setOccupied(true);
            k++;
        }
    }
    //calcule des voisins
    std::vector<Node> alentours;
    for (auto &node : nodes){
        for (auto &node2 : nodes){
            if ( abs(node2.getX() - node.getX()) < 2 && abs(node2.getY() - node.getY()) <2){
                alentours.push_back(node2);
            }
        }
        node.setAlentours(alentours);
        alentours.clear();
    }
    
}

void HeuristicAI::updateMapNodes(state::State& state){
    for(auto &node : nodes){
        node.setOccupied(false);
                for(auto &perso : state.getPersonnages())
                    if(perso->getPosition().getX() == node.getX()
                    && perso->getPosition().getY() == node.getY())
                        node.setOccupied(true);
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
    
}

void HeuristicAI::setNodes(const std::vector<Node>& node){
    
}
