#include "automaton.hpp"

using namespace DFA;
using namespace std;

Automaton::Automaton():
    transition(),
    finalStates()
{
}


string Automaton::toString() const{
    ostringstream ss;

    ss << finalStates.size() << "\n";

    for(auto i : finalStates){
        ss << i.first << " : " << i.second << "\n";
    }

    ss << transition.size() << "\n";

    for(auto p : transition){
        ss <<  p.first << " " << p.second;
    }
    
    return ss.str();
}

istream& Automaton::operator>>(istream& is){
    
    string tmp;
    int nb;
    is >> nb;

    for(int i(0); i<nb; i++){
        int state;
        string token;
        is >> state >> tmp >> token;

        addFinalState(state, token);
    }

    is >> nb;
    for(int i(0); i<nb; i++){
        
        int start, end, nbTrans;
        string pattern;
        is >> start >> nbTrans;
        
        for(int j(0); j<nbTrans; j++){
            is >> end >> tmp >> pattern;
            addTransition(start, end, pattern);
        }
    }

    return is;
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


