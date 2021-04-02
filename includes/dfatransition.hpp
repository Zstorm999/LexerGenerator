#ifndef _TRANSITIONS_HPP
#define _TRANSITIONS_HPP

#include <string>
#include <map>
#include <ostream>
#include <utility>

namespace DFA{


    class Transitions
    {
    public:

        Transitions();
        Transitions(Transitions const& other);
        ~Transitions();

        std::string toString() const;

        void AddTransition(char letter, int finalState);
        void AddTransition(std::string pattern, int finalState);

        int Move(char letter) const;

        void Compact();

    private:
        typedef std::pair<char, char> Interval;

        //data members
        std::map<char, int>* letterTransition;
        std::map<Interval, int>* intervalTransition;

        inline bool contains(Interval const& i, char letter) const{
            return letter >= i.first && letter <= i.second;
        }

    };
    
    inline std::ostream& operator<<(std::ostream& os, Transitions t){
        return os << t.toString();
    }

}

#endif //_TRANSITIONS_HPP