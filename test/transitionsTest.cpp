#include "gtest/gtest.h"
#include "transitions.hpp"

//Transitions Test

TEST(TransitionsTest, singleLetterChar){
    DFA::Transitions t;
    t.AddTransition('a', 1);

    ASSERT_EQ(t.Move('a'), 1);
}

TEST(TransitionsTest, singleLetterString){
    DFA::Transitions t;
    t.AddTransition("a", 1);

    ASSERT_EQ(t.Move('a'), 1);
}

TEST(TransitionsTest, simpleInterval){
    DFA::Transitions t;
    t.AddTransition("a-z", 1);

    ASSERT_EQ(t.Move('a'), 1);
    ASSERT_EQ(t.Move('d'), 1);
    ASSERT_EQ(t.Move('z'), 1);
}

TEST(TransitionsTest, multipleInterval){
    DFA::Transitions t;
    t.AddTransition("A-Za-z", 1);

    ASSERT_EQ(t.Move('a'), 1);
    ASSERT_EQ(t.Move('d'), 1);
    ASSERT_EQ(t.Move('z'), 1);
    ASSERT_EQ(t.Move('A'), 1);
    ASSERT_EQ(t.Move('D'), 1);
    ASSERT_EQ(t.Move('Z'), 1);
}

TEST(TransitionsTest, multipleIntervalAndLetter){
    DFA::Transitions t;

    t.AddTransition("A-Z_$a-z", 1);

    ASSERT_EQ(t.Move('a'), 1);
    ASSERT_EQ(t.Move('d'), 1);
    ASSERT_EQ(t.Move('z'), 1);
    ASSERT_EQ(t.Move('A'), 1);
    ASSERT_EQ(t.Move('D'), 1);
    ASSERT_EQ(t.Move('Z'), 1);
    ASSERT_EQ(t.Move('_'), 1);
    ASSERT_EQ(t.Move('$'), 1);
}

TEST(TransitionsTest, variableNameRegex){
    DFA::Transitions t;

    t.AddTransition("a-zA-Z_$0-9", 1);

    ASSERT_EQ(t.Move('a'), 1);
    ASSERT_EQ(t.Move('d'), 1);
    ASSERT_EQ(t.Move('z'), 1);
    ASSERT_EQ(t.Move('A'), 1);
    ASSERT_EQ(t.Move('D'), 1);
    ASSERT_EQ(t.Move('Z'), 1);
    ASSERT_EQ(t.Move('_'), 1);
    ASSERT_EQ(t.Move('$'), 1);
    ASSERT_EQ(t.Move('4'), 1);
}

TEST(TransitionsTest, emptyTransition){
    DFA::Transitions t;


    ASSERT_EQ(t.Move('a'), -1);
}

//Compact Test

TEST(CompactTransitionTest, cleanIntervals){
    DFA::Transitions t;
    t.AddTransition("a-z", 1);

    t.Compact();

    ASSERT_EQ(t.toString(), "0\n");
}

TEST(CompactTransitionTest, interval){
    DFA::Transitions t;
    t.AddTransition('a', 1);
    t.AddTransition('b', 1);
    t.AddTransition('c', 1);

    t.Compact();
    
    ASSERT_EQ(t.toString(), "1\n1 : a-c\n");
}

TEST(CompactTransitionTest, noInterval){
    DFA::Transitions t;
    t.AddTransition('a', 1);
    t.AddTransition('c', 1);
    t.AddTransition('K', 1);

    t.Compact();

    ASSERT_EQ(t.toString(), "1\n1 : Kac\n");
}



TEST(CompactTransitionTest, differentDestination){
    DFA::Transitions t;
    t.AddTransition('a', 1);
    t.AddTransition('b', 2);
    t.AddTransition('c', 1);

    t.Compact();
    
    ASSERT_EQ(t.toString(), "2\n1 : ac\n2 : b\n");


}



TEST(CompactTransitionTest, mixed){
    DFA::Transitions t;
    t.AddTransition('a', 1);
    t.AddTransition('b', 1);
    t.AddTransition('c', 1);
    t.AddTransition('d', 1);
    t.AddTransition('e', 2);
    t.AddTransition('K', 1);

    t.Compact();
    
    ASSERT_EQ(t.toString(), "2\n1 : Ka-d\n2 : e\n");
}

