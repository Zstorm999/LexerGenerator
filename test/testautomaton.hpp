#ifndef _TEST_AUTOMATON_H
#define _TEST_AUTOMATON_H

#include "dfa.hpp"

using namespace DFA;

class TestAutomaton : public Automaton{
public:    
    inline TestAutomaton():
        Automaton()
    {
        AddTransition(0, 1, "i");
        AddTransition(1, 2, "f");

        AddTransition(0, 1, "f");
        AddTransition(1, 3, "o");
        AddTransition(3, 4, "r");

        AddTransition(0, 5, "a-eg-hj-zA-Z_");
        AddTransition(1, 5, "a-eg-np-zA-Z_$0-9");
        AddTransition(2, 5, "a-zA-Z_$0-9");
        AddTransition(3, 5, "a-qs-zA-Z_$0-9");
        AddTransition(4, 5, "a-zA-Z0-9_$");
        AddTransition(5, 5, "a-zA-Z0-9_$");

        AddFinalState(2, "if");
        AddFinalState(4, "for");
        AddFinalState(5, "id");
    }

    static std::string ExpectedString(){
        return std::string("3\n2 : if\n4 : for\n5 : id\n6\n0 2\n1 : fi\n5 : _A-Za-eg-hj-z\n1 3\n2 : f\n3 : o\n5 : $_0-9A-Za-eg-np-z\n2 1\n5 : $_0-9A-Za-z\n3 2\n4 : r\n5 : $_0-9A-Za-qs-z\n4 1\n5 : $_0-9A-Za-z\n5 1\n5 : $_0-9A-Za-z\n");
    }
};

#endif //_TEST_AUTOMATON_H