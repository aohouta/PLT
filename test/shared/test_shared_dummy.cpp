
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"

#include <string>
#include <vector>

using namespace ::state;
using namespace std;

/* 
BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestState)
{
    //Test des méthodes de la classe Personnage
    {
        Personnage Attila(Guerrier);
        
        vector<int> statsguer = {90,30,30,50,90,90,3,30};
        vector<int> Astats = Attila.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Astats.begin(),Astats.end(),statsguer.begin(),statsguer.end());
        
        Attila.setPosition(1,1);
        vector<int> Aposition = Attila.getPosition();
        BOOST_CHECK_EQUAL(Aposition[0],1);
        BOOST_CHECK_EQUAL(Aposition[1],1);
        
        
        Personnage MagicienDesTenebres{Mage};
        vector<int> statsmag = {50,30,90,90,30,50,5,50};
        vector<int> Mstats = MagicienDesTenebres.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Mstats.begin(),Mstats.end(),statsmag.begin(),statsmag.end());
        MagicienDesTenebres.setPosition(2,1);
        vector<int> Mposition = MagicienDesTenebres.getPosition();
        BOOST_CHECK_EQUAL(Mposition[0],2);
        BOOST_CHECK_EQUAL(Mposition[1],1);
        
        Personnage Legolas{Archer};
        vector<int> statsarcher = {30,90,50,30,50,30,9,90};
        vector<int> Lstats = Legolas.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Lstats.begin(),Lstats.end(),statsarcher.begin(),statsarcher.end());
        Legolas.setPosition(2,2);
        vector<int> Lposition = Legolas.getPosition();
        BOOST_CHECK_EQUAL(Lposition[0],2);
        BOOST_CHECK_EQUAL(Lposition[1],2);
        
    }
    
    //Test des méthodes de la classe Joueur
    {
        Joueur Abdel("Abdel", Humain);
        Abdel.setGameStatus(AFK);
        BOOST_CHECK_EQUAL(Abdel.getGameStatus(),Joue);
        Abdel.setPlayerType(BotDifficile);
        BOOST_CHECK_EQUAL(Abdel.getPlayerType(),Humain);
    }
  /*{
    Exemple ex {};
    BOOST_CHECK_EQUAL(ex.x, 0);
    ex.setX(21);
    BOOST_CHECK_EQUAL(ex.x, 21);
  }

  {
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }*/
//}

/* vim: set sw=2 sts=2 et : */


