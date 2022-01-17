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
    int indexperso = selectPersonnage(state);
    Personnage &Perso = *state.getPersonnages()[indexperso];
    state.activePlayer = state.getPersonnages()[indexperso];
    cout << "Le personnage sélectionné est ... " << Perso.getNom() << "!" << endl;
    
    int indexennemi = selectTarget(state,indexperso);
    Personnage &target = *state.getPersonnages()[indexennemi];
    cout << "La cible est ... " << target.getNom() << "!" << endl;
    Node destination{target.getPosition().getX(),target.getPosition().getY(),0,true};
    for (auto &node : nodes){
        if (node.getX() == target.getPosition().getX() && node.getY() == target.getPosition().getY() ) destination = node;
    }
    
    cout << Perso.getNom() << " s'apprête à avancer à la position -> ("<< destination.alentours[0].getX() << "," << destination.alentours[0].getY() <<")...\n"<< endl;
    ID_Action Action = MOVING;
    Perso.setAction(Action) ;
    MoveCommand move(*state.map.layout[destination.alentours[0].getX()][destination.alentours[0].getY()]);
    move.Execute(state);
    
    cout << Perso.getNom() << " s'apprête à attaquer la cible ! \n"<< endl;
    Action = ATTACKING;
    Perso.setAction(Action);
    AttackCommand atck(*state.map.layout[target.getPosition().getX()][target.getPosition().getY()]);
    atck.Execute(state);
    
    
    cout << "Fin de l'action.\n" << endl;
    
    
    
}

int HeuristicAI::selectPersonnage(state::State& state){
    // selectionne le personnage le plus près d'un ennemi
    int index = -1;
    int globalMinDist = INT32_MAX;

    for (unsigned int i = 0; i < state.getPersonnages().size(); i++){
        if (state.getPersonnages()[i]->getEtatPerso() != Mort){
            int minimalDistance = INT32_MAX;
            for (auto &enemiPerso : state.getPersonnages())
                if(enemiPerso->getID_Invocateur() != state.getPersonnages()[i]->getID_Invocateur() && enemiPerso->getEtatPerso() != Mort){
                    int distance = abs(state.getPersonnages()[i]->getPosition().getX() - enemiPerso->getPosition().getX()) + abs(state.getPersonnages()[i]->getPosition().getY() - enemiPerso->getPosition().getY());
                    if(distance < minimalDistance){
                        minimalDistance = distance;
                    }
                    if(minimalDistance < globalMinDist){
                        globalMinDist = minimalDistance;
                        index = i;
                    }
                }
        }
    }
    return index;
}

int HeuristicAI::selectTarget(state::State& state, int PersonnageIndex){
    
    Personnage &Perso = *state.getPersonnages()[PersonnageIndex];
    int index = -1;
    int minimalDist = INT32_MAX;
   
    for(unsigned int i = 0; i < state.getPersonnages().size(); i++){
        Personnage &ennemiPerso = *state.getPersonnages()[i];
        int distance = abs(Perso.getPosition().getX() - ennemiPerso.getPosition().getX()) + abs(Perso.getPosition().getY() - ennemiPerso.getPosition().getY());
        if(state.getPersonnages()[i]->getID_Invocateur() != Perso.getID_Invocateur() && state.getPersonnages()[i]->getEtatPerso() != Mort && distance < minimalDist){
            index = i;
            minimalDist = distance;
        }
    }
    return index;
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
    for (auto &node : nodes){
        if (node.getOccupied() == true){
            for (auto &node2 : nodes){
                if ( node2.getOccupied() != true && abs(node.getX() - node2.getX()) + abs(node.getY() - node2.getY()) <2 ){
                    cout << "distance : " << abs(node.getX() - node2.getX()) + abs(node.getY() - node2.getY()) << endl;
                    node.alentours.push_back(node2);
                }
            }
        }
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
    return nodes;
}

void HeuristicAI::setNodes(const std::vector<Node>& node){
    this-> nodes = node;
}
