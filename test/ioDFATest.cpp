#include "testautomaton.hpp"
#include <gtest/gtest.h>
#include <string>
#include <fstream>

using namespace std;


TEST(IOAutomatonTest, emptyOutput){
    Automaton a;

    string correct("0\n0\n");
    ASSERT_EQ(a.toString(), correct);
}

TEST(IOAutomatonTest, normalOutput){
    TestAutomaton a;

    ASSERT_EQ(a.toString(), TestAutomaton::ExpectedString());
}

TEST(IOAutomatonTest, emptyInput){
    Automaton a;
    string correct("0\n0\n");
    stringstream ss(correct);

    ss >> a;
    ASSERT_EQ(a.toString(), correct);
}

TEST(IOAutomatonTest, coherence){
    TestAutomaton ta;
    Automaton a;
    stringstream ss;

    ss << ta;
    ss >> a;

    ASSERT_EQ(ta.toString(), a.toString());
    ASSERT_EQ(a.toString(), TestAutomaton::ExpectedString());
}

TEST(IOAutomatonTest, inputFromFile){
    fstream fs;
    Automaton a;
    
    try{
        fs.open("testres/testAutomaton.txt", fstream::in);
    }
    catch(fstream::failure e){
        cout << e.what();
    }

    fs >> a;
    fs.close();

    ASSERT_EQ(a.toString(), TestAutomaton::ExpectedString());
}