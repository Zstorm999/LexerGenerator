#include "transitions.hpp"

using namespace DFA;
using namespace std;

Transitions::Transitions():
    letterTransition()
{

}

void Transitions::AddTransition(char letter, int finalState){
    letterTransition[letter] = finalState;
}

int Transitions::operator()(char letter){

    auto pos = letterTransition.find(letter);
    if(pos != letterTransition.end()){
        return pos->second;
    }

    return -1;
}
