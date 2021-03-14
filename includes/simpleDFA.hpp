#ifndef _SIMPLE_DFA_H
#define _SIMPLE_DFA_H

#include <string>
#include <utility>
#include <map>
#include <iterator>
#include <iostream>

namespace DFA{

    class TransitionFunction{
    public:

        TransitionFunction();

        void addTransition(int start, int end, char symbol);

        int operator ()(int startState, char symbol);

    //private:    
        std::map<std::pair<int, char>, int> transition;

    };


    class Automaton{
    public:

        Automaton();

        std::string Matches(std::string str);

        void showMap(){
            for(auto i : move.transition){
                std::cout << "(" << i.first.first << ", " <<  i.first.second << "), " << i.second << "\n";
            }
        }

    private:
        
        std::string isFinal(int state) {
            if(state == 2) return "if";
            if(state == 4) return "for";

            return "";
        }

        int* states;
        TransitionFunction move;
    };
}

#endif //_SIMPLE_DFA_H