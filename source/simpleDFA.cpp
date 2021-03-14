#include "simpleDFA.hpp"

using namespace DFA;

TransitionFunction::TransitionFunction():
    transition()
{

}

void TransitionFunction::addTransition(int start, int end, char symbol){
    std::pair<int, char> pair(start, symbol);
    transition[pair] = end;
}

int TransitionFunction::operator()(int state, char symbol){
    std::pair<int, char> pair(state, symbol);

    auto pos = transition.find(pair);
    if(pos != transition.end()){
        //found a transition !

        return pos->second;
    }
    
    return -1;
}

Automaton::Automaton():
    move()
{
    move.addTransition(0, 1, 'i');
    move.addTransition(1, 2, 'f');
    move.addTransition(0,1, 'f');
    move.addTransition(1, 3, 'o');
    move.addTransition(3,4, 'r');
}

std::string Automaton::Matches(std::string str){

    int currentState = 0;
    for(auto &c : str){
        currentState = move(currentState, c);

        //a state of -1 means no transition was found
        if(currentState == -1) return "";
    }

    return isFinal(currentState);

}
