#ifndef _TRANSITIONS_HPP
#define _TRANSITIONS_HPP

#include <map>

namespace DFA{

    class Transitions
    {
    private:
        std::map<char, int> letterTransition;

    public:
        Transitions();

        void AddTransition(char letter, int finalState);

        int operator()(char letter);
    };
    
}

#endif //_TRANSITIONS_HPP