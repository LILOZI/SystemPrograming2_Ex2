#include "Algorithms.hpp"
#include "HelpAlgo.hpp"
/*
 This function checks if a given graph is connected.
 If the graph is undirected then it uses the BFS algorithm to traverse the graph 
    and check if all the vertices were visited.
 If the graph is directed then it uses the DFS algorithm to traverse the graph
    and then runs BFS from the last root of the DFS to check if all the vertices were visited. 
*/
std::string GraphLib::Algorithms::isConnected(const Graph &g){
    if(!g.isLoaded()){
        throw std::invalid_argument("The graph is not loaded.");
    }
    size_t len = g.getNumVertices();
    if(!g.isDirected()){
        // if the graph is undirected run a single BFS
        std::vector<int> dis(len, INT_MAX);
        std::vector<int> pre(len, -1);
        std::vector<int> col(len, WHITE);
        BFS(g, 0, dis, pre, col);
        for(size_t i = 0; i< len; i++){
            if(col[i] == WHITE){
                return "The graph is not connected.";
            }
        }
        return "The graph is connected.";
    }
    
    // If the graph is undirected run a DFS and then BFS from the last root of the DFS tree
    std::vector<int> col(len, WHITE);
    std::vector<int> pre(len, -1);
    std::vector<int> dis(len, 0);
    std::vector<int> fin(len, 0);
    DFS(g, col, pre, dis, fin);
    int maxFin = 0;
    int lastRoot = -1;
    for(size_t i = 0; i<col.size(); i++){
        if(pre[i] == -1){
            if(fin[i] > maxFin){
                maxFin = fin[i];
                lastRoot = i;
            }
        }
    }
    for(size_t i = 0; i< len; i++){
        col[i] = WHITE;
        pre[i] = -1;
        dis[i] = INT_MAX;
    }
    BFS(g, (size_t)lastRoot, dis, pre, col);
    for(size_t i = 0; i< len; i++){
        if(col[i] == WHITE){
            return "The graph is not connected.";
        }
    }
    return "The graph is connected.";
}
/*
 This function uses BFS if the graph is unweighted, Dijkstra if the graph has no
    negative values and Bellman-Ford if the graph has negative values.
*/
std::string GraphLib::Algorithms::shortestPath(const Graph &g, size_t src, size_t dst){
    if(!g.isLoaded()){
        throw std::invalid_argument("The graph is not loaded.");
    }
    size_t len = g.getNumVertices();
    if(src >= len || dst >= len){
        throw std::invalid_argument("The source or destination vertex is out of range.");
    }
    if(src == dst){
        return "The shortest path is: " + std::to_string(src);
    }
    std::vector<int> dis(len, INT_MAX);
    std::vector<int> pre(len, -1);
    if(!g.isWeighted()){ // the graph has no weights
        std::vector<int> col(len, WHITE);
        BFS(g, src, dis, pre, col);
        if(dis[dst] == INT_MAX){
            return "There is no path between " + std::to_string(src) + " and " + std::to_string(dst) + ".";
    }
        return "The shortest path is: " + getPath(pre, src, dst, len);
    }
    if(g.isNegValues()){ // the graph has negative values
        Graph temp;
        // remove all the negative weight cycles that are in the graph
        // if the vetrtices are connected via a cycle then any path is invalid
        std::vector<int> cyc;
        std::vector<std::vector<int>> newGraph = g.getGraph();
        temp.loadGraph(newGraph);
        std::string cycle = negativeCycle(temp);
        while(cycle != "The graph has no negative cycle."){
            cycle = cycle.substr(23, cycle.size() - 23);
            std::vector<int> path = parsePath(cycle);
            for(size_t i = 0; i < path.size() - 1; i++){
                newGraph[(size_t)path[i]][(size_t)path[i+1]] = NO_EDGE;
            } 
            temp.loadGraph(newGraph);
            cycle = negativeCycle(temp);
        }
        temp.loadGraph(newGraph);
        dis[src] = 0;
        // find the shortest path in the cycle free graph
        bellmanFord(temp, dis, pre, cyc);
        if(dis[dst] == INT_MAX){
            std::vector<int> col(len, WHITE);
            for(size_t i = 0; i < len; i++){
                dis[i] = INT_MAX;
                pre[i] = -1;
            }
            // if the vertices are connected in the original graph
            BFS(g, src, dis, pre, col);
            if(dis[dst] != INT_MAX){
                return std::to_string(src) + " and " + std::to_string(dst) + " are connected by a negative weight cycle.";
            }
            // originally there was no path
            return "There is no path between " + std::to_string(src) + " and " + std::to_string(dst) + ".";
        }
        return "The shortest path is: " + getPath(pre, src, dst, len);
    }
    // there are weights but they are not negative
    Dijkstra(g, src, dis, pre);
    if(dis[dst] == INT_MAX){
        return "There is no path between " + std::to_string(src) + " and " + std::to_string(dst) + ".";
    }
    return "The shortest path is: " + getPath(pre, src, dst, len);
}


