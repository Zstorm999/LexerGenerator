#ifndef _SIMPLE_DFA_H
#define _SIMPLE_DFA_H

#include <string>
#include <iostream>

#include "dfatransition.hpp"


namespace DFA{

    class Automaton{
    public:

        Automaton();

        std::string toString() const;
        std::istream& operator>>(std::istream& is);

        std::string Matches(std::string const& str) const;

        inline void AddFinalState(int state, std::string token){
            finalStates[state] = token;
        }

        inline void AddTransition(int start, int end, std::string pattern){
            transition[start].AddTransition(pattern, end);
        }


    private:
        

        std::map<int, std::string> finalStates;
        std::map<int, Transitions> transition;

        inline std::string isFinal(int state) const{
            
            auto p = finalStates.find(state);
            if( p != finalStates.end()){
                return p->second;
            }
            return "";
        }

    };

    inline std::ostream& operator<<(std::ostream& os, Automaton const& a){ 
        os << a.toString();
        return os;
    }

    inline std::istream& operator>>(std::istream& is, Automaton& a){
        return a.operator>>(is);
    }

}

#endif //_SIMPLE_DFA_H