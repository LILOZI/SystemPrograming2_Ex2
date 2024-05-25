#include "Graph.hpp"
#include <stdexcept>

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

void GraphLib::Graph::copyFlags(const GraphLib::Graph &g){
    this->directed = g.isDirected();
    this->negValues = g.isNegValues();
    this->weighted = g.isWeighted();
    this->loaded = g.isLoaded();
}

void GraphLib::Graph::updateGraphFlags()
{
    this->directed = !this->isSymetric();
    this->negValues = false;
    this->weighted = false;
    for(size_t i = 0; i < this->getNumVertices(); i++){
        for(size_t j = 0; j < this->getNumVertices(); j++){
            if(this->adjTable[i][j] < 0){
                this->setNegValues();
                this->setWeighted();
                return;
            }
            if(this->adjTable[i][j] > 1){
                this->setWeighted();
            }
        }
    }
}

bool GraphLib::Graph::subGraph(const GraphLib::Graph &g) const
{
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    size_t vxs1 = this->getNumVertices();
    size_t vxs2 = g.getNumVertices();
    if(vxs1 > vxs2){
        return false;
    }
    for(size_t i = 0; i<= vxs2 - vxs1; i++){
        for(size_t j = 0; j<= vxs2 - vxs1; j++){
            bool finished = true;
            for(size_t k = 0; k < vxs1; k++){
                for(size_t l = 0; l < vxs1; l++){
                    if(this->adjTable[k][l] != g.getWeight(i + k, j + l)){
                        finished = false;
                        break;
                    }
                }
                if(!finished){
                    break;
                }
            }
            if(finished){
                return true;
            }
        }
    }
    return true;
}

int GraphLib::Graph::countEdges() const
{
    if(!this->loaded){
        throw std::invalid_argument("The graph is not loaded.");
    }
    size_t len = this->getNumVertices();
    int edge_count = 0;
    for(size_t i = 0; i<len; i++){
        for(size_t j = 0; j<len; j++){
            if(this->adjTable[i][j] != NO_EDGE){
                edge_count++;
            }
        }
    }
    return edge_count;
}

GraphLib::Graph& GraphLib::Graph::operator=(const GraphLib::Graph &g)
{
    if(!g.isLoaded()){
        throw std::invalid_argument("The assigning graph is not loaded.");
    }
    this->adjTable = g.getGraph();
    this->copyFlags(g);
    return *this;
}


GraphLib::Graph GraphLib::Graph::operator+(const GraphLib::Graph &g) const{
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    size_t vxs1 = this->getNumVertices();
    size_t vxs2 = g.getNumVertices();
    if(vxs1 != vxs2){
        throw std::invalid_argument("The given graph has different size.");
    }
    GraphLib::Graph result;
    std::vector<std::vector<int>> temp;
    for(size_t i = 0; i<vxs1; i++){
        std::vector<int> innerVec;
        for(size_t j = 0; j<vxs2; j++){
            innerVec.push_back(this->adjTable[i][j] + g.getWeight(i, j));
        }
        temp.push_back(innerVec);
    }
    result.loadGraph(temp);
    result.updateGraphFlags();
    return result;
}

GraphLib::Graph& GraphLib::Graph::operator+=(const GraphLib::Graph &g){
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    if(this->getNumVertices() != g.getNumVertices()){
        throw std::invalid_argument("The given graph has different size.");
    }
    *this = this->operator+(g);
    this->updateGraphFlags();
    return *this;
}

GraphLib::Graph GraphLib::Graph::operator++(int)
{
    Graph temp = *this;
    size_t len = this->getNumVertices();
    for(size_t i = 0; i<len; i++){
        for(size_t j = 0; j<len; j++){
            this->adjTable[i][j]++;
        }
    }
    temp.copyFlags(*this);
    this->updateGraphFlags();
    this->negValues = false;
    return temp;
}

GraphLib::Graph& GraphLib::Graph::operator++()
{
    size_t len = this->getNumVertices();
    for(size_t i = 0; i<len; i++){
        for(size_t j = 0; j<len; j++){
            this->adjTable[i][j]++;
        }
    }
    this->updateGraphFlags();
    return *this;
}