/*
 This function checks if the graph contains a cycle.
 It does so by running DFS on the graph and checking if there is a back edge.
 If there is a back edge then there is a cycle.
*/
std::string GraphLib::Algorithms::isContainsCycle(const Graph &g){
    if(!g.isLoaded()){
        throw std::invalid_argument("The graph is not loaded.");
    }
    size_t len = g.getNumVertices();
    std::vector<int> col(len, WHITE); 
    std::vector<int> pre(len, -1); 
    std::vector<int> cycle; 
    for (size_t i = 0; i < len; i++) {
        if (col[i] == WHITE) {
            DFSDetectCycle(g, i, col, pre, cycle); 
        }
    }
    if(cycle.empty()){
        return "There is no cycle in the graph.";
    }
    std::string result = "The cycle is: ";
    result += getPath(pre, (size_t)cycle[0], (size_t)cycle[1], len);

    result += "->"  + std::to_string(cycle[0]);

    return result;
}
/*
 This function checks if the graph is bipartite.
 It does so by running BFS on the graph and coloring the vertices in two colors.
 If there is an edge between two vertices of the same color then the graph is not bipartite.
*/
std::string GraphLib::Algorithms::isBipartite(const Graph &g){
    if(!g.isLoaded()){
        throw std::invalid_argument("The graph is not loaded.");
    }
    size_t len = g.getNumVertices();
    std::vector<int> col(len, WHITE);  
    std::vector<int> A; // GRAY
    std::vector<int> B; // BLACK
    // if the graph is directed make it an undirected graph
    // the directed graph is bipartite if and only if the undirected graph is bipartite
    if(g.isDirected()){
        Graph undirectedGraph = g;
        std::vector<std::vector<int>> newGraph = g.getGraph();
        for(size_t i = 0; i < len; i++){
            for(size_t j = 0; j < len; j++){
                if(g.getWeight(i, j) != NO_EDGE){
                    newGraph[j][i] = 1;
                }
            }        
        }
        undirectedGraph.loadGraph(newGraph);
        return isBipartite(undirectedGraph);
    }
    // go through all the vertices, if the vertex is white then color it gray
    // and color all the adjacent vertices with the opposite color
    // if the color is black color all the adjacent vertices with gray
    // if there is an edge between two vertices of the same color then the graph is not bipartite
    for(size_t i = 0; i < len; i++){
        if(col[i] == WHITE){
            // self edge will make it automatically not bipartite
            if(g.getWeight(i, i) != NO_EDGE){
                return "The graph is not bipartite.";
            }
            col[i] = GRAY;
            A.push_back(i);
            for(size_t j = 0; j < len; j++){
                if(g.getWeight(i, j) != NO_EDGE){
                    if(col[j] == WHITE){
                        col[j] = BLACK;
                        B.push_back(j);
                    }
                    else if(col[j] == GRAY){
                        return "The graph is not bipartite.";
                    }
                }
            }
        }
        if(col[i] == BLACK){
            for(size_t j = 0; j < len; j++){
                if(g.getWeight(i, j) != NO_EDGE){
                    if(col[j] == WHITE){
                        col[j] = GRAY;
                        A.push_back(j);
                    }
                    else if(col[j] == BLACK){
                        return "The graph is not bipartite.";
                    }
                }
            }
        }
        if(col[i] == GRAY){
            for(size_t j = 0; j < len; j++){
                if(g.getWeight(i, j) != NO_EDGE){
                    if(col[j] == WHITE){
                        col[j] = BLACK;
                        B.push_back(j);
                    }
                    else if(col[j] == GRAY){
                        return "The graph is not bipartite.";
                    }
                }
            }
        }
    }
    std::string result = "The graph is bipartite: A={";
    for(size_t i = 0; i < A.size(); i++){
        result += std::to_string(A[i]);
        if(i != A.size() - 1){
            result += ", ";
        }
    }
    result += "}, B={";
    for(size_t i = 0; i < B.size(); i++){
        result += std::to_string(B[i]);
        if(i != B.size() - 1){
            result += ", ";
        }
    }
    result += "}.";
    return result;
}
/*
 This function checks if the graph has a negative cycle and returns it.
 It does so by creating a new graph with an additional vertex and connecting 
 it to all other vertices with weight 1.
 Then it runs the Bellman-Ford algorithm on the new graph.
*/
std::string GraphLib::Algorithms::negativeCycle(const Graph &g){
    if(!g.isLoaded()){
        throw std::invalid_argument("The graph is not loaded.");
    }
    if(!g.isNegValues()){
        return "The graph has no negative cycle.";
    }
    size_t len = g.getNumVertices();
    // create a new graph with an additional vertex
    std::vector<std::vector<int>> newGraph(len +1, std::vector<int>(len + 1, NO_EDGE));
    // add an edge from the new vertex to all other vertices
    for(size_t i = 0; i<len; i++){
        newGraph[len][i] = 1; 
    }
    // copy all the edges to the new graph
    for(size_t i = 0; i < len; i++){
        for(size_t j = 0; j < len; j++){
            if(g.getWeight(i, j) != NO_EDGE){
                newGraph[i][j] = g.getWeight(i, j);
            }
        }
    }
    Graph temp;
    // no need for try-catch block since if the new graph is not squared
    // then the original graph was illegal to begin with.
    temp.loadGraph(newGraph);
    if(!g.isDirected()){
        temp.setUnDirected();
    }
    std::vector<int> dis(len + 1, INT_MAX);
    std::vector<int> pre(len + 1, -1);
    std::vector<int> cycle;
    // the starting distance is -1 because the edge weight is 1
    // (zero is used to represent no edge in the graph)
    dis[len] = -1;
    // bellman ford return true if there is a negative cycle   
    if(bellmanFord(temp, dis, pre, cycle)){
        
        std::string path = getPath(pre, (size_t)cycle[0], (size_t)cycle[1], len);
        if(cycle[0] == len){
        path = path.substr(3, path.size() - 3);
        std::string lastEdge = path.substr(0, 1);
        return "The negative cycle is: " + path + "->" + lastEdge;
        }
        return "The negative cycle is: " + path + "->" + std::to_string(cycle[0]);
    }
    return "The graph has no negative cycle.";
    
}

