
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
    //Test method of class "Personnage"
    /*{
        Personnage Attila("Attila le guerrier",Guerrier);
        
        //constructor test via method getStats
        //{PV,PVmax ,Mana, ManaMax, ATK, MAG, RM, DEF, VIT, MOB, ESQ}
        vector<int> statsguer = {90,90,0,50,30,30,50,90,90,3,30};
        vector<int> Astats = Attila.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Astats.begin(),Astats.end(),statsguer.begin(),statsguer.end());        

        
        //setter and getter Orientation 
        Attila.setOrientation(Face);
        ID_Orientation AttilaOrientation = Attila.getOrientation();
        BOOST_CHECK_EQUAL(AttilaOrientation,Face);

        //setter and getter seEffet
        Effet slow(Ralentissement);
        Effet stun(Etourdissement);
        vector<Effet> effetAttila = {slow, stun};
        Attila.setListeEffet(effetAttila);
        vector<Effet> testEffetAttila = Attila.getListeEffet();

        BOOST_CHECK_EQUAL(effetAttila[0].getType_Effet(),Ralentissement);
        BOOST_CHECK_EQUAL(effetAttila[1].getType_Effet(),Etourdissement);

        //setter and getter Position

        BOOST_CHECK_EQUAL(Attila.getPosition().getX(),0);
        BOOST_CHECK_EQUAL(Attila.getPosition().getY(),0);

        Attila.setPosition({10,20});
        BOOST_CHECK_EQUAL(Attila.getPosition().getX(),10);
        BOOST_CHECK_EQUAL(Attila.getPosition().getY(),20);        

        //setter and getter Type
        BOOST_CHECK_EQUAL(Attila.getPType(),Guerrier);
        Attila.setPType(Archer);
        BOOST_CHECK_EQUAL(Attila.getPType(),Archer);
        Attila.setPType(Guerrier);

        //setter and getter Etat
        Attila.setEtatPerso(Attente);
        BOOST_CHECK_EQUAL(Attila.getEtatPerso(),Attente);
        Attila.setEtatPerso(Mort);
        BOOST_CHECK_EQUAL(Attila.getEtatPerso(),Mort);
        Attila.setEtatPerso(Attente);

        //setter and getter Action
        Attila.setAction(IDLE);
        BOOST_CHECK_EQUAL(Attila.getAction(),IDLE);     


        //setter and getter Nom
        Attila.setNom("Attila le hun");
        BOOST_CHECK_EQUAL(Attila.getNom(),"Attila le hun");

        //setter and getter NbTour
        Attila.setNbTours(10);
        BOOST_CHECK_EQUAL(Attila.getNbTours(),10);

        //setter and getter PVmax
        BOOST_CHECK_EQUAL(Attila.getPVmax(), 90);
        Attila.setPVmax(110);
        BOOST_CHECK_EQUAL(Attila.getPVmax(), 110);

        //setter and getter PV
        BOOST_CHECK_EQUAL(Attila.getPV(), 90);
        Attila.setPV(110);
        BOOST_CHECK_EQUAL(Attila.getPV(), 110); 
        Attila.setPV(999);
        BOOST_CHECK_EQUAL(Attila.getPV(), Attila.getPVmax());    

        //setter and getter ATK
        BOOST_CHECK_EQUAL(Attila.getATK(), 30);
        Attila.setATK(-40);
        BOOST_CHECK_EQUAL(Attila.getATK(), 0);
        Attila.setATK(40);
        BOOST_CHECK_EQUAL(Attila.getATK(), 40);

        //setter and getter MAG
        BOOST_CHECK_EQUAL(Attila.getMAG(), 30);
        Attila.setMAG(20);
        BOOST_CHECK_EQUAL(Attila.getMAG(), 20);

        //setter and getter RM
        BOOST_CHECK_EQUAL(Attila.getRM(), 50);
        Attila.setRM(60);
        BOOST_CHECK_EQUAL(Attila.getRM(), 60);

        //setter and getter DEF
        BOOST_CHECK_EQUAL(Attila.getDEF(), 90);
        Attila.setDEF(120);
        BOOST_CHECK_EQUAL(Attila.getDEF(), 120);

        //setter and getter VIT
        BOOST_CHECK_EQUAL(Attila.getVIT(), 90);
        Attila.setVIT(80);
        BOOST_CHECK_EQUAL(Attila.getVIT(), 80);

        //setter and getter MOB
        BOOST_CHECK_EQUAL(Attila.getMOB(), 3);
        Attila.setMOB(4);
        BOOST_CHECK_EQUAL(Attila.getMOB(), 4);

        //setter and getter ESQ
        BOOST_CHECK_EQUAL(Attila.getESQ(), 30);
        Attila.setESQ(25);
        BOOST_CHECK_EQUAL(Attila.getESQ(), 25);

        //setter and getter ManaMax
        Attila.setManaMax(60);
        BOOST_CHECK_EQUAL(Attila.getManaMax(),60);
        Attila.setManaMax(50);

        //setter and getter Mana
        Attila.setMana(30);
        BOOST_CHECK_EQUAL(Attila.getMana(),30);
        Attila.setMana(999);
        BOOST_CHECK_EQUAL(Attila.getMana(),Attila.getManaMax());
        Attila.setMana(0);


        //setter and getter ListeSort
        Sort sortA, sortB;
        sortA.setNomSort("Foudre DE LA MORT QUI TUE");
        sortB.setNomSort("Sans une bosse !");
        vector<Sort> listeSortAttila{sortA,sortB};
        Attila.setListeSort(listeSortAttila);
        vector<Sort> sortAttila = Attila.getListeSort();
        BOOST_CHECK_EQUAL(Attila.getListeSort()[0].getNomSort(),"Foudre DE LA MORT QUI TUE");
        BOOST_CHECK_EQUAL(Attila.getListeSort()[1].getNomSort(),"Sans une bosse !");
        

    
        //other test
        Personnage MagicienDesTenebres{"Dark Mage of Eternal Doom",Mage};
        vector<int> statsmag = {50,50,0,100,30,90,90,30,50,5,50};
        vector<int> Mstats = MagicienDesTenebres.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Mstats.begin(),Mstats.end(),statsmag.begin(),statsmag.end());
        
        
        Personnage Legolas{"Legolas Vertefeuille",Archer};
        vector<int> statsarcher = {30,30,0,70,90,50,30,50,30,9,90};
        vector<int> Lstats = Legolas.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Lstats.begin(),Lstats.end(),statsarcher.begin(),statsarcher.end());
     
        
    }
    //Test method of class "Effet"
    {
        int lowestEffectLevel = 0;
        int lowestEffectDuration = 1;
        //constructor
        Effet slow(Ralentissement);
        BOOST_CHECK_EQUAL(slow.getType_Effet(),Ralentissement);
        BOOST_CHECK_EQUAL(slow.getNiveauEffet(),0);
        BOOST_CHECK_EQUAL(slow.getEffetDuree(),1);

        //setter NiveauEffet
        slow.setNiveauEffet(2);
        BOOST_CHECK_EQUAL(slow.getNiveauEffet(),2);
        slow.setNiveauEffet(-2);
        BOOST_CHECK_EQUAL(slow.getNiveauEffet(),lowestEffectLevel);

        //setter EffetDuree
        slow.setEffetDuree(2);
        BOOST_CHECK_EQUAL(slow.getEffetDuree(),2);
        slow.setEffetDuree(-2);
        BOOST_CHECK_EQUAL(slow.getEffetDuree(),lowestEffectDuration);

        //setter Type_Effet
        slow.setType_Effet(Regeneration);
        BOOST_CHECK_EQUAL(slow.getType_Effet(),Regeneration);


        
    }
    //Test method of class "Sort"
    { 
      //constructor
      Effet slow(Ralentissement);
      Effet heal(Regeneration);
      Sort sortA;

      //setter and getter Nom
      sortA.setNomSort("Soin euphorique");
      BOOST_CHECK_EQUAL(sortA.getNomSort(),"Soin euphorique");

      //setter and getter Description
      sortA.setDescription("Soigne tellement la cible qu'elle en devient euphorique, ralentie 50%");
      BOOST_CHECK_EQUAL(sortA.getDescription(),"Soigne tellement la cible qu'elle en devient euphorique, ralentie 50%");

      //setter and getter Effet
      vector<Effet> effetsSortA = {slow,heal};
      sortA.setEffetSort(effetsSortA);
      vector<Effet> testEffetSortA = sortA.getEffetSort();
      BOOST_CHECK_EQUAL(testEffetSortA[0].getType_Effet(),Ralentissement);
      BOOST_CHECK_EQUAL(testEffetSortA[1].getType_Effet(),Regeneration);
      
      //setter and getter Cout
      sortA.setCout(10);
      BOOST_CHECK_EQUAL(sortA.getCout(),10);

      //setter and getter Range
      sortA.setRange(5);
      BOOST_CHECK_EQUAL(sortA.getRange(),5);
      

      //setter and getter Zone


      //setter and getter DmgPhysique
      sortA.setDmgPhysique(100);
      BOOST_CHECK_EQUAL(sortA.getDmgPhysique(),100);

      //setter and getter DmgMagique
      sortA.setDmgMagique(50);
      BOOST_CHECK_EQUAL(sortA.getDmgMagique(),50);

      //setter and getter QtSoin
      sortA.setQtSoin(9999);
      BOOST_CHECK_EQUAL(sortA.getQtSoin(),9999);


    }

    //Test method of class "Position"
    {
      //constructor
      Position pos;
      Position posB(5,10);
      BOOST_CHECK_EQUAL(pos.getX(),0);
      BOOST_CHECK_EQUAL(pos.getY(),0);
      BOOST_CHECK_EQUAL(posB.getX(),5);
      BOOST_CHECK_EQUAL(posB.getY(),10);




       
    }

    //Test method of class "Joueur"
    {
      //constructor
      Joueur joueur1("Papapc",Humain);
      BOOST_CHECK_EQUAL(joueur1.getNomJoueur(),"Papapc");
      BOOST_CHECK_EQUAL(joueur1.getPlayerType(),Humain);

      //setter Nom
      joueur1.setNomJoueur("BOT OF DOOM");
      BOOST_CHECK_EQUAL(joueur1.getNomJoueur(),"BOT OF DOOM");

      //setter  PlayerType
      joueur1.setPlayerType(BotDifficile);
      BOOST_CHECK_EQUAL(joueur1.getPlayerType(),BotDifficile);

      //getter and setter GameStatus
      joueur1.setGameStatus(Joue);
      BOOST_CHECK_EQUAL(joueur1.getGameStatus(),Joue);

      //getter and setter Personnages
      Personnage persoA("Dark Mage of Eternal Doom",Mage);
      Personnage persoB("Attila le guerrier",Guerrier);
      vector<Personnage> listePersonnage = {persoA,persoB};
      joueur1.setPersonnages(listePersonnage);
      BOOST_CHECK_EQUAL(joueur1.getPersonnages()[0].getNom(),"Dark Mage of Eternal Doom");
      BOOST_CHECK_EQUAL(joueur1.getPersonnages()[1].getNom(),"Attila le guerrier");




    }

    //Test method of class "State"
    {
       
    }

    //Test method of class "Map"
    {
       
    }

    //Test method of class "Cell"
    {
       
    }
    */
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


