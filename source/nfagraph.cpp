#include "nfagraph.hpp"

#include <algorithm>

using namespace NFA;
using namespace std;

Graph::Graph()
{

}

void Graph::addNode(string token){
    nodes.push_back(Node(token));
}

void Graph::addTransition(uint start, uint end){

    if(!valid(start))
        throw TreeException("given start node does not belong to the tree!");

    if(!valid(end))
        throw TreeException("Given end node does not belong to the tree !");
    
    nodes[start].addNext(end);
}

void Graph::addTransition(uint start, uint end, char letter){

    if(!valid(start))
        throw TreeException("given start node does not belong to the tree!");

    if(!valid(end))
        throw TreeException("Given end node does not belong to the tree !");

    nodes[start].addNext(end, letter);
}

Graph::Node& Graph::getNode(uint id){

    if(!valid(id))
        throw TreeException("given node does not belong to the tree!");

    return nodes[id];
}
int Graph::getNextID(){
    return nodes.size();
}

bool Graph::valid(uint node){
    return node < nodes.size();
}

Graph Graph::fuseNewBranch(Graph const& first, Graph const& second){


    if(first.nodes.size() == 0 ) return second;
    if(second.nodes.size() == 0) return first;

    Graph newGraph;
    Graph const* poldGraph;

    //iterating on the second graph will be quicker
    if(first.nodes.size() > second.nodes.size()){
        newGraph = first;
        poldGraph = &second;
    }
    else{
        newGraph = second;
        poldGraph = &first;

    }

    size_t offset = newGraph.nodes.size();

    //append second graph at the end of the first;
    for(size_t i = 0; i < poldGraph->nodes.size(); i++){
        Node n = poldGraph->nodes[i];

        for(auto it = n.nextStates.begin(); it != n.nextStates.end(); it++){
            it->nextID += offset;
        }

        newGraph.nodes.push_back(n);
    }

    //linking the graphs via an epsilon transition
    newGraph.addTransition(0, offset);

    return newGraph;
}

Graph::Node::Node(){

}

Graph::Node::Node(string const& token):
    finalToken(token)
{

}

void Graph::Node::addNext(int next){
    Transition t;
    t.isEpsilon = true;
    t.letter = 0;
    t.nextID = next;

    nextStates.push_back(t);
}

void Graph::Node::addNext(int next, char letter){
    Transition t;
    t.isEpsilon = false;
    t.letter = letter;
    t.nextID = next;

    nextStates.push_back(t);
}

//-------------------------------------------------------------------

map<uint, set<uint>> Graph::epsilonClosure(){
    map<uint, set<uint>> m;
    
    bool stable;
    std::set<uint> done;

    //creating the base map: each closure contains at least its own element and direct epsilon transitions
    for(uint i = 0; i< nodes.size(); i++){
        set<uint> newSet = {i};
        set<uint> trivial = {i};

        //checking for direct epsilon transitions
        for(auto it = nodes[i].nextStates.begin(); it != nodes[i].nextStates.end(); it++){
            if(it->isEpsilon){
                newSet.insert(it->nextID);
            }
        }

        //if element is trivial, its closure is already done
        if(newSet == trivial){
            done.insert(i);
        }

        m.insert(make_pair(i, newSet));

    }

    if(done.size() == nodes.size()){
        //we have a DFA ! no need to go further
        return m;
    }

    

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

