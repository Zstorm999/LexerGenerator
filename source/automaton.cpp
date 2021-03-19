#include "automaton.hpp"

using namespace DFA;
using namespace std;

Automaton::Automaton():
    transition(),
    finalStates()
{
    
}

string Automaton::Matches(string const& str) const{

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

    ss << "Transitions\n\n";

    for(auto p : transition){
        ss << "From " << p.first << " : \n";
        ss << p.second << "\n";
    }
    
    return ss.str();
}
