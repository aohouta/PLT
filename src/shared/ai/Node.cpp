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

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;


Node::Node(int x,int y,int id, bool occupied, int poids){
    this->x = x;
    this->y = y;
    this->id = id;
    this->occupied = occupied;
    this->poids = poids;
}

int Node::getX() const{
    return x;
}

void Node::setX(int x){
    this->x = x;
}

int Node::getY() const{
    return y;
}

void Node::setY(int y){
    this->y = y;
}

bool Node::getOccupied() const{
    return occupied;
}

void Node::setOccupied(bool occupied){
    this->occupied=occupied;
}

int Node::getId() const{
    return id;
}
void Node::setId(int id){
    this->id = id;
}

int Node::getPoids() const{
    return poids;
}
void Node::setPoids(int poids){
    this->poids = poids;
}
int Node::distance(Node& other){
    return abs(this->x - other.getX()) + abs(this->y - other.getY());
}

