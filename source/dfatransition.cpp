#include "dfatransition.hpp"

using namespace DFA;
using namespace std;

Transitions::Transitions():
    letterTransition(new map<char, int>),
    intervalTransition(new map<Interval, int>)
{

}

Transitions::Transitions(Transitions const& other)
{
    letterTransition = new map<char, int>(*other.letterTransition);
    intervalTransition = new map<Interval, int>(*other.intervalTransition);
}

Transitions::~Transitions(){
    delete letterTransition;
    delete intervalTransition;
}

string Transitions::toString() const{
    stringstream ss;

    map<int, stringstream> trans;

    for(auto p : *letterTransition){
        trans[p.second] << p.first; 
    }

    for(auto p: *intervalTransition){
        trans[p.second] << p.first.first << "-" << p.first.second;
    }

    ss << trans.size() << "\n";
    for(auto p = trans.begin(); p != trans.end(); p++){
        ss << p->first << " : " << p->second.str() <<"\n";
    }

    return ss.str();
}

void Transitions::AddTransition(char letter, int finalState){
    (*letterTransition)[letter] = finalState;  
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
            Interval inter(secondPrev, c);
            (*intervalTransition)[inter] = finalState;
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
    //but there should only be a few of them, so that's not a big problem
    if(!intervalTransition->empty()){
        for(auto p : *intervalTransition){
            if(contains(p.first, letter)) 
                return p.second;
        }
    }

    auto posInLetters = letterTransition->find(letter);
    if(posInLetters != letterTransition->end()){
        return posInLetters->second;
    }

    return -1;
}

void Transitions::Compact(){
    //we assume all values are in letters, and that intervals is empty
    //anyway all values in letters will be lost when calling this function
    
    //so first we delete any previously existing interval map T_T*
    //this is to make sure there is no unintended side effect
    //maybe change this in a future version ? (I really don't think this is useful...)

    delete intervalTransition;
    intervalTransition = new map<Interval, int>;

    map<char, int>::iterator p = letterTransition->begin();
    map<char, int>::iterator pNext;

    loop:

    while(p != letterTransition->end()){
        
        //we need to find if the letter could fit in an already existing interval
        for(auto it = intervalTransition->begin(); it != intervalTransition->end(); it++){
            
            if(it->second == p->second){
                //two possible cases : after, not related
                //before and inside are not possible since values are evaluated in ascending order
                Interval i = it->first;
                char letter = p->first;

                if(letter == (i.second +1)){
                    //we need to update the interval
                    intervalTransition->erase(it);
                    i.second++;
                    (*intervalTransition)[i] = p->second;
                    //no ned to continue looping, no other interval will fit

                    p = letterTransition->erase(p);

                    goto loop;
                }
            }
        }

        //if we get to this point, it means that no interval was found for the letter
        //this is the point where we add a new interval, if the next letter has the same destination
        pNext = p;
        pNext++;

        if(p->second == pNext->second && p->first == (pNext->first-1)){
            
            Interval i(p->first, pNext->first);
            (*intervalTransition)[i] = p->second;

            //remove both from letters
            p = letterTransition->erase(p);
            p = letterTransition->erase(p);
        }
        else{
            p = pNext;
        }

        
    }

    //there is no need to check for interval overlap, since map stores elements in ascending order

}
