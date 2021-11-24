#include "Sort.h"
#include <iostream>

using namespace std;
namespace state {

Sort::Sort(){}

const std::string& Sort::getNomSort() const{
    return NomSort;
}

void Sort::setNomSort(const std::string& Nom){
    this->NomSort = Nom;
}

const std::string& Sort::getDescription() const{
    return Description;
}

void Sort::setDescription(const std::string& Description){
    this->Description = Description;
}

const std::vector<Effet>& Sort::getEffetSort() const{
    return EffetSort;
}

void Sort::setEffetSort(const std::vector<Effet>& EffetSort){
    this->EffetSort = EffetSort;
}

int Sort::getCout() const{
    return Cout;
}

void Sort::setCout(int Cout){
    this->Cout =Cout;
}

const std::vector<std::array<int,2> >& Sort::getZone() const{
    return Zone;
}

void Sort::setZone(const std::vector<std::array<int,2> >& Zone){
    this->Zone = Zone;
}

int Sort::getDmgPhysique() const{
    return DmgPhysique;
}

void Sort::setDmgPhysique(int DmgPhysique){
    this->DmgPhysique = DmgPhysique;
}

int Sort::getDmgMagique() const{
    return DmgMagique;
}

void Sort::setDmgMagique(int DmgMagique){
    this->DmgMagique = DmgMagique;
}

int Sort::getQtSoin() const{
    return QtSoin;
}

void Sort::setQtSoin(int Soin){
    this->QtSoin = Soin;

}

}

