#include <iostream>

#include <fstream>
#include <string.h>
#include <sstream>
#include <map>
#include <memory>
#include <unistd.h>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>



#include "../shared/state.h"
#include "../shared/engine.h"
#include "../shared/ai.h"

using namespace std;
using namespace state;
using namespace render;
using namespace engine;

int main(int argc,char* argv[])
{
    


    if(argc >= 2){
        
       
        
        if (strcmp(argv[1], "record") == 0){

            cout << "--- Record Battle Random AI vs HeuristicAI ---" << endl;
            State state{"render"};
            engine::Engine ngine(state);
            state.map.initMap();

            //team 1
            cout << "Team 1 will be random AI" << endl;
            state.initPersonnage(Mage,1,11,1);
            state.initPersonnage(Archer,1,12,1);
            state.initPersonnage(Guerrier,1,13,1);
            //team 2
            cout << "Team 2 will be HeuristicAI" << endl;
            state.initPersonnage(Mage,19,11,2);
            state.initPersonnage(Archer,19,12,2);
            state.initPersonnage(Guerrier,19,13,2);
            
            
            ai::RandomAI rai;
            ai::HeuristicAI hai;
            hai.initMapNode(state);

            state.SaveInitSate();
            ngine.Start();


            while (ngine.IsGameOver(state) == false){
                sleep(3);
                while(state.activePlayer == nullptr){;}
                if(state.activePlayer->getID_Invocateur()==1){
                    cout << "- Random AI-"<< endl;
                    rai.run(state);
                }
                else{
                    cout << "-Heuristic AI-"<< endl;
                    hai.run(ngine,state);
                }

            

                
                ngine.EndTurn();
                
                
            }
            state.gameOver = true;
            ngine.Stop();

        }
        
            
        
    }

    return 0;
}