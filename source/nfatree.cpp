#include "nfatree.hpp"

#include <algorithm>

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

map<uint, set<uint>> Tree::epsilonClosure(){
    map<uint, set<uint>> m;
    
    bool stable;

    //creating the base map: each closure contains at least its own element
    for(uint i = 0; i< nodes.size(); i++){
        set<uint> newSet = {i};

        set<uint> epsilonNext;

        for(auto it = nodes[i].nextStates.begin(); it != nodes[i].nextStates.end(); it++){
            if(it->isEpsilon){
                newSet.insert(it->nextID);
            }
        }

        m.insert(make_pair(i, newSet));

    }

    std::set<uint> done;

    do{

        stable = true;
        for(auto i = m.begin(); i != m.end(); i++){
            
            //no need to check already stable nodes
            if(done.find(i->first) != done.end()) continue;

            set<uint> newClosure = i->second;

            for(auto j = i->second.begin(); j != i->second.end(); j++){

                newClosure.insert(m[*j].begin(), m[*j].end());
            }
            

            if(newClosure != i->second){
                stable =  false;
                m[i->first] = newClosure;
            }
            else{
                done.insert(i->first);
            }

        }

    }while(!stable);

    return m;
}

