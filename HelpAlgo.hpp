namespace GraphLib
{   
   /**
    * @brief This fucntion retrieves the path from the predecessor vector.
    * @param pre The predecessor vector.
    * @param src The source vertex.
    * @param dst The destination vertex.
    * @return The path in the format "src->v1->v2->...->dst".
   **/
   std::string getPath(std::vector<int> &pre, size_t src, size_t dst, int len);

   /**
    * @brief This function is a helper function that runs the BFS algorithm on the graph.
    * @brief The vectors should be given after the initialization, the distance vector should have the value of INT_MAX,
       the predecessor vector should have the value of -1 and color vector should have the value of WHITE.
    * @param g The graph to be traversed.
    * @param src The source vertex.
    * @param dis The distance vector.
    * @param pre The predecessor vector.
    * @param col The color vector.
    * @return void, value will be stored in the given vectors.
    * @throws std::invalid_argument if the graph is not loaded.
   **/
   void BFS(const Graph &g, size_t src, std::vector<int> &dis, std::vector<int> &pre, std::vector<int> &col);
   
   /**
    * @brief This function is a helper function that runs the outer loop of the DFS algorithm on the graph.
    * @brief The vectors should be given after the initialization, the color vector should have the value of WHITE,
       the predecessor vector should have the value of -1, the discovery and finish time vectors should be initialized with 0.
    * @param g The graph to be traversed.  
    * @param col The color vector.
    * @param pre The predecessor vector.
    * @param dis The discovery time vector.
    * @param fin The finish time vector.
    * @return void, value will be stored in the given vectors.
    * @throws std::invalid_argument if the graph is not loaded.
   **/
   void DFS(const Graph &g, std::vector<int> &col, std::vector<int> &pre, std::vector<int> &dis, std::vector<int> &fin);
   
   /**
    * @brief This function is a helper function that runs the inner loop of the DFS algorithm on the graph.
    * @param g The graph to be traversed.
    * @param v The vertex to be visited.
    * @param col The color vector.
    * @param pre The predecessor vector.
    * @param dis The discovery time vector.
    * @param fin The finish time vector.
    * @return void, value will be stored in the given vectors.
   **/
   void DFS_VISIT(const Graph &g, size_t v, std::vector<int> &col, std::vector<int> &pre, int &time,std::vector<int> &dis, std::vector<int> &fin); 

   /**
    * @brief This function is a helper function that runs a modified DFS algorithm to detect cycles in the graph.
    * @brief The vectors should be given after the initialization, the color vector should have the value of WHITE
       and the predecessor vector should have the value of -1.
    * @param g The graph to be traversed.
    * @param v The vertex to be visited.
    * @param col The color vector.
    * @param pre The predecessor vector.
    * @param cycle The cycle vector.
    * @return void, value will be stored in the given vectors,
      if a cycle is detected then the cycle vector will contain two vertices that are part of the cycle.
   **/
   void DFSDetectCycle(const Graph &g, size_t v, std::vector<int> &col, std::vector<int> &pre, std::vector<int> &cycle);

   /**
    * @brief This function is a helper function that relaxes the edges of the graph.
    * @param u The source vertex.
    * @param v The destination vertex.
    * @param weight The weight of the edge.
    * @param dis The distance vector.
    * @param pre The predecessor vector.
    * @return void, value will be stored in the given vectors.
   **/
   void relax(size_t u, size_t v, int weight, std::vector<int> &dis, std::vector<int> &pre);

   /**
    * @brief This function is a helper function that runs the Dijkstra algorithm on the graph.
    * @brief The vectors should be given after the initialization, the distance vector should have the value of INT_MAX,
       the predecessor vector should have the value of -1 and the distance vector need one vector to be initialized with starting value 0.
    * @param g The graph to be traversed.
    * @param src The source vertex.   
    * @param dis The distance vector.
    * @param pre The predecessor vector.
    * @return void, value will be stored in the given vectors.
    * @throws std::invalid_argument if the graph is not loaded.
   **/
   void Dijkstra(const Graph &g, size_t src, std::vector<int> &dis, std::vector<int> &pre);
   
   /** 
    * @brief This function is a helper function that runs the Bellman-Ford algorithm on the graph.
    * @brief The vectors should be given after the initialization, the distance vector should have the value of INT_MAX
       and the predecessor vector should have the value of -1. The distance vector need one vector to be initialized with starting value 0.
    * @param g The graph to be traversed.
    * @param dis The distance vector.
    * @param pre The predecessor vector.
    * @param cycle The cycle vector.
    * @return true if the graph contains a negative cycle, false otherwise,
      if a negative cycle is detected then the cycle vector will contain TWO vertices that are part of the cycle.
    * @throws std::invalid_argument if the graph is not loaded.  
   **/
   bool bellmanFord(const Graph &g, std::vector<int> &dis, std::vector<int> &pre, std::vector<int> &cycle);
   
   /**
    * @brief Given a path in a string format return a vector that represent the 
       vertices in order.
    * @param path The path in the format "src->v1->v2->...->dst".
    * @return A vector of integers that represent the vertices in order.
   **/
   std::vector<int> parsePath(std::string path);

}