std::string GraphLib::getPath(std::vector<int> &pre, size_t src, size_t dst, int len){
    if(len < 2){
        return std::to_string(src);
    }
    if(dst == src){
        return std::to_string(src);
    }
    return getPath(pre, src, (size_t)pre[dst], len-1) + "->" + std::to_string(dst);
}

void GraphLib::BFS(const Graph &g, size_t src,std::vector<int> &dis, std::vector<int> &pre, std::vector<int> &col){
    if(!g.isLoaded()){
        throw std::invalid_argument("The graph is not loaded.");
    }
    size_t len = g.getNumVertices();
    std::vector<int> q;
    q.push_back(src);
    col[src] = GRAY;
    pre[src] = -1;
    dis[src] = 0;
    while(!q.empty()){
        int cur = q[0];
        q.erase(q.begin());
        for(size_t i = 0; i< len; i++){
            if(g.getWeight((size_t)cur, i) != NO_EDGE && (col[i] == WHITE)){
                
                q.push_back(i);
                col[i] = GRAY;
                pre[i] = cur;
                dis[i] = dis[(size_t)cur] + 1;
            }
        }
        col[(size_t)cur] = BLACK;
    }
}

void GraphLib::DFS(const Graph &g, std::vector<int> &col, std::vector<int> &pre, std::vector<int> &dis, std::vector<int> &fin) { 
    if(!g.isLoaded()){
        throw std::invalid_argument("The graph is not loaded.");
    }
    int time = 0;
    for(size_t i = 0; i < g.getNumVertices(); i++){
        if(col[i] == WHITE){
            DFS_VISIT(g, i, col, pre, time,dis, fin); // Visit each unvisited vertex
        }
    }
}

void GraphLib::DFS_VISIT(const Graph &g, size_t v, std::vector<int> &col, std::vector<int> &pre, int &time,std::vector<int> &dis, std::vector<int> &fin) {
    col[v] = 1; // Mark vertex as visited (color it gray)
    time++;
    dis[v] = time;
    // Perform any necessary operations on the vertex v
    
    for (size_t i = 0; i < g.getNumVertices(); i++) {
        if (g.getWeight(v, i) != NO_EDGE && col[i] == WHITE) {
            pre[i] = v; // Set the predecessor of vertex i to v
            DFS_VISIT(g, i, col, pre, time,dis, fin); // Recursively visit the adjacent vertices
        }
        
    }
    
    col[v] = BLACK; // Mark vertex as finished (color it black)
    time++;
    fin[v] = time;
}

