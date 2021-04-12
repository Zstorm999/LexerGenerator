#include <iostream>
#include <fstream>
#include "dfa.hpp"

int main(void){

    DFA::Automaton a;


    std::cout << "\"if\" matches: " <<a.Matches("if") << "\n";
    std::cout << "\"\" matches: " << a.Matches("")  << "\n";
    std::cout << "\"for\" matches: " << a.Matches("for") << "\n";
    std::cout << "\"iffir\" matches: " << a.Matches("iffir") << "\n";
    std::fstream fs;

    std::cout << "\n" << a;

    return 0;
}