//
//  RandomAI.cpp

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
    shared_ptr<state::Personnage> cible = selectTarget(state);
    Node cibleNode, playerNode;
    for(auto &node : nodes){
        if (node.occupiedBy == state.activePlayer) {
            playerNode  = node;
        }
        else if (node.occupiedBy == cible){
            cibleNode = node;
        }
            
    }
 

    cout << "Le personnage sélectionné est ... " << state.activePlayer->getNom() <<" de l'équipe "<< state.activePlayer->getID_Invocateur()<<" !" << endl;
    
    cout << "La cible est ... " << cible->getNom() <<" de l'équipe "<< cible->getID_Invocateur()<< " !" << endl;
    
    
    
    cout << "player : "<<  state.activePlayer->getPosition().getX() <<","<< state.activePlayer->getPosition().getY() <<endl;
    cout << "cible : "<< cible->getPosition().getX() <<","<< cible->getPosition().getY() <<endl;
    int distance = abs(state.activePlayer->getPosition().getX() - cible->getPosition().getX()) + abs(state.activePlayer->getPosition().getY() - cible->getPosition().getY());

    //target is in attack range
    if (distance <= state.activePlayer->getBasicRange())
    {
        cout << state.activePlayer->getNom() <<" de l'équipe "<< state.activePlayer->getID_Invocateur()<<" s'apprête à attaquer la cible ! \n"<< endl;
        AttackCommand atck(*state.map.layout[cible->getPosition().getX()][cible->getPosition().getY()]);
        atck.Execute(state);
    }
    else{
        //Move closer as possible from target
        Node caseCibleN;
        int minimalDist = abs(cibleNode.getX() - state.activePlayer->getPosition().getX()) + abs(cibleNode.getY() - state.activePlayer->getPosition().getY());
        for (auto &voisin : playerNode.alentours){
            
            int dist = abs(cibleNode.getX() - voisin.getX()) + abs(cibleNode.getY() - voisin.getY());
            int range = abs(voisin.getX() - state.activePlayer->getPosition().getX()) + abs(voisin.getY() - state.activePlayer->getPosition().getY());
            if (dist < minimalDist && range <= state.activePlayer->getMOB() ){
                minimalDist = dist;
                caseCibleN = voisin;
            }
            if ( dist == state.activePlayer->getBasicRange()) {
                caseCibleN = voisin;
                break;
            }
        }

        cout << " dist optimal = " << minimalDist << endl;
        cout << state.activePlayer->getNom() <<" de l'équipe "<< state.activePlayer->getID_Invocateur()<< " s'apprête à avancer à la position -> ("<< caseCibleN.getX() << "," << caseCibleN.getY() <<")...\n"<< endl;
        MoveCommand move(*state.map.layout[caseCibleN.getX()][caseCibleN.getY()]);
        move.Execute(state);

        //to optimise
        //if in range after move
        cout << "player : "<< state.activePlayer->getPosition().getX() <<","<< state.activePlayer->getPosition().getY() <<endl;
        cout << "cible : "<< cibleNode.getX() <<","<< cibleNode.getY() <<endl;
        

        if (minimalDist <= state.activePlayer->getBasicRange())
        {
            cout << state.activePlayer->getNom() <<" de l'équipe "<< state.activePlayer->getID_Invocateur()<<" s'apprête à attaquer la cible ! \n"<< endl;
            AttackCommand atck(*state.map.layout[selectTarget(state)->getPosition().getX()][selectTarget(state)->getPosition().getY()]);
            atck.Execute(state);
        }
    }
    
    
    
    
    cout << "Fin de l'action.\n" << endl;
    

    
}