void GraphLib::DFSDetectCycle(const Graph &g, size_t v, std::vector<int> &col, std::vector<int> &pre, std::vector<int> &cycle) {
    col[v] = GRAY; // Mark vertex as visited (color it gray)
    // Perform any necessary operations on the vertex v
    
    for (size_t i = 0; i < g.getNumVertices(); i++) {
        if(!cycle.empty()){
            return;
        }
        if (g.getWeight(v, i) != NO_EDGE && col[i] == WHITE) {
            pre[i] = v; // Set the predecessor of vertex i to v
            DFSDetectCycle(g, i, col, pre, cycle); // Recursively visit the adjacent vertices
        }
        else if (g.getWeight(v, i) != NO_EDGE && col[i] == GRAY){// Found a back edge 
            if(g.isDirected()){
                cycle.push_back(i);
                cycle.push_back(v);
                return;
            }
            if(pre[v] != i){
                cycle.push_back(i);
                cycle.push_back(v);
                return;
            }
        }
    }
    col[v] = BLACK; // Mark vertex as finished (color it black)
}

void GraphLib::relax(size_t u, size_t v, int weight, std::vector<int> &dis, std::vector<int> &pre) {
    if (dis[u] + weight < dis[v]) {
        dis[v] = dis[u] + weight;
        pre[v] = u;
    }
}

void GraphLib::Dijkstra(const Graph &g, size_t src, std::vector<int>& dis, std::vector<int>& pre) {
    size_t len = g.getNumVertices();
    std::vector<bool> visited(len, false);
    
    dis[src] = 0;
    
    for (size_t i = 0; i < len - 1; i++) {
        int minDist = INT_MAX;
        int minIndex = -1;
        
        // Find the vertex with the minimum distance
        for (size_t v = 0; v < len; v++) {
            if (!visited[v] && dis[v] < minDist) {
                minDist = dis[v];
                minIndex = v;
            }
        }
        if(minIndex == -1){
            continue;
        }
        // Mark the vertex as visited
        visited[(size_t)minIndex] = true;
        
        // Update the distances of the adjacent vertices
        for (size_t v = 0; v < len; v++) {
            if (g.getWeight((size_t)minIndex, v) != NO_EDGE && !visited[v] && dis[(size_t)minIndex] != INT_MAX&& dis[(size_t)minIndex] + g.getWeight((size_t)minIndex, v) < dis[v]) { // && dis[minIndex] + g.adjTable[minIndex][v] < dis[v]
                // relax(minIndex, v, g.adjTable[minIndex][v], dis, pre);
                dis[v] = dis[(size_t)minIndex] + g.getWeight((size_t)minIndex, v);
                pre[v] = minIndex;
            }
        }
    }
}
/*
 This function is an implementation of the Bellman-Ford algorithm, that uses the
 property of the Upper bound of the shortest path to detect negative-weight cycles
 and find the shortest path between two vertices.
*/
bool GraphLib::bellmanFord(const Graph &g, std::vector<int> &dis, std::vector<int> &pre, std::vector<int> &cycle) {
    size_t len = g.getNumVertices();
    // vectors dis(distance) and pre(predecessor) were initialized before the function call
    // relax all the edges len-1 times, for the length of the largest shortest path
    for (size_t i = 0; i < len -1; i++) {
        for (size_t u = 0; u < len; u++) {
            for (size_t v = 0; v < len; v++) {
                if (g.getWeight(u,v) != NO_EDGE){
                    if(!g.isDirected() && pre[u] == (int)v){
                        continue;
                    }
                    // did not reach vertex u yet
                    if(dis[u] == INT_MAX){
                        continue;
                    }
                    // if u hav been reached try to relax the edge
                    if(dis[u] != INT_MAX) { // && dis[u] + g.getWeight(u,v) < dis[v]
                        relax(u, v, g.getWeight(u,v), dis, pre); // Use the relax function
                    }
                }
            }
        }
    }
    // all the vertices should have converged at this point
    // if we can relax an edge, then that edge is a part of a negative-weight cycle
    for (size_t u = 0; u < len-1; u++) {
        for (size_t v = 0; v < len; v++) {
            
            if(g.getWeight(u,v) != NO_EDGE){
                if(!g.isDirected() && pre[u] == (int)v){
                    continue;
                }
                if(dis[u] == INT_MAX){
                    continue;
                }
                if(dis[u] != INT_MAX && dis[u] + g.getWeight(u,v) < dis[v]) {
                    
                    pre[v] = u;
                    cycle.push_back(u);
                    cycle.push_back(pre[u]);
                    return true; // Negative-weight cycle detected 
                }      
            }
        }
    }
    return false; // No negative-weight cycle detected
}

std::vector<int> GraphLib::parsePath(std::string path) {
    std::vector<int> result;
    std::string delimiter = "->";
    size_t pos = 0;
    std::string token;
    while ((pos = path.find(delimiter)) != std::string::npos) {
        token = path.substr(0, pos);
        result.push_back(std::stoi(token));
        path.erase(0, pos + delimiter.length());
    }
    result.push_back(std::stoi(path));
    return result;  
}
    