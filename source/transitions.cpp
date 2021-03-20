#include "transitions.hpp"

using namespace DFA;
using namespace std;

Transitions::Transitions():
    letterTransition(),
    intervalTransition()
{
    
}

string Transitions::toString() const{
    stringstream ss;

    map<int, string> trans;

    for(auto p : letterTransition){
        trans[p.second] += p.first; 
    }

    for(auto p: intervalTransition){
        trans[p.second] += p.first.ToString();
    }

    ss << trans.size() << "\n";
    for(auto p : trans){
        ss << p.first << " : " << p.second <<"\n";
    }

    return ss.str();
}

void Transitions::AddTransition(char letter, int finalState){
    letterTransition[letter] = finalState;  
}

void Transitions::AddTransition(string pattern, int finalState){

    if(pattern.length() == 1){
        AddTransition(pattern[0], finalState);
        return;
    }

    char prev = -1;
    char secondPrev = -1;

    bool isFirst = true;

    for(auto i = pattern.begin(); i!=pattern.end(); i++){
        
        char c = *i;

        //we need to add an interval
        if(prev == '-'){
            _Interval inter(secondPrev, c);
            intervalTransition[inter] = finalState;
            isFirst = true;
        }
        else{
            //the only interestung case is we're first, meaning the current char can be added
            if(isFirst){
                if(i+1 != pattern.end() && *(i+1) == '-'){
                    isFirst = false;
                }
                else{
                    AddTransition(c, finalState);
                }
            }
            
        }

        secondPrev = prev;
        prev = c;
        
    }

}


int Transitions::Move(char letter) const{

    //we need to pass through all the intervals...
    //but there should only be a fiew of them, so that's not a big problem
    if(!intervalTransition.empty()){
        for(auto p : intervalTransition){
            if(p.first.Contains(letter)) 
                return p.second;
        }
    }

    auto posInLetters = letterTransition.find(letter);
    if(posInLetters != letterTransition.end()){
        return posInLetters->second;
    }

    return -1;
}
