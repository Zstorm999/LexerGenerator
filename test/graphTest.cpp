#include <gtest/gtest.h>
#include "nfagraph.hpp"

#include <algorithm>

using namespace NFA;

TEST(GraphTest, exceptions){

    Graph t;

    ASSERT_ANY_THROW(t.getNode(0));
    ASSERT_ANY_THROW(t.addTransition(0, 0));
    ASSERT_ANY_THROW(t.addTransition(0, 1));
    
    t.addNode();

    ASSERT_NO_THROW(t.getNode(0));
    ASSERT_NO_THROW(t.addTransition(0, 0));
    ASSERT_ANY_THROW(t.addTransition(0, 1));
}


TEST(GraphTest, eclosureEmpty){
    Graph t;
    t.addNode();

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected = {0};

    ASSERT_EQ(closure.size(), 1);
    ASSERT_EQ(closure[0], expected);
}

TEST(GraphTest, eclosureTrivial){

    Graph t;

    for(int i = 0; i < 10; i++) t.addNode();

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    ASSERT_EQ(closure.size(), 10);

    for(uint i=0; i<10; i++){
        std::set<uint> expected = {i};
        EXPECT_EQ(closure[i], expected); 
    }
}

TEST(GraphTest, eclosureSimple){
    Graph t;
    t.addNode();
    t.addNode();
    t.addTransition(0, 1);
    
    
    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected0 = {0, 1};

    std::set<uint> expected1 = {1};

    ASSERT_EQ(closure.size(), 2);
    EXPECT_EQ(closure[0], expected0);
    EXPECT_EQ(closure[1], expected1);


}

TEST(GraphTest, eclosureLoop){

    Graph t;
    t.addNode();
    t.addNode();
    t.addTransition(0, 1);
    t.addTransition(1, 0);

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected0 = {0, 1};

    std::set<uint> expected1 = {0, 1};

    ASSERT_EQ(closure.size(), 2);
    EXPECT_EQ(closure[0], expected0);
    EXPECT_EQ(closure[1], expected1);
}

TEST(GraphTest, eclosureNested){
    Graph t;
    t.addNode();
    t.addNode();
    t.addNode();

    t.addTransition(0, 1);
    t.addTransition(1, 2);

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected[] = {{0, 1, 2}, {1, 2}, {2}};

    ASSERT_EQ(closure.size(), 3);
    EXPECT_EQ(closure[0], expected[0]);
    EXPECT_EQ(closure[1], expected[1]);
    EXPECT_EQ(closure[2], expected[2]);

}

TEST(GraphTest, eclosureLoopNested){
    Graph t;
    t.addNode();
    t.addNode();
    t.addNode();

    t.addTransition(0, 1);
    t.addTransition(1, 2);
    t.addTransition(2, 0);

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected[] = {{0, 1, 2}, {0, 1, 2}, {0, 1, 2}};

    ASSERT_EQ(closure.size(), 3);
    EXPECT_EQ(closure[0], expected[0]);
    EXPECT_EQ(closure[1], expected[1]);
    EXPECT_EQ(closure[2], expected[2]);
}

TEST(GraphTest, eclosureReal){
    //Ex 2.2 from 'Basics of Compiler Design' by T. Mogensen
    Graph t;
    
    for(int i = 0; i< 7; i++) t.addNode();
    t.addNode("final");

    t.addTransition(0, 1);
    t.addTransition(1, 0, 'a');
    t.addTransition(0, 2);
    t.addTransition(2, 3);
    t.addTransition(2, 4);
    t.addTransition(3, 5, 'b');
    t.addTransition(4, 5, 'a');
    t.addTransition(5, 6, 'a');
    t.addTransition(6, 7, 'a');

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected[] = {
        {0, 1, 2, 3, 4},
        {1},
        {2, 3, 4},
        {3},
        {4},
        {5},
        {6},
        {7}
    };

    ASSERT_EQ(closure.size(), 8);

    for(int i = 0; i<8; i++){
        EXPECT_EQ(closure[i], expected[i]);
    }

}

TEST(GraphTest, merge){
    Graph g1;

    g1.addNode();
    g1.addNode();

    g1.addTransition(0, 1);

    Graph g2;

    g2.addNode();
    g2.addNode();

    g2.addTransition(0, 1);

    Graph result = Graph::fuseNewBranch(g1, g2);

    ASSERT_EQ(result.getNextID(), 4);

    for(int i = 0; i< result.getNextID(); i++){
        Graph::Node n = result.getNode(i);

        if(i == 0){
            EXPECT_EQ(n.nextStates[1].nextID, 2);
        }

        if(i%2 == 0){
            EXPECT_EQ(n.nextStates[0].nextID, i+1);
        }
        else{
            EXPECT_EQ(n.nextStates.size(), 0);
        }

    }

}

