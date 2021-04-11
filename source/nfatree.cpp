#include "nfatree.hpp"

#include <exception>

using namespace NFA;
using namespace std;

Tree::Tree()
{

}

void Tree::addNode(string token){
    nodes.push_back(Node(token));
}

void Tree::addTransition(uint start, uint end){

    if(!valid(start))
        throw TreeException("given start node does not belong to the tree!");

    if(!valid(end))
        throw TreeException("Given end node does not belong to the tree !");
    
    nodes[start].addNext(end);
}

void Tree::addTransition(uint start, uint end, char letter){

    if(!valid(start))
        throw TreeException("given start node does not belong to the tree!");

    if(!valid(end))
        throw TreeException("Given end node does not belong to the tree !");

    nodes[start].addNext(end, letter);
}

Tree::Node& Tree::getNode(uint id){

    if(!valid(id))
        throw TreeException("given node does not belong to the tree!");

    return nodes[id];
}
int Tree::getNextID(){
    return nodes.size();
}


bool Tree::valid(uint node){
    return node < nodes.size();
}

Tree::Node::Node(){

}

Tree::Node::Node(string const& token):
    finalToken(token)
{

}

void Tree::Node::addNext(int next){
    Transition t;
    t.isEpsilon = true;
    t.letter = 0;
    t.nextID = next;

    nextStates.push_back(t);
}

void Tree::Node::addNext(int next, char letter){
    Transition t;
    t.isEpsilon = false;
    t.letter = letter;
    t.nextID = next;

    nextStates.push_back(t);
}

//-------------------------------------------------------------------

map<int, set<int>> Tree::epsilonClosure(){
    map<int, set<int>> m;

    /*for(auto n : nodes){
        set<int> s;
        s.insert(n.first);

        m[n.first] = s;
    }*/

    return m;
}

