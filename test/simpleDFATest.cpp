#include "../includes/automaton.hpp"
#include "gtest/gtest.h"


using namespace DFA;

class TestAutomaton : public Automaton{
public:    
    TestAutomaton():
        Automaton()
    {
        addTransition(0, 1, "i");
        addTransition(1, 2, "f");

        addTransition(0, 1, "f");
        addTransition(1, 3, "o");
        addTransition(3, 4, "r");

        addTransition(0, 5, "a-eg-hj-zA-Z_");
        addTransition(1, 5, "a-eg-np-zA-Z_$0-9");
        addTransition(2, 5, "a-zA-Z_$0-9");
        addTransition(3, 5, "a-qs-zA-Z_$0-9");
        addTransition(4, 5, "a-zA-Z0-9_$");
        addTransition(5, 5, "a-zA-Z0-9_$");

        addFinalState(2, "if");
        addFinalState(4, "for");
        addFinalState(5, "id");
    }
};


TEST(SimpleDFATest, emptyString){
    TestAutomaton a;
    ASSERT_EQ(a.Matches(""), "");
}

TEST(SimpleDFATest, IfStatement){
    TestAutomaton a;
    ASSERT_EQ(a.Matches("if"), "if");
}

TEST(SimpleDFATest, ForStatement){
    TestAutomaton a;
    ASSERT_EQ(a.Matches("for"), "for");
}

TEST(SimpleDFATest, VariableNameLettersLower){
    TestAutomaton a;
    ASSERT_EQ(a.Matches("abcdefghijklmnopqrstuvwxyz"), "id");
}

TEST(SimpleDFATest, VariableNameLettersUpper){
    TestAutomaton a;
    ASSERT_EQ(a.Matches("ABCDEFGHIJKLMONPQRSTUVWXYZ"), "id");
}

TEST(SimpleDFATest, VariableName){
    TestAutomaton a;
    ASSERT_EQ(a.Matches("var1"), "id");
    ASSERT_EQ(a.Matches("_variable"), "id");
    ASSERT_EQ(a.Matches("_____"), "id");
    ASSERT_EQ(a.Matches("ifasda"), "id");
    ASSERT_EQ(a.Matches("forqsq546"), "id");
}

TEST(SimpleDFATest, InvalidName){
    TestAutomaton a;
    ASSERT_EQ(a.Matches("1var"), "");
}