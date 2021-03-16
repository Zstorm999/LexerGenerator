#include "simpleDFA.hpp"

using namespace DFA;

Automaton::Automaton():
    move()
{
    move[0].AddTransition('i', 1);
    move[1].AddTransition('f', 2);

    move[0].AddTransition('f', 1);
    move[1].AddTransition('o', 3);
    move[3].AddTransition('r', 4);
}

std::string Automaton::Matches(std::string str){

    int currentState = 0;
    for(auto &c : str){
        currentState = move[currentState](c);

        //a state of -1 means no transition was found
        if(currentState == -1) return "";
    }

    return isFinal(currentState);

}
