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
    CHECK_THROWS_AS(g1 == g2, std::invalid_argument);
    CHECK_THROWS_AS(g1 != g2, std::invalid_argument);
    CHECK_THROWS_AS(g1 < g2, std::invalid_argument);
    CHECK_THROWS_AS(g1 <= g2, std::invalid_argument);
    CHECK_THROWS_AS(g1 > g2, std::invalid_argument);
    CHECK_THROWS_AS(g1 >= g2, std::invalid_argument);
    CHECK_THROWS_AS(std::cout << g1, std::invalid_argument);

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

    std::vector<std::vector<int>> graph2 {
        {-3,1,1},
        {2,0,3},
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
    CHECK(!g1.isNegValues() && gSum.isNegValues());
    CHECK((g1 + g1).getGraph() == (g1 * 2).getGraph() && (g1 + g1).getGraph() == g11.getGraph());
    CHECK((g1 + g1) == (g1 * 2) && (g1 + g1) == g11);
}

TEST_CASE("Test multiplication by an integer")
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


}
