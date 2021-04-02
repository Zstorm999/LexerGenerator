#include "nfatree.hpp"

using namespace NFA;
using namespace std;

TreeNode::TreeNode(int _id, string token):
    id(_id),
    finalToken(token),
    nextStates(vector<TreeTransition*>())
{
    nextStates.reserve(20);
}

TreeNode::~TreeNode(){
    
    for(auto it = nextStates.begin(); it != nextStates.end(); it++){
        delete *it;
    }
}

TreeTransition::TreeTransition(char _letter):
    letter(_letter),
    next(nullptr)
{

}

TreeTransition::~TreeTransition(){
    //delete only if not already null
    if(next != nullptr)
        delete next;
}

set<int> NFA::epsilonClosure(TreeNode const& t){
    set<int> s;
    s.insert(t.id);

    return s;
}

