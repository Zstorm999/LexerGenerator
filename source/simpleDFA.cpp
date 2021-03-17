#include "simpleDFA.hpp"

using namespace DFA;

Automaton::Automaton():
    transition()
{
    transition[0].AddTransition('i', 1);
    transition[1].AddTransition('f', 2);

    transition[0].AddTransition('f', 1);
    transition[1].AddTransition('o', 3);
    transition[3].AddTransition('r', 4);

    transition[0].AddTransition("a-eg-hj-zA-Z_", 5);
    transition[1].AddTransition("a-eg-np-zA-Z_$0-9", 5);
    transition[3].AddTransition("a-qs-zA-Z_$0-9", 5);
    transition[5].AddTransition("a-zA-Z0-9_$", 5);
}

std::string Automaton::Matches(std::string str){

    int currentState = 0;
    for(auto &c : str){
        
        //update current state
        currentState = transition[currentState].Move(c);

        //a state of -1 means no transition was found
        if(currentState == -1) return "";
    }

    return isFinal(currentState);

}
