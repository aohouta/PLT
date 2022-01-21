#include "SaveState.h"

using namespace std;

namespace state
{
    SaveState::SaveState (state::State state){
        savedState = state;
    }

    state::State SaveState::LoadState(){
        return savedState;
    }
}