GraphLib::Graph GraphLib::Graph::operator+() const
{
    if (!this->loaded)
    {
        throw std::invalid_argument("The graph is not loaded.");
    }
    return *this;
}

GraphLib::Graph GraphLib::Graph::operator-(const GraphLib::Graph &g) const{
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    size_t vxs1 = this->getNumVertices();
    size_t vxs2 = g.getNumVertices();
    if(vxs1 != vxs2){
        throw std::invalid_argument("The given graph has different size.");
    }
    GraphLib::Graph result;
    std::vector<std::vector<int>> temp;
    for(size_t i = 0; i<this->adjTable.size();i++){
        std::vector<int> innerVec;
        for(size_t j = 0; j<this->adjTable[0].size();j++){
            innerVec.push_back(this->adjTable[i][j] - g.getWeight(i, j));
        }
        temp.push_back(innerVec);
    }
    result.loadGraph(temp);
    result.updateGraphFlags();
    return result;
}

GraphLib::Graph& GraphLib::Graph::operator-=(const GraphLib::Graph &g){
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    size_t vxs1 = this->getNumVertices();
    size_t vxs2 = g.getNumVertices();
    if(vxs1 != vxs2){
        throw std::invalid_argument("The given graph has different size.");
    }
    *this = this->operator-(g);
    this->updateGraphFlags();
    return *this;
}

GraphLib::Graph GraphLib::Graph::operator--(int)
{
    Graph temp = *this;
    temp.copyFlags(*this);
    size_t len = this->getNumVertices();
    for(size_t i = 0; i<len; i++){
        for(size_t j = 0; j<len; j++){
            this->adjTable[i][j]--;
        }
    }
    this->updateGraphFlags();  
    return temp;
}

GraphLib::Graph& GraphLib::Graph::operator--()
{
    size_t len = this->getNumVertices();
    for(size_t i = 0; i<len;i ++){
        for(size_t j = 0; j<len; j++){
            this->adjTable[i][j]--;
        }
    }
    this->updateGraphFlags();
    return *this;
}

GraphLib::Graph GraphLib::Graph::operator-() const
{   
    Graph temp = *this;
    temp *= -1;
    temp.updateGraphFlags();
    return temp;
}

GraphLib::Graph GraphLib::Graph::operator*(int scalar) const{
    if(!this->loaded){
        throw std::invalid_argument("The graph is not loaded.");
    }
    Graph result;
    std::vector<std::vector<int>> temp;
    size_t len = this->getNumVertices();
    for(size_t i = 0; i<len; i++){
        std::vector<int> innerVec;
        for(size_t j = 0; j<len; j++){
            innerVec.push_back(this->adjTable[i][j] * scalar);
        }
        temp.push_back(innerVec);
    }
    result.loadGraph(temp);
    result.updateGraphFlags();
    return result;
}

GraphLib::Graph& GraphLib::Graph::operator*=(int scalar){
    if(!this->loaded){
        throw std::invalid_argument("The graph is not loaded.");
    }
    size_t len = this->getNumVertices();
    for(size_t i = 0; i<len; i++){
        for(size_t j = 0; j<len; j++){
            this->adjTable[i][j] *= scalar;
        }
    }
    this->updateGraphFlags();
    return *this;
}

GraphLib::Graph GraphLib::Graph::operator/(int scalar) const{
    if(!this->loaded){
        throw std::invalid_argument("The graph is not loaded.");
    }
    if(scalar == 0){
        throw std::invalid_argument("The scalar value is zero.");
    }
    Graph result;
    std::vector<std::vector<int>> temp;
    size_t len = this->getNumVertices();
    for(size_t i = 0; i<len; i++){
        std::vector<int> innerVec;
        for(size_t j = 0; j<len; j++){
            innerVec.push_back(this->adjTable[i][j] / scalar);
        }
        temp.push_back(innerVec);
    }
    result.loadGraph(temp);
    result.updateGraphFlags();
    return result;
}

