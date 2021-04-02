#ifndef _NFA_TREE_H
#define _NFA_TREE_H

#include <vector>
#include <string>
#include <set>

namespace NFA{

    //forward declaration
    struct TreeTransition;
    
    struct TreeNode{   
        TreeNode(int _id, std::string token="");
        ~TreeNode();

        int id; //needed ?
        std::string finalToken;

        std::vector<TreeTransition*> nextStates;
    };

    struct TreeTransition{
        TreeTransition(char letter = -1);
        ~TreeTransition();

        TreeNode* next;
        char letter;
    };


    std::set<int> epsilonClosure(TreeNode const& n);

}

#endif //_NFA_TREE_H