#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph() {
    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder() {
    return this->order;
}

int Graph::getNumberEdges() {
    return this->number_edges;
}

//Function that verifies if the graph is directed
bool Graph::getDirected() {
    return this->directed;
}

//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge() {
    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode() {
    return this->weighted_node;
}

Node *Graph::getFirstNode(){
    return this->first_node;
}

Node *Graph::getLastNode() {
    return this->last_node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::insertNode(int id) {
    Node *next, *aux = nullptr;

    // Verifica se já existe algum nó
    if(this->getFirstNode() == nullptr) {
        this->first_node = new Node(id);
    } else {
        next = this->first_node;
        // Procura o último nó inserido
        while (next != nullptr) {
            aux = next;
            next = next->getNextNode();
        }
        // Inseri o nó na última posição
        aux->setNextNode(new Node(id));        
    }
}

void Graph::insertEdge(int id, int target_id, float weight) {
    // Procura se o nó id existe. Se não existir insere ele no grafo
    if(!this->searchNode(id))
        this->insertNode(id);
    // Procura se o nó target_id existe. Se não existir insere ele no grafo
    if(!this->searchNode(target_id))
        this->insertNode(id);

    Node *nodeId = this->getNode(id);
    Node *nodeTargetId = this->getNode(target_id);

    if(this->getDirected()) {
        // Cria a aresta => id -> target_id
        nodeId->insertEdge(target_id, weight);

        // Aumenta os graus de saída e de entrada
        nodeId->incrementOutDegree();
        nodeTargetId->incrementInDegree();
    } else {
        // Cria a aresta => id - target_id
        nodeId->insertEdge(id, weight);
        nodeTargetId->insertEdge(target_id, weight);

        // Aumenta os graus de saída e de entrada
        nodeId->incrementOutDegree();
        nodeTargetId->incrementOutDegree();
        nodeId->incrementInDegree();
        nodeTargetId->incrementInDegree();
    }
}

void Graph::removeNode(int id) { 
    Node *node, *nodeAux, *nodePrev;
    nodeAux = new Node(id);
    node = this->getFirstNode();

    while(node != nullptr) {
        node->removeEdge(id, this->getDirected(), nodeAux);
        node = node->getNextNode();
    }

    // Se o nó for o primeiro da lista
    if(node->getId() == id) {
        this->first_node = node->getNextNode();
        node->removeAllEdges();
        delete node;
        return;
    }

    nodeAux = node;
    node = node->getNextNode();
    while(node != nullptr) {
        if(node->getId() == id) {
            nodeAux->setNextNode(node->getNextNode());
            node->removeAllEdges();
            delete node;
            return;
        }
        nodePrev = node;
        node = node->getNextNode();
    }
}

bool Graph::searchNode(int id) {
    Node *node = this->getFirstNode();
    while(node != nullptr) {
        if(node->getId() == id)
            return true;
        node = node->getNextNode();
    }
}

Node *Graph::getNode(int id) {
    Node *node = this->getFirstNode();

    while(node != nullptr) {
        if(node->getId() == id)
            return node;
        node = node->getNextNode();
    }    
}


//Function that prints a set of edges belongs breadth tree

void Graph::breadthFirstSearch(ofstream &output_file) {
    
}



float Graph::floydMarshall(int idSource, int idTarget) {
    
}

   

float Graph::dijkstra(int idSource, int idTarget) {
    
}

//function that prints a topological sorting
void topologicalSorting(){

}

void breadthFirstSearch(ofstream& output_file) {

}
Graph* getVertexInduced(int* listIdNodes) {

}

Graph* agmKuskal() {

}
Graph* agmPrim() {

}
