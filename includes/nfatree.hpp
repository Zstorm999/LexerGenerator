#ifndef _NFA_TREE_H
#define _NFA_TREE_H

#include <vector>
#include <string>


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

}

#endif //_NFA_TREE_H