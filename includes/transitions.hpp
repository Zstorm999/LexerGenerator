#ifndef _TRANSITIONS_HPP
#define _TRANSITIONS_HPP

#include <string>
#include <map>

namespace DFA{

    class Transitions
    {
    public:
        //nested class
        class _Interval;

        Transitions();

        void AddTransition(char letter, int finalState);
        void AddTransition(std::string pattern, int finalState);

        int Move(char letter);

    private:

        //data members
        std::map<char, int> letterTransition;
        std::map<_Interval, int> intervalTransition;
    };

    class  Transitions::_Interval
    {
        char start, end;
    
    public:
        inline _Interval(char _start, char _end)
            :start(_start), end(_end)
        {

        }

        inline bool Contains(char rune) const{
            if( rune >= start && rune <= end) return true;
            return false;
        }

        inline bool _Less(_Interval i){
            return start < i.start;
        }
    };

    inline bool operator<(Transitions::_Interval i1, Transitions::_Interval i2){
        return i1._Less(i2);
    }
    
    

}

#endif //_TRANSITIONS_HPP