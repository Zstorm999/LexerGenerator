#include "simpleDFA.hpp"

using namespace DFA;
using namespace std;

Automaton::Automaton():
    transition(),
    finalStates()
{
    transition[0].AddTransition('i', 1);
    transition[1].AddTransition('f', 2);

    transition[0].AddTransition('f', 1);
    transition[1].AddTransition('o', 3);
    transition[3].AddTransition('r', 4);

    transition[0].AddTransition("a-eg-hj-zA-Z_", 5);
    transition[1].AddTransition("a-eg-np-zA-Z_$0-9", 5);
    transition[2].AddTransition("a-zA-Z_$0-9", 5);
    transition[3].AddTransition("a-qs-zA-Z_$0-9", 5);
    transition[4].AddTransition("a-zA-Z0-9_$", 5);
    transition[5].AddTransition("a-zA-Z0-9_$", 5);


    finalStates[2] = "if";
    finalStates[4] = "for";
    finalStates[5] = "id";
}

string Automaton::Matches(string str) const{

    int currentState = 0;
    for(auto &c : str){
        
        //update current state
        auto p = transition.find(currentState);
        if(p!= transition.end())
            currentState = p->second.Move(c);
        else 
            return "";

        //a state of -1 means no transition was found
        if(currentState == -1) return "";
    }

    return isFinal(currentState);

}

string Automaton::toString() const{
    stringstream ss;

    ss << "Automaton\n\nFinal States\n";

    for(auto i : finalStates){
        ss << i.first << " : \"" << i.second << "\"\n";
    }
    
    return ss.str();
}
