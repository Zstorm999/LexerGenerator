#ifndef _SIMPLE_DFA_H
#define _SIMPLE_DFA_H

#include <string>
#include <utility>
#include <map>
#include <iterator>
#include <iostream>

#include "transitions.hpp"

namespace DFA{

    class Automaton{
    public:

        Automaton();

        std::string Matches(std::string str);
    private:
        
        std::string isFinal(int state) {
            if(state == 2) return "if";
            if(state == 4) return "for";
            if(state == 5) return "id";

            return "";
        }

        int* states;
        std::map<int, Transitions> transition;
    };
}

#endif //_SIMPLE_DFA_H