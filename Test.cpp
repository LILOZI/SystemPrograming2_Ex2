#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

TEST_CASE("Test operations on unloaded graphs")
{
    GraphLib::Graph g1;
    GraphLib::Graph g2;
    
    CHECK_THROWS_AS(g1 + g2, std::invalid_argument);
    CHECK_THROWS_AS(g1 += g2, std::invalid_argument);
    CHECK_THROWS_AS(g1++, std::invalid_argument);
    CHECK_THROWS_AS(++g1, std::invalid_argument);
    CHECK_THROWS_AS(+g1, std::invalid_argument);
    CHECK_THROWS_AS(g1 - g2, std::invalid_argument);
    CHECK_THROWS_AS(g1 -= g2, std::invalid_argument);
    CHECK_THROWS_AS(g1--, std::invalid_argument);
    CHECK_THROWS_AS(--g1, std::invalid_argument);
    CHECK_THROWS_AS(-g1, std::invalid_argument);
    CHECK_THROWS_AS(g1 * 1, std::invalid_argument);
    CHECK_THROWS_AS(g1 *= 1, std::invalid_argument);
    CHECK_THROWS_AS(g1 * g2 , std::invalid_argument);
    CHECK_THROWS_AS(g1 *= g2, std::invalid_argument);
    CHECK_THROWS_AS(g1 / 1, std::invalid_argument);
    CHECK_THROWS_AS(g1 /= 1, std::invalid_argument);
    CHECK_THROWS_AS(g1.operator==(g2), std::invalid_argument);
    CHECK_THROWS_AS(g1.operator!=(g2), std::invalid_argument);
    CHECK_THROWS_AS(g1.operator<(g2), std::invalid_argument);
    CHECK_THROWS_AS(g1.operator<=(g2), std::invalid_argument);
    CHECK_THROWS_AS(g1.operator>(g2), std::invalid_argument);
    CHECK_THROWS_AS(g1.operator>=(g2), std::invalid_argument);
    // CHECK_THROWS_AS(std::cout << g1, std::invalid_argument);

}

TEST_CASE("Test graph addition"){
    GraphLib::Graph g1;
    GraphLib::Graph g2;
    GraphLib::Graph g3;
    GraphLib::Graph g11;
    GraphLib::Graph gSum;
    std::vector<std::vector<int>> graph1 {
        {NO_EDGE,1,1},
        {2,NO_EDGE,3},
        {1,4,5}
    };

    std::vector<std::vector<int>> graph1pp {
        {1,2,2},
        {3,1,4},
        {2,5,6}
    };

    std::vector<std::vector<int>> graph2 {
        {-3,1,1},
        {2,NO_EDGE,3},
        {1,4,5}
    };

    std::vector<std::vector<int>> graph3 {
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1,}
    };

    std::vector<std::vector<int>> graph11 {
        {NO_EDGE,2,2},
        {4,NO_EDGE,6},
        {2,8,10}
    };

    std::vector<std::vector<int>> sum {
        {-3,2,2},
        {4,NO_EDGE,6},
        {2,8,10}
    };
    
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g11.loadGraph(graph11);
    gSum.loadGraph(sum);


    CHECK((g1 + g2).getGraph() == sum);
    CHECK((g1 + g2) == gSum);
    CHECK_THROWS_AS(g1 + g3, std::invalid_argument);
    g3.loadGraph(graph3);
    CHECK_THROWS_AS(g1 + g3, std::invalid_argument);
    CHECK_EQ(!g1.isNegValues() && gSum.isNegValues(), true);
    CHECK(+g1 == g1);
    CHECK((+g1 + g2).getGraph() == sum);
    g1+=g2;
    CHECK(g1 == gSum);

    g1.loadGraph(graph1);
    g3 = ++g1;
    g1.loadGraph(graph1);
    g2 = g1++;

    CHECK(g2.getGraph() == graph1);
    CHECK(g3.getGraph() == graph1pp);

}

TEST_CASE("Test graph substraction"){
    GraphLib::Graph g1;
    GraphLib::Graph g2;
    GraphLib::Graph g3;
    GraphLib::Graph g11;
    GraphLib::Graph gSum;
    std::vector<std::vector<int>> graph1 {
        {NO_EDGE,1,1},
        {2,NO_EDGE,3},
        {1,4,5}
    };

    std::vector<std::vector<int>> minusgraph2 {
        {3,-1,-1},
        {-2,NO_EDGE,-3},
        {-1,-4,-5}
    };

    std::vector<std::vector<int>> graph1mm {
        {-1,NO_EDGE,NO_EDGE},
        {1,-1,2},
        {NO_EDGE,3,4}
    };

    std::vector<std::vector<int>> graph2 {
        {-3,1,1},
        {2,NO_EDGE,3},
        {1,4,5}
    };

    std::vector<std::vector<int>> graph3 {
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1,}
    };

    std::vector<std::vector<int>> graph11 {
        {NO_EDGE,NO_EDGE,NO_EDGE},
        {NO_EDGE,NO_EDGE,NO_EDGE},
        {NO_EDGE,NO_EDGE,NO_EDGE}
    };

    std::vector<std::vector<int>> sum {
        {3,NO_EDGE,NO_EDGE},
        {NO_EDGE,NO_EDGE, NO_EDGE},
        {NO_EDGE,NO_EDGE,NO_EDGE}
    };
    
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g11.loadGraph(graph11);
    gSum.loadGraph(sum);


    CHECK((g1 - g2).getGraph() == sum);
    CHECK((g1 - g2) == gSum);
    CHECK_THROWS_AS(g1 - g3, std::invalid_argument);
    g3.loadGraph(graph3);
    CHECK_THROWS_AS(g1 - g3, std::invalid_argument);
    CHECK_EQ(!g1.isNegValues() && !gSum.isNegValues(), true);
    CHECK((-g2).getGraph() == minusgraph2);
    CHECK((-g2 - (-g1)).getGraph() == sum);
    g1-=g2;
    CHECK(g1 == gSum);

    g1.loadGraph(graph1);
    g3 = --g1;
    g1.loadGraph(graph1);
    g2 = g1--;

    CHECK_EQ(!g2.isNegValues() && g3.isNegValues(), true);
    CHECK(g2.getGraph() == graph1);
    CHECK(g3.getGraph() == graph1mm);

}