GraphLib::Graph& GraphLib::Graph::operator/=(int scalar){
    if(!this->loaded){
        throw std::invalid_argument("The graph is not loaded.");
    }
    if(scalar == 0){
        throw std::invalid_argument("The scalar value is zero.");
    }
    size_t len = this->getNumVertices();
    for(size_t i = 0; i<len; i++){
        for(size_t j = 0; j<len; j++){
            this->adjTable[i][j] /= scalar;
        }
    }
    this->updateGraphFlags();
    return *this;
}

GraphLib::Graph GraphLib::Graph::operator*(const GraphLib::Graph &g) const{
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    size_t vxs1 = this->getNumVertices();
    size_t vxs2 = g.getNumVertices();
    if(vxs1 != vxs2){
        throw std::invalid_argument("The given graph has different size.");
    }
    GraphLib::Graph result;
    std::vector<std::vector<int>> temp (vxs1, std::vector<int>(vxs1, NO_EDGE));
    for(size_t i = 0; i<vxs1; i++){
        for(size_t j = 0; j<vxs1; j++){
            int sum = 0;
            for(size_t k = 0; k<vxs1;k++){
                temp[i][j] += this->adjTable[i][k] * g.getWeight(k, j);
            }
        }
    }
    result.loadGraph(temp);
    result.updateGraphFlags();
    return result;
}

GraphLib::Graph& GraphLib::Graph::operator*=(const GraphLib::Graph &g){
    try{
        *this = this->operator*(g);
        this->updateGraphFlags();
        return *this;
    }
    catch(const std::invalid_argument &e){
        throw e;
    }
}

bool GraphLib::Graph::operator==(const GraphLib::Graph &g) const{
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    size_t vxs1 = this->getNumVertices();
    size_t vxs2 = g.getNumVertices();
    if(vxs1 != vxs2){
        return false;
    }
    for(size_t i = 0; i<vxs1; i++){
        for(size_t j = 0; j<vxs1; j++){
            if(this->adjTable[i][j] != g.getWeight(i, j)){
                return false;
            }
        }
    }
    return true;
}

bool GraphLib::Graph::operator!=(const GraphLib::Graph &g) const{
    try{
        return !(*this == g);
    }
    catch(const std::invalid_argument &e){
        throw e;
    }
}

bool GraphLib::Graph::operator<(const GraphLib::Graph &g) const
{
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }

    // G1 is a subgraph of G2 then, G1 < G2
    if(this->subGraph(g)){
        return true;
    }
    // G1 > G2 or G1 == G2
    if(g.subGraph(*this) || *this == g){
        return false;
    }
    int edge1 = this->countEdges();
    int edge2 = g.countEdges();
    // G1 has less edges than G2 then, G1 < G2
    if(edge1 < edge2){
        return true;
    }
    // G1 > G2
    if(edge1 > edge2){
        return false;
    }
    //G1 has less vertices than G2 then, G1 < G2
    if(this->getNumVertices() < g.getNumVertices()){
        return true;
    }
    return false;

}

bool GraphLib::Graph::operator<=(const GraphLib::Graph &g) const
{
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    return *this == g || *this < g;
}


bool GraphLib::Graph::operator>(const GraphLib::Graph &g) const
{
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    return !(*this <= g);
}

bool GraphLib::Graph::operator>=(const GraphLib::Graph &g) const
{
    if(!g.isLoaded() || !this->loaded){
        throw std::invalid_argument("One of the graphs is not loaded.");
    }
    return !(*this < g);
}

std::ostream& GraphLib::operator<<(std::ostream& os, const GraphLib::Graph& g)
{
    if(!g.isLoaded()){
        throw std::invalid_argument("The graph is not loaded.");
    }
    size_t len = g.getNumVertices();
    for(size_t i = 0; i<len; i++){
        os << "[ ";
        for(size_t j = 0; j<len; j++){
            os << g.getWeight(i, j) << " ";
        }
        os << "]" << std::endl;
    }
    os << std::endl;
    return os;
}