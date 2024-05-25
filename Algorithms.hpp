
#include <string>
#include "Graph.hpp"

namespace GraphLib{
        
        namespace Algorithms{
                /**
                 * @brief This function checks if the given graph is connected.
                 * @param g The graph to be checked.
                 * @return "The graph is connected." or "The graph is not connected.".
                 * @throws std::invalid_argument if the graph is not loaded.
                **/
               std::string isConnected(const Graph &g);
                
                /**
                 * @brief This function find the shortest path between two vertices.
                 * @brief Vertices must be natural numbers given in the range [0, n-1] where n is the number of vertices.
                 * @param g The graph to look for path on.
                 * @param src The source vertex.
                 * @param dst The destination vertex.
                 * @return The shortest path between the two vertices int the next
                        * format: "src->v1->v2->...->dst".
                 * @throws std::invalid_argument if the graph is not loaded.      
                **/
                std::string shortestPath(const Graph &g, size_t src, size_t dst);

                /**
                 * @brief This function checks if the given graph contains a cycle.
                 * @param g The graph to be checked.
                 * @return "There is no cycle in the graph" or "The cycle is: {cycle}"
                 * @throws std::invalid_argument if the graph is not loaded.
                **/
                std::string isContainsCycle(const Graph &g);

                /**
                 * @brief This function checks if the given graph is Bipartite.
                 * @param g The graph to be checked.
                 * @return The partition to sets of vertices A and B.
                 * @throws std::invalid_argument if the graph is not loaded.
                **/
                std::string isBipartite(const Graph &g);

                /**
                 * @brief This function finds whether the graph contains a negative cycle.
                 * @brief In an undirected graph two vertices are not considered a cycle on their own,
                 * @brief but in a directed graph two vertices are considered a cycle.
                 * @param g The graph to look for path on.
                 * @return "There is no negative cycle in the graph" or "The negative cycle is: {cycle}
                 * @throws std::invalid_argument if the graph is not loaded.
                **/
                std::string negativeCycle(const Graph &g);

        }
}