#ifndef _TEST_AUTOMATON_H
#define _TEST_AUTOMATON_H

#include "dfa.hpp"

using namespace DFA;

class TestAutomaton : public Automaton{
public:    
    inline TestAutomaton():
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

    static std::string ExpectedString(){
        return std::string("3\n2 : if\n4 : for\n5 : id\n6\n0 2\n1 : fi\n5 : _A-Za-eg-hj-z\n1 3\n2 : f\n3 : o\n5 : $_0-9A-Za-eg-np-z\n2 1\n5 : $_0-9A-Za-z\n3 2\n4 : r\n5 : $_0-9A-Za-qs-z\n4 1\n5 : $_0-9A-Za-z\n5 1\n5 : $_0-9A-Za-z\n");
    }
};

#endif //_TEST_AUTOMATON_H