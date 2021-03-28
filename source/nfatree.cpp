#include "nfatree.hpp"

using namespace NFA;
using namespace std;

Automaton::TreeNode::TreeNode(int _id, string token):
    id(_id),
    finalToken(token),
    nextStates(vector<TreeTransition*>())
{
    nextStates.reserve(20);
}

Automaton::TreeNode::~TreeNode(){
    
    for(auto it = nextStates.begin(); it != nextStates.end(); it++){
        delete *it;
    }
}

Automaton::TreeTransition::TreeTransition(char _letter):
    letter(_letter),
    next(nullptr)
{

}

Automaton::TreeTransition::~TreeTransition(){
    //delete only if not already null
    if(next != nullptr)
        delete next;
}
