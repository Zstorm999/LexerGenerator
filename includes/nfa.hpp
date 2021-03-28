#ifndef _NFA_H
#define _NFA_H

#include <string>
#include <map>

#include "dfa.hpp"
#include "nfatree.hpp"

namespace NFA{

    class Automaton{
    public:
        Automaton();

        void AddRegex(std::string regex);
        DFA::Automaton MakeDeterministic();
    
    private:
        struct TreeNode;
        struct TreeTransition;

        TreeNode* states; 
    };

}

#endif //_NFA_H