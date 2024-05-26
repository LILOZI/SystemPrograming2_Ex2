#include <vector>
#include <iostream>
#include <stdexcept>
#pragma once

namespace GraphLib{
    #define INT_MAX 2147483647
    #define NO_EDGE 0
    enum Color{WHITE, GRAY, BLACK};

    /**
     * @class Graph
     * @brief This class represents a graph.
     * @brief The graph can be directed or undirected, weighted or unweighted.
     * @brief The graph can contain negative values or not.
     * @brief The graph uses an adjacency matrix to represent the graph, hence 
     * @brief the graph is loaded by squared matrices only. 
     * @brief The graph can not have an edge weighted as 0, the value 0 is used to represent no edge.
     **/
    class Graph {
        private:
        std::vector<std::vector<int>> adjTable;
        bool directed;
        bool weighted;
        bool negValues;
        bool loaded;
        bool isSymetric();
        void copyFlags(const GraphLib::Graph &g);
        void setDirected() { directed = true; }
        void setWeighted() {weighted = true;}
        void setNegValues() {negValues = true;}
        void setLoaded() {loaded = true;}
        void clear() {adjTable.clear();loaded = false; directed = false; weighted = false; negValues = false;}
        public:
        Graph();

        ~Graph();

        /**
         * @brief This is a copy constructor.
         * @throws std::invalid_argument if the given graph is not loaded.
        **/
        Graph(const Graph &g) {
            if(!g.loaded){throw std::invalid_argument("The given graph is not loaded.");}
            adjTable = g.adjTable;
            copyFlags(g);
        }
        
        /**
         * @return The number of vertices in the graph.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        size_t getNumVertices() const {
            if(!loaded){throw std::invalid_argument("The graph is not loaded.");}
            return adjTable.size();
        }

        /**
         * @param i The vertex that the edge "lefts".
         * @param j The vertex that the edge "enters".
         * @return The weight of the edge between the two vertices.
         * @throws std::invalid_argument if the given vertices are out of range or the graph is not loaded.
        **/
        int getWeight(size_t i, size_t j) const {
            if(i >= adjTable.size() || j >= adjTable.size()){throw std::invalid_argument("The given vertices are out of range.");}
            if(!loaded){throw std::invalid_argument("The graph is not loaded.");}
            return adjTable[i][j];
        }

        /**
         * @brief This method loads values to the adjacency matrix that represents the graph.
         * @param mat The matrix that represents the graph.
         * @return true if the graph is loaded, false otherwise.
         * @throws std::invalid_argument if the given matrix is not squared or empty.
        **/
        void loadGraph(std::vector<std::vector<int>> mat);
        /**
         * @brief This method prints information about the graph in the following format:
         * @brief "This is {a directed/ an undirected} graph with {number of vertices} vertices and {number of edges} edges."
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        void printGraph();

        /**
         * @return Whether the graph is directed or not.
        **/
        bool isDirected() const {return directed;}

        void setUnDirected() {directed = false;}

        /**
         * @return Whether the graph is weighted or not.
        **/
        bool isWeighted() const {return weighted;}

        /**
         * @return Whether the graph has negative values or not.
        **/
        bool isNegValues() const {return negValues;}

        /**
         * @return Whether the graph has been loaded or not.
        **/
        bool isLoaded() const {return loaded;}

        /**
         * @return The adjacency matrix that represents the graph.
        **/
        std::vector<std::vector<int>> getGraph() const {return adjTable;}

        /**
         * @brief This method updates all the boolean flags of a graph.
         * @return void.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        void updateGraphFlags();

        /**
         * @brief This method checks if the current graph is a subgraph of given graph.
         * @param g The graph to be checked if it contains the current graph.
         * @return true if the current graph is a subgraph of the given graph, false otherwise.
         * @throws std::invalid_argument if one of the graphs is not loaded.
        **/
        bool subGraph(const Graph &g) const;

        /**
         * @brief This method counts how many edges a graph has.
         * @return The number of edges in the graph.
         * @throws std::invalid_argument if the graph is not loaded. 
        **/
        int countEdges() const;

// ---------------------------------------------------------------------------------------------
//                    all of the overloaded operators
// ---------------------------------------------------------------------------------------------    
        
        /**
         * @brief This method overloads the operator = to copy a graph.
         * @param g The graph to be copied.
         * @return The new graph after the copy.
         * @throws std::invalid_argument if the given graph is not loaded.
        **/
        Graph& operator=(const Graph &g);

        /**
         * @brief This method overloads the operator + to add two graphs.
         * @param g The graph to be added to the current graph.
         * @return pointer to the new graph that is the sum of the two graphs.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph.
        **/
        Graph operator+(const Graph &g) const;

        /**
         * @brief This method overloads the operator += to add a graph to the current graph.
         * @param g The graph to be added to the current graph.
         * @return The current graph after the addition.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph.
        **/
        Graph& operator+=(const Graph &g);

