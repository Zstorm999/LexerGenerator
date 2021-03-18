#ifndef _SIMPLE_DFA_H
#define _SIMPLE_DFA_H

#include <string>
#include <map>
#include <sstream>
#include <iostream>


#include "transitions.hpp"

namespace DFA{

    class Automaton{
    public:

        Automaton();

        std::string Matches(std::string str) const;

        std::string toString() const;

    private:
        
        inline std::string isFinal(int state) const{
            
            auto p = finalStates.find(state);
            if( p != finalStates.end()){
                return p->second;
            }
            return "";
        }

        std::map<int, std::string> finalStates;
        std::map<int, Transitions> transition;
    };

    inline std::ostream& operator<<(std::ostream& os, Automaton const& a){ 
        os << a.toString();
        return os;
    }

}

#endif //_SIMPLE_DFA_H