#include "../includes/simpleDFA.hpp"
#include "gtest/gtest.h"


using namespace DFA;

TEST(SimpleDFATest, emptyString){
    Automaton a;
    ASSERT_EQ(a.Matches(""), "");
}

TEST(SimpleDFATest, IfStatement){
    Automaton a;
    ASSERT_EQ(a.Matches("if"), "if");
}

TEST(SimpleDFATest, ForStatement){
    Automaton a;
    ASSERT_EQ(a.Matches("for"), "for");
}

TEST(SimpleDFATest, VariableNameLettersLower){
    Automaton a;
    ASSERT_EQ(a.Matches("abcdefghijklmnopqrstuvwxyz"), "id");
}

TEST(SimpleDFATest, VariableNameLettersUpper){
    Automaton a;
    ASSERT_EQ(a.Matches("ABCDEFGHIJKLMONPQRSTUVWXYZ"), "id");
}

TEST(SimpleDFATest, VariableName){
    Automaton a;
    ASSERT_EQ(a.Matches("var1"), "id");
    ASSERT_EQ(a.Matches("_variable"), "id");
    ASSERT_EQ(a.Matches("_____"), "id");
}

TEST(SimpleDFATest, InvalidName){
    Automaton a;
    ASSERT_EQ(a.Matches("1var"), "");
    ASSERT_EQ(a.Matches("iffif"), "");
    ASSERT_EQ(a.Matches("forrqsd"), "");
}