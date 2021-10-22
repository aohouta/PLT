#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

//void testc();

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);
    string hi = "hello";
    string stat = "state";

    //testc();

    if(argv[1] == hi){
        cout << "Bonjour le monde !" << endl;
    }
    else if(argv[1] == stat){
        cout << "Pas encore de test :/" << endl;
    }
    cout << "test\n";
    return 0;
}