shared_ptr<state::Personnage> HeuristicAI::selectTarget(state::State& state){
    
    shared_ptr<state::Personnage> ennemiPerso;
    vector<Node> listOfTarget;
    int distance, nodeWeight;
    for(auto &node : nodes){
        //Looking for node where an enemy is standing
       if (node.occupiedBy != NULL && node.occupiedBy->getEtatPerso() != Mort && node.occupiedBy->getID_Invocateur() != state.activePlayer->getID_Invocateur()){
           ennemiPerso = node.occupiedBy;
            distance =  abs(state.activePlayer->getPosition().getX() - ennemiPerso->getPosition().getX()) + abs(state.activePlayer->getPosition().getY() - ennemiPerso->getPosition().getY());
            if (distance <= state.activePlayer->getMOB()+state.activePlayer->getBasicRange() ) {

                //dmg formula
                int BaseATK = state.activePlayer->getTotalAttack();
                int BaseDEF = ennemiPerso->getTotalDef();
                float BaseDmg = BaseATK*(1-(BaseDEF/100));
                //target
                if ( static_cast<int>(BaseDmg) >= ennemiPerso->getPV() ) {
                    //Mage is top priority
                    if (ennemiPerso->getPType() == Mage) {
                        node.poids = 9;} 
                    //Archer is second priority
                    else if(ennemiPerso->getPType() == Archer) {
                        node.poids = 8;}
                    else {
                        node.poids = 7;
                    }
                                  
                }
                else {
                    //Mage is top priority
                    if (ennemiPerso->getPType() == Mage) {
                        node.poids = 6;} 
                    //Archer is second priority
                    else if(ennemiPerso->getPType() == Archer) {
                        node.poids = 5;}
                    else {
                        node.poids = 4;
                    }

                }
            }
            else {
                //Mage is top priority
                if (ennemiPerso->getPType() == Mage) {
                    node.poids = 3;} 
                //Archer is second priority
                else if(ennemiPerso->getPType() == Archer) {
                    node.poids = 2;}
                else {
                    node.poids = 1;}
            }
        listOfTarget.push_back(node);
       }
    }
    nodeWeight = listOfTarget[0].poids;
    for(auto &node : listOfTarget){
        if(node.poids >= nodeWeight ){
            ennemiPerso = node.occupiedBy;
        }

    }
    
    return ennemiPerso;
}

bool HeuristicAI::initMapNode(state::State& state){

    cout << "Initialisation des nodes" << endl;

    int tailleMapX = static_cast<int>(state.map.layout.size());
    int tailleMapY = static_cast<int>(state.map.layout[0].size());

 
    shared_ptr<state::Personnage> persoOnNode;

    //Look for every cell on the map
    for(int i = 0; i < tailleMapX; i++){
        for( int j = 0; j < tailleMapY; j++){
            persoOnNode = NULL;           
            //if someone on a cell = node is occuped
            for(auto& perso : state.getPersonnages()){
                if(perso->getPosition().Compare(state.map.layout[i][j]->getPosition())) persoOnNode = perso;
                }
            Node newNode( state.map.layout[i][j]->getPosition().getX() , state.map.layout[i][j]->getPosition().getY() ,i+j, persoOnNode, 0);
            nodes.push_back(newNode);
        }
    }
    //calcule des voisins
    cout << "Initialisation des voisins" << endl;

    bool valid;

    for (auto &node : nodes){
        if (node.occupiedBy != NULL){

            for (auto &node2 : nodes){
                valid = true;
                valid = node.distance(node2) <= node.occupiedBy->getMOB();

                //check if in map
                if (node2.getX() >= tailleMapX || node2.getX() < 0){
                    valid = false;
                }
                if (node2.getY() >= tailleMapY || node2.getY() < 0){
                    valid = false;
                }
                

                if ( node2.occupiedBy == NULL && valid == true  ){
                    //cout << "distance : " << node.distance(node2) << endl;
                    node.alentours.push_back(node2);
                }
            }
        }
    }
    return true;
    
}

void HeuristicAI::updateMapNodes(state::State& state){

    int tailleMapX = static_cast<int>(state.map.layout.size());
    int tailleMapY = static_cast<int>(state.map.layout[0].size());

    shared_ptr<state::Personnage> persoOnNode;
    bool valid;

    
    for(auto &node : nodes){
        //erase alentours
        node.alentours.clear();
        node.poids = 0;
        Position posNode{node.getX(),node.getY()};
        node.occupiedBy = NULL;           

        //if someone on a cell = node is occupied
        for(auto& perso : state.getPersonnages()){
            if(perso->getPosition().Compare(posNode)){
                node.occupiedBy = perso;
                for (auto &node2 : nodes){
                    valid = true;
                    valid = node.distance(node2) <= node.occupiedBy->getMOB();

                    //check if in map
                    if (node2.getX() >= tailleMapX || node2.getX() < 0){
                        valid = false;
                    }
                    if (node2.getY() >= tailleMapY || node2.getY() < 0){
                        valid = false;
                    }
                    

                    if ( node2.occupiedBy == NULL && valid == true  ){
                        //cout << "distance : " << node.distance(node2) << endl;
                        node.alentours.push_back(node2);
                    }   
                } 
            }


        }

        /*

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
        }*/
        /*
        for(int i= 0; i< node.alentours.size();i++){
            if (node.alentours[i].getOccupied() == true) node.alentours.erase(node.alentours.begin()+i,node.alentours.begin()+i+1);
        }
        */
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

