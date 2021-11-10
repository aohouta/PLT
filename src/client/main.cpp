#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "Affichage.cpp"

#include "../shared/state.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
    string hi = "hello";
    string stat = "state";
    string rend = "render";
    std::vector<int> temp;

    Personnage perso(Archer);
    temp = perso.getStats();

    if(argc >= 2){
        if(argv[1] == hi){
            cout << "Bonjour le monde !" << endl;
        }
        else if(argv[1] == stat){
            cout << "go faire make test" << endl;
        }
        else if(argv[1] == rend){
            afficheState();
        }
    }
    cout << temp[1];
    return 0;
}
