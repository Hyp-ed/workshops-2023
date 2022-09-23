#include "state_machine/state.hpp"

namespace hyped::state_machine 
{
    int main() 
    {
        data::Data &data     = data::Data::getInstance();
        State *current_state = Idle::getInstance();

        current_state->enter(); 
        State *new_state;  

        while(new_state = current_state->checkTransition()) 
        {
            current_state->exit(); 
            current_state = new_state; 
            current_state->enter(); 
        }

        return 0; 

    }

}

