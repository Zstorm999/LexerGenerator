#ifndef _NFA_TREE_H
#define _NFA_TREE_H

#include <vector>
#include <string>

#include "nfa.hpp"

namespace NFA{
    
    struct Automaton::TreeNode{   
        TreeNode(int _id, std::string token="");
        ~TreeNode();

        int id; //needed ?
        std::string finalToken;

        std::vector<TreeTransition*> nextStates;
    };

    struct Automaton::TreeTransition{
        TreeTransition(char letter = -1);
        ~TreeTransition();

        TreeNode* next;
        char letter;
    };

}

#endif //_NFA_TREE_H