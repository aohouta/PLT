
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"

#include <string>
#include <vector>

using namespace ::state;
using namespace std;


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestState)
{
    //Test des méthodes de la classe Personnage
    {
        Personnage Attila(Guerrier);
        
        //test constructeur stat guerrier
        vector<int> statsguer = {90,30,30,50,90,90,3,30};
        vector<int> Astats = Attila.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Astats.begin(),Astats.end(),statsguer.begin(),statsguer.end());

        //test setter et getter position
        //array<int,2> moveAttila = {1,1};
        //Attila.setPosition(moveAttila);
        //array<int,2> Aposition = Attila.getPosition();
        //BOOST_CHECK_EQUAL(Aposition[0],1);
       // BOOST_CHECK_EQUAL(Aposition[1],1);
        
        //test setter et getter orientation
        Attila.setOrientation(Face);
        ID_Orientation AttilaOrientation = Attila.getOrientation();
        BOOST_CHECK_EQUAL(AttilaOrientation,Face);

        //test setter et getter effets
        /*vector<Effets> ListeEffets{Etourdissement,Ralentissement,BoostATK,BoostMag,BoostDef,Affaiblissement,Regeneration};
        vector<Effets> ListeEffets{ID_Effet::Etourdissement};
        Attila.setListeEffet(ListeEffets);
        vector<Effets> effetsAttila = Attila.getListeEffet();
        BOOST_CHECK_EQUAL_COLLECTIONS(ListeEffets.begin(),ListeEffets.end(),effetsAttila.begin(),effetsAttila.end());
        */

        //test setter et getter Type
        BOOST_CHECK_EQUAL(Attila.getPType(),Guerrier);
        Attila.setPType(Archer);
        BOOST_CHECK_EQUAL(Attila.getPType(),Archer);
        Attila.setPType(Guerrier);

        //test setter et getter Etat
        BOOST_CHECK_EQUAL(Attila.getEtatPerso(),Alive);
        Attila.setEtatPerso(Dead);
        BOOST_CHECK_EQUAL(Attila.getEtatPerso(),Dead);
        Attila.setEtatPerso(Alive);

        //test setter et getter Nom
        Attila.setNom("Attila le hun");
        BOOST_CHECK_EQUAL(Attila.getNom(),"Attila le hun");

        //test setter et getter NbTour
        Attila.setNbTours(10);
        BOOST_CHECK_EQUAL(Attila.getNbTours(),10);

        //test setter et getter PV
        BOOST_CHECK_EQUAL(Attila.getPV(), 90);
        Attila.setPV(110);
        BOOST_CHECK_EQUAL(Attila.getPV(), 110);

        //test setter et getter ATK
        BOOST_CHECK_EQUAL(Attila.getATK(), 30);
        Attila.setATK(40);
        BOOST_CHECK_EQUAL(Attila.getATK(), 40);

        //test setter et getter MAG
        BOOST_CHECK_EQUAL(Attila.getMAG(), 30);
        Attila.setMAG(20);
        BOOST_CHECK_EQUAL(Attila.getMAG(), 20);

        //test setter et getter RM
        BOOST_CHECK_EQUAL(Attila.getRM(), 50);
        Attila.setRM(60);
        BOOST_CHECK_EQUAL(Attila.getRM(), 60);

        //test setter et getter DEF
        BOOST_CHECK_EQUAL(Attila.getDEF(), 90);
        Attila.setDEF(120);
        BOOST_CHECK_EQUAL(Attila.getDEF(), 120);

        //test setter et getter VIT
        BOOST_CHECK_EQUAL(Attila.getVIT(), 90);
        Attila.setVIT(80);
        BOOST_CHECK_EQUAL(Attila.getVIT(), 80);

        //test setter et getter MOB
        BOOST_CHECK_EQUAL(Attila.getMOB(), 3);
        Attila.setMOB(4);
        BOOST_CHECK_EQUAL(Attila.getMOB(), 4);

        //test setter et getter ESQ
        BOOST_CHECK_EQUAL(Attila.getESQ(), 30);
        Attila.setESQ(25);
        BOOST_CHECK_EQUAL(Attila.getESQ(), 25);

        //test setter et getter Sorts
        
        



        Personnage MagicienDesTenebres{Mage};
        vector<int> statsmag = {50,30,90,90,30,50,5,50};
        vector<int> Mstats = MagicienDesTenebres.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Mstats.begin(),Mstats.end(),statsmag.begin(),statsmag.end());
        
        
        Personnage Legolas{Archer};
        vector<int> statsarcher = {30,90,50,30,50,30,9,90};
        vector<int> Lstats = Legolas.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Lstats.begin(),Lstats.end(),statsarcher.begin(),statsarcher.end());
     
        
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
}

/* vim: set sw=2 sts=2 et : */


