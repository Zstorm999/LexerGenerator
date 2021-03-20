#include "testautomaton.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(IOAutomatonTest, emptyOutput){
    Automaton a;

    string correct("0\n0\n");
    ASSERT_EQ(a.toString(), correct);
}

TEST(IOAutomatonTest, normalOutput){
    TestAutomaton a;

    string correct("3\n2 : if\n4 : for\n5 : id\n6\n0\n1 : fi\n5 : _A-Za-eg-hj-z\n1\n2 : f\n3 : o\n5 : $_0-9A-Za-eg-np-z\n2\n5 : $_0-9A-Za-z\n3\n4 : r\n5 : $_0-9A-Za-qs-z\n4\n5 : $_0-9A-Za-z\n5\n5 : $_0-9A-Za-z\n");
    ASSERT_EQ(a.toString(), correct);
}