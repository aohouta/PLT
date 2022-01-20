
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"

#include <string>
#include <vector>




using namespace ::state;
using namespace ::engine;
using namespace std;


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestState)
{
    //Test method of class "Personnage"
    {
        Personnage Attila("Attila le guerrier",Guerrier,1);
        
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

        //getTotal

          //buff ATK

        Effet Buff1(BoostAtk, 1, 5);
        effetAttila.push_back(Buff1);
        Attila.setListeEffet(effetAttila);

        BOOST_CHECK_EQUAL(Attila.getTotalAttack(), 45);

        Effet Buff2(BoostAtk, 1, 1);
        effetAttila.push_back(Buff2);
        Attila.setListeEffet(effetAttila);

        BOOST_CHECK_EQUAL(Attila.getTotalAttack(), 45);

        Effet Buff3(BoostAtk, 1, 10);
        effetAttila.push_back(Buff3);
        Attila.setListeEffet(effetAttila);

        BOOST_CHECK_EQUAL(Attila.getTotalAttack(), 60);

         //Buff Def

        Effet BuffD1(BoostDef, 1, 5);
        effetAttila.push_back(BuffD1);
        Attila.setListeEffet(effetAttila);

        BOOST_CHECK_EQUAL(Attila.getTotalDef(), 135);

        Effet BuffD2(BoostDef, 1, 1);
        effetAttila.push_back(BuffD2);
        Attila.setListeEffet(effetAttila);

        BOOST_CHECK_EQUAL(Attila.getTotalDef(), 135);

        Effet BuffD3(BoostDef, 1, 10);
        effetAttila.push_back(BuffD3);
        Attila.setListeEffet(effetAttila);
        BOOST_CHECK_EQUAL(Attila.getTotalDef(), 180);

          //debuff

        
        Effet Debuff1(Affaiblissement, 1, 5);
        effetAttila.push_back(Debuff1);
        Attila.setListeEffet(effetAttila);

        BOOST_CHECK_EQUAL(Attila.getTotalAttack(), 45);
        BOOST_CHECK_EQUAL(Attila.getTotalDef(), 135);

        Effet Debuff2(Affaiblissement, 1, 1);
        effetAttila.push_back(Debuff2);
        Attila.setListeEffet(effetAttila);

        BOOST_CHECK_EQUAL(Attila.getTotalAttack(), 45);
        BOOST_CHECK_EQUAL(Attila.getTotalDef(), 135);

        Effet Debuff3(Affaiblissement, 1, 10);
        effetAttila.push_back(Debuff3);
        Attila.setListeEffet(effetAttila);

        BOOST_CHECK_EQUAL(Attila.getTotalAttack(), 30);
        BOOST_CHECK_EQUAL(Attila.getTotalDef(), 90);


         

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
        Personnage MagicienDesTenebres{"Dark Mage of Eternal Doom",Mage,1};
        vector<int> statsmag = {50,50,0,100,30,90,90,30,50,5,50};
        vector<int> Mstats = MagicienDesTenebres.getStats();
        BOOST_CHECK_EQUAL_COLLECTIONS(Mstats.begin(),Mstats.end(),statsmag.begin(),statsmag.end());
        
        
        Personnage Legolas{"Legolas Vertefeuille",Archer,1};
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

      BOOST_CHECK_EQUAL(posB.Compare(pos),false);
      Position posC(5,10);
      BOOST_CHECK_EQUAL(posB.Compare(posC),true);
      




       
    }

    //Test method of class "Joueur"
    {
      //constructor
      Joueur joueur1("Papapc",Humain,1);
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
      Personnage persoA("Dark Mage of Eternal Doom",Mage,1);
      Personnage persoB("Attila le guerrier",Guerrier,2);
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


BOOST_AUTO_TEST_CASE(TestEngine)
{ 

  State TestState{"state de test"};
  Engine TestEngine(TestState);

  //init a 20 by 25 map
  for (int i = 0; i < 20; ++i)
    {
        std::vector<std::shared_ptr<Cell>> newline;
        for (int j = 0; j < 25; ++j)
        {
            
               
          std::shared_ptr<Cell> spc(new Cell(GROUND, i, j, i+j));
          newline.push_back(move(spc));
        }

         TestState.map.layout.push_back(move(newline));
    }

  //guerrier 
  TestState.initPersonnage(Guerrier,1,1,1);
  TestState.initPersonnage(Guerrier,1,2,1);
  TestState.initPersonnage(Guerrier,2,1,1);
  TestState.initPersonnage(Guerrier,1,0,1); 

  //set guerrier as active player
  TestState.activePlayer = TestState.getPersonnages()[0];

  {
    //Test method of ActionCommand

    ActionCommand ac;
    float orientation;
    shared_ptr<state::Personnage> perso;
    //face to face
    perso = TestState.getPersonnages()[1];
    orientation = ac.OrientationMult(TestState.activePlayer,perso);
    BOOST_CHECK_EQUAL(1,orientation);
    //face to side
    perso = TestState.getPersonnages()[2];
    orientation = ac.OrientationMult(TestState.activePlayer,perso);
    BOOST_CHECK_EQUAL(1.5,orientation);
    //face to back
    perso = TestState.getPersonnages()[3];
    orientation = ac.OrientationMult(TestState.activePlayer,perso);
    BOOST_CHECK_EQUAL(2,orientation);
  }

  {
    //Test method of AttackCommand
    cout << "---------------- Test AttackCommand -------------- \n";
  
    
    
    //target cell is 1,2
    shared_ptr<state::Cell> targetCell;

    targetCell = TestState.map.layout[1][2];

    //attack command
    AttackCommand atk(*targetCell);
    atk.setCaster(TestState.activePlayer);

    bool testRange = atk.InRange(*targetCell);
    BOOST_CHECK_EQUAL(true,testRange);

    //target cell is 2,2, you need range >=2 to by in range
    targetCell = TestState.map.layout[2][2];
    atk.setTargetCell(*targetCell);
    testRange = atk.InRange(*targetCell);

    BOOST_CHECK_EQUAL(false,testRange);


    //Guerrier in 1,1 try to attack position 2,2
    cout << "Guerrier en 1,1 attaque la postition 2,2 \n";
    int testExecute = atk.Execute(TestState); // = 1 because he can't
    BOOST_CHECK_EQUAL(1,testExecute);

    //Guerrier in 1,1 try to attack position 1,2
    cout << "Guerrier en 1,1 attaque la postition 0,1 \n";
    atk.setTargetCell(*TestState.map.layout[0][1]);
    testExecute = atk.Execute(TestState); // = 0 because he can, but no other player here
    BOOST_CHECK_EQUAL(0,testExecute);
    //Guerrier in 1,1 try to attack another guerrier in 1,2
    cout << "Un nouveau guerrier arrive en 1,2, il se font face \n";
    cout << "Guerrier en 1,1 attaque la guerrier en 1,2 \n";
       
    testExecute = atk.Execute(TestState);
    BOOST_CHECK_EQUAL(0,testExecute);

    //Guerrier in 1,1 try to attack another guerrier in 2,1
    cout << "Un nouveau guerrier arrive en 2,1, il se présente de côté \n";
    cout << "Guerrier en 1,1 attaque la guerrier en 2,1 \n";    
    atk.setTargetCell(*TestState.map.layout[2][1]);  
    testExecute = atk.Execute(TestState);
    BOOST_CHECK_EQUAL(0,testExecute);

    //Guerrier in 1,1 try to attack another guerrier in 1,0
    cout << "Un nouveau guerrier arrive en 1,0, il se présente de dos \n";
    cout << "Guerrier en 1,1 attaque la guerrier en 1,0 \n";   
    atk.setTargetCell(*TestState.map.layout[1][0]);  
    testExecute = atk.Execute(TestState);
    BOOST_CHECK_EQUAL(0,testExecute);
  }

  {
    //Test method of MoveCommand
    cout << "---------------- MoveCommand -------------- \n";
    shared_ptr<state::Cell> targetCell = TestState.map.layout[0][1];
    MoveCommand mov(*targetCell);

    shared_ptr<state::Personnage> perso = TestState.activePlayer;
    // Mov from 1,1 to 0,1 =>Distance = 1
    cout << "Guerrier start from X:1 Y:1 \n";
    int testMov = mov.Execute(TestState);
    BOOST_CHECK_EQUAL(1,testMov);
    BOOST_CHECK_EQUAL(0,perso->getPosition().getX());
    BOOST_CHECK_EQUAL(1,perso->getPosition().getY());

    // Mov from 0,1 to 10,10 =>Distance = 19 > range guerrier =3
    targetCell = TestState.map.layout[10][10];
    mov.TargetCell = *targetCell;
    cout << "Guerrier start from X:0 Y:1 \n";
    testMov = mov.Execute(TestState);
    BOOST_CHECK_EQUAL(0,testMov);
    BOOST_CHECK_EQUAL(0,perso->getPosition().getX());
    BOOST_CHECK_EQUAL(1,perso->getPosition().getY());

    // Mov from 0,1 to 2,1 =>Distance = 2 but someone already here
    targetCell = TestState.map.layout[2][1];
    mov.TargetCell = *targetCell;
    cout << "Guerrier start from X:0 Y:1 \n";
    testMov = mov.Execute(TestState);
    BOOST_CHECK_EQUAL(0,testMov);
    BOOST_CHECK_EQUAL(0,perso->getPosition().getX());
    BOOST_CHECK_EQUAL(1,perso->getPosition().getY());




    



  }






  
}