        /**
         * @brief This method overloads the operator ++ to add 1 to all the values in the graph.
         * @brief The addition is done before the value is returned.
         * @return The current graph after the addition.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph& operator++();
        
        /**
         * @brief This method overloads the operator ++ to add 1 to all the values in the graph.
         * @brief The addition is done after the value is returned.
         * @return The current graph before the addition.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph operator++(int);

        /**
         * @brief This method overloads the operator + to return the unary addition of a graph.
         * @return The current graph.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph operator+() const;

        /**
         * @brief This method overloads the operator - to subtract two graphs.
         * @param g The graph to be subtracted from the current graph.
         * @return pointer to the new graph that is the subtraction of the two graphs.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph.
        **/
        Graph operator-(const Graph &g) const;

        /**
         * @brief This method overloads the operator -= to subtract a graph from the current graph.
         * @param g The graph to be subtracted from the current graph.
         * @return The current graph after the subtraction.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph. 
        **/
        Graph& operator-=(const Graph &g);

        /**
         * @brief This method overloads the operator -- to subtract 1 from all the values in the graph.
         * @brief The substraction is done before the value is returned.
         *  @return The current graph after the subtraction.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph& operator--();

        /**
         * @brief This method overloads the operator -- to subtract 1 from all the values in the graph.
         * @brief The substraction is done after the value is returned. 
         * @return The current graph before the subtraction.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph operator--(int);

        /**
         * @brief This method overloads the operator - to negate all the values in the graph.
         * @return pointer to the new graph that is the negation of the current graph.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph operator-() const;
    
        /**
         * @brief This method overloads the operator * to multiply the graph by a number. 
         * @param num The number to multiply the graph by.
         * @return pointer to the new graph that is the multiplication of the current graph by the given number.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph operator*(int num) const;

        /**
         * @brief This method overloads the operator *= to multiply the graph by a number.
         * @param num The number to multiply the graph by.
         * @return The current graph after the multiplication.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph& operator*=(int num);

        /**
         * @brief This method overloads the operator / to divide the graph by a number.
         * @param num The number to divide the graph by.
         * @return pointer to the new graph that is the division of the current graph by the given number.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph operator/(int num) const;

        /**
         * @brief This method overloads the operator /= to divide the graph by a number.
         * @param num The number to divide the graph by.
         * @return The current graph after the division.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        Graph& operator/=(int num);

        /**
         * @brief This method overloads the operator * to multiply two graphs.
         * @param g The graph to be multiplied by the current graph.
         * @return pointer to the new graph that is the multiplication of the two graphs.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph can not multiplie the current graph .
        **/
        Graph operator*(const Graph &g) const;

        /**
         * @brief This method overloads the operator *= to multiply two graphs.
         * @param g The graph to be multiplied by the current graph.
         * @return The current graph after the multiplication.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph can not multiplie the current graph .
        **/
        Graph& operator*=(const Graph &g);

        /**
         * @brief  This method overloads the operator == to compare two graphs.
         * @param g The graph to be compared to the current graph.
         * @return true if the two graphs are equal, false otherwise.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph.
        **/
        bool operator==(const Graph &g) const;
        
        /**
         * @brief This method overloads the operator != to compare two graphs.
         * @param g The graph to be compared to the current graph.
         * @return true if the two graphs are not equal, false otherwise.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph.
        **/
        bool operator!=(const Graph &g) const;

        /**
         * @brief This method overloads the operator < to compare two graphs.
         * @param g The graph to be compared to the current graph.
         * @return true if the current graph is less than the given graph, false otherwise.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph. 
        **/
        bool operator<(const Graph &g) const;

        /**
         * @brief This method overloads the operator <= to compare two graphs.
         * @param g The graph to be compared to the current graph.
         * @return true if the current graph is less than or equal to the given graph, false otherwise.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph. 
        **/
        bool operator<=(const Graph &g) const;

        /**
         * @brief This method overloads the operator > to compare two graphs.
         * @param g The graph to be compared to the current graph.
         * @return true if the current graph is greater than the given graph, false otherwise.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph.
        **/
        bool operator>(const Graph &g) const;

        /**
         * @brief This method overloads the operator >= to compare two graphs.
         * @param g The graph to be compared to the current graph.
         * @return true if the current graph is greater than or equal to the given graph, false otherwise.
         * @throws std::invalid_argument if one of the graphs is not loaded.
         * @throws std::invalid_argument if the given graph is not the same size as the current graph.
        **/
        bool operator>=(const Graph &g) const;

        /**
         * @brief This method overloads the operator << to print the graph.
         * @param os The output stream.
         * @param g The graph to be printed.
         * @return The output stream after printing the graph.
         * @throws std::invalid_argument if the graph is not loaded.
        **/
        friend std::ostream& operator<<(std::ostream& os, const Graph &g);

    };
};