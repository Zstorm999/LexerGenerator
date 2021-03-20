#include "testautomaton.hpp"
#include "gtest/gtest.h"


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