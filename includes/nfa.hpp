#ifndef _NFA_H
#define _NFA_H

#include <string>
#include <map>

#include "dfa.hpp"
#include "nfagraph.hpp"

namespace NFA{

    class Automaton{
    public:
        Automaton();

        Graph getStates();

        void AddRegex(std::string regex);
        DFA::Automaton MakeDeterministic();
    
    private:

        NFA::Graph graph; 
    };

}

#endif //_NFA_H