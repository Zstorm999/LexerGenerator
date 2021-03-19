#ifndef _TRANSITIONS_HPP
#define _TRANSITIONS_HPP

#include <string>
#include <map>
#include <ostream>
#include <sstream>

namespace DFA{

    class Transitions
    {
    public:
        //nested class
        class _Interval;

        Transitions();

        std::string toString() const;

        void AddTransition(char letter, int finalState);
        void AddTransition(std::string pattern, int finalState);

        int Move(char letter) const;

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

        inline std::string toString() const {
            std::stringstream ss;
            ss << "[" << start << "; " << end << "]";
            return ss.str();
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
    
    inline std::ostream& operator<<(std::ostream& os, Transitions t){
        return os << t.toString();
    }

}

#endif //_TRANSITIONS_HPP