TEST_CASE("Test multiplication by an integer and division by scalar")
{
    GraphLib::Graph g1;
    GraphLib::Graph g2;
    GraphLib::Graph g3;
    GraphLib::Graph gProduct;
    std::vector<std::vector<int>> graph1 {
        {NO_EDGE,1,1},
        {2,NO_EDGE,3},
        {1,4,5}
    };

    std::vector<std::vector<int>> graph2 {
        {-3,1,1},
        {2,0,3},
        {1,4,5}
    };

    std::vector<std::vector<int>> graph11 {
        {NO_EDGE,2,2},
        {4,NO_EDGE,6},
        {2,8,10}
    };

    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    gProduct.loadGraph(graph11);

    CHECK_EQ((g1 + g1).getGraph() == (g1 * 2).getGraph() && (g1 + g1).getGraph() == gProduct.getGraph(), true);
    CHECK_EQ((g1 + g1) == (g1 * 2) && (g1 + g1) == gProduct, true);

    gProduct *= -7;
    std::vector<std::vector<int>> graphProduct {
        {NO_EDGE,-14,-14},
        {-28,NO_EDGE,-42},
        {-14,-56,-70}
    };
    CHECK_EQ((g1 * -14) == gProduct, true);
    CHECK(gProduct.getGraph() == graphProduct);
    CHECK_EQ(gProduct.isNegValues() && gProduct.isDirected() && gProduct.isWeighted(), true);
    gProduct /= -7;
    CHECK(gProduct == g1*2);
    CHECK_EQ(!gProduct.isNegValues() && gProduct.isDirected() && gProduct.isWeighted(), true);
    CHECK(gProduct.getGraph() == graph11);  
    CHECK(gProduct/2 == g1);
}

TEST_CASE("Test assigning to a graph")
{
    GraphLib::Graph g1;
    GraphLib::Graph g2;

    std::vector<std::vector<int>> graph11 {
        {NO_EDGE,2,2},
        {4,NO_EDGE,6},
        {2,-4,10}
    };
    g1.loadGraph(graph11);

    g2 = g1;
    CHECK(g2.getGraph() == graph11);
    CHECK(g1 == g2);
    CHECK_EQ(g2.isDirected(), true);
    CHECK_EQ(g2.isNegValues() && g2.isWeighted() && g2.isLoaded(), true);
    
}

TEST_CASE("Test graph multiplication")
{
    GraphLib::Graph g1;
    GraphLib::Graph g2;
    GraphLib::Graph g3;
    GraphLib::Graph gProduct;
    std::vector<std::vector<int>> graph1 {
        {NO_EDGE,1,1},
        {2,NO_EDGE,3},
        {1,4,5}
    };

    std::vector<std::vector<int>> graph2 {
        {-3,1,1},
        {2,NO_EDGE,3},
        {1,4,5}
    };

    std::vector<std::vector<int>> graph3 {
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1,}
    };

    std::vector<std::vector<int>> product {
        {3,4,8},
        {-3,14,17},
        {10,21,38}
    };

    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g3.loadGraph(graph3);
    gProduct.loadGraph(product);

    CHECK((g1 * g2).getGraph() == product);
    CHECK((g1 * g2) == gProduct);
    CHECK_THROWS_AS(g1 * g3, std::invalid_argument);
    g3 = g1;
    g3 *= g2;
    CHECK(g3 == gProduct);
    CHECK_EQ(g3.isNegValues() && g3.isWeighted() && g3.isDirected(), true);
}

TEST_CASE("Test bigger than smaller than")
{
    GraphLib::Graph g1;
    GraphLib::Graph g2;
    GraphLib::Graph g3;
    GraphLib::Graph g4;
    std::vector<std::vector<int>> graph1 {
        {NO_EDGE,1,1},
        {2,NO_EDGE,3},
        {1,4,5}
    };
    std::vector<std::vector<int>> graph2 {
        {NO_EDGE,1},
        {2,NO_EDGE}
    };
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    CHECK_EQ(g1 > g2 && g1 >= g2 && g2 < g1 && g2 <= g1, true);
    std::vector<std::vector<int>> graph3 {
        {1,1},
        {NO_EDGE,3}
    };
    g3.loadGraph(graph3);
    CHECK_EQ(g1 > g3 && g1 >= g3 && g3 < g1 && g3 <= g1, true);
    
}
