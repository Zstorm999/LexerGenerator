#ifndef _NFA_TREE_H
#define _NFA_TREE_H

#include <vector>
#include <string>
#include <set>
#include <map>
#include <deque>

#include <exception>

namespace NFA{


    class Graph{
    public:
        struct Node;

        Graph();

        void addNode(std::string token="");

        void addTransition(uint start, uint end);
        void addTransition(uint start, uint end, char letter);
        
        //returns the node with corresponding ID
        Node& getNode(uint id);

        //returns the ID that will be attributed to the next node added in the tree
        int getNextID();

        //returns a map containing each node index as a key, and the associated epsilon closure as a value
        std::map<uint, std::set<uint>> epsilonClosure();

    private:

        bool valid(uint node);
        
        std::deque<Node> nodes;
    };

    
    struct Graph::Node{   

        struct Transition{
            bool isEpsilon;

            char letter;
            int nextID;
        };

        Node();
        Node(std::string const& token);

        void addNext(int next);
        void addNext(int next, char letter);

        std::string finalToken;

        std::vector<Transition> nextStates;
    };

    class TreeException : public std::exception{
    public:
        inline TreeException(const std::string& msg):
            message(msg)
        {}

        inline const char* what(){
            return message.c_str();
        } 
    
    private:
        std::string message;

    };

}

#endif //_NFA_TREE_H