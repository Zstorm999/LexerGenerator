#ifndef _TEST_AUTOMATON_H
#define _TEST_AUTOMATON_H

#include "automaton.hpp"

using namespace DFA;

class TestAutomaton : public Automaton{
public:    
    TestAutomaton():
        Automaton()
    {
        addTransition(0, 1, "i");
        addTransition(1, 2, "f");

        addTransition(0, 1, "f");
        addTransition(1, 3, "o");
        addTransition(3, 4, "r");

        addTransition(0, 5, "a-eg-hj-zA-Z_");
        addTransition(1, 5, "a-eg-np-zA-Z_$0-9");
        addTransition(2, 5, "a-zA-Z_$0-9");
        addTransition(3, 5, "a-qs-zA-Z_$0-9");
        addTransition(4, 5, "a-zA-Z0-9_$");
        addTransition(5, 5, "a-zA-Z0-9_$");

        addFinalState(2, "if");
        addFinalState(4, "for");
        addFinalState(5, "id");
    }
};

#endif //_TEST_AUTOMATON_H