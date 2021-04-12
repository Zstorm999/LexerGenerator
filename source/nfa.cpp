#include "nfa.hpp"

using namespace NFA;
using namespace std;

Automaton::Automaton():
    graph()
{

}

Graph Automaton::getStates(){
    return graph;
}

void Automaton::AddRegex(string regex){

}

DFA::Automaton Automaton::MakeDeterministic(){
    DFA::Automaton deterministic;

    return deterministic;
}
