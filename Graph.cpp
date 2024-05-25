#include "Graph.hpp"

// This is the class constructor, set all boolean flags to false
GraphLib::Graph::Graph(){
    directed = false;
    negValues = false;
    weighted = false;
    loaded = false;
}

// This is the class destructor
GraphLib::Graph::~Graph(){}
/*
 This method loads values to the adjacency matrix that represents the graph.
 It also sets the boolean flags that represent the graph properties.
 If the graph is not squared or empty then the function will throw an invalid argument exception.
 If the graph is already loaded then the function will override it.
 */
void GraphLib::Graph::loadGraph(std::vector<std::vector<int>> mat){
    this->clear();
    if(mat.empty()){
        throw std::invalid_argument("The given matrix is empty.");
    }
    //check if the given matrix is squared
    for(size_t i = 0; i<mat.size();i++){
        if(mat[i].size() != mat.size()){
            throw std::invalid_argument("The given matrix is not squared.");
        }
    }
    size_t len = mat.size();
    bool flag = false;
    for(const auto& innerVec : mat){
        if( innerVec.size() != len){
            this->adjTable.clear();
        }
        if(!this->isNegValues()){
            for(const auto& element : innerVec){
                if(!this->isNegValues()){
                    if( element < 0){
                        this->setNegValues();
                        this->setWeighted();
                        break;
                    }
                }
                if(!this->isWeighted()){
                    if(element > 1){
                        this->setWeighted();
                    }
                }
            }
        }
        this->adjTable.push_back(innerVec);
    }
    if(!this->isSymetric()){
        this->setDirected();
    }
    this->setLoaded();
}

/*
 This method prints information about the graph.
*/
void GraphLib::Graph::printGraph(){
    if(!this->isLoaded()){
        throw std::invalid_argument("The graph is not loaded.");
    }
    int edge_count = 0;
    for(size_t i = 0; i<this->adjTable.size();i++){
        for(size_t j = 0; j<this->adjTable[0].size();j++){
            if(this->adjTable[i][j] != NO_EDGE){
                edge_count++;
            }
        }
    }
    std::string result = "This is a";
    if(this->isDirected()){
        result += " directed graph with " + std::to_string(this->adjTable.size()) + " vertices and " + std::to_string(edge_count) + " edges.";
    }else{
        result += "n undirected graph with " + std::to_string(this->adjTable.size()) + " vertices and " + std::to_string(edge_count/2) + " edges.";
    }
    
    std::cout << result << std::endl;
}

/*
 This method checks whether the matrix that represents the graph is symmetric or not.
*/
bool GraphLib::Graph::isSymetric(){
    for(size_t i = 0; i<this->adjTable.size();i++){
        for(size_t j = 0; j<this->adjTable[0].size();j++){
            if(this->adjTable[i][j] != this->adjTable[j][i]){
                return false;
            }
        }
    }
    return true;

}

