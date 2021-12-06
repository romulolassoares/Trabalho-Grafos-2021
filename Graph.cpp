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
    Node *next;
    Node *aux = nullptr;

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
        this->insertNode(target_id);

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
        nodeId->insertEdge(target_id, weight);
        nodeTargetId->insertEdge(id, weight);

        // // Aumenta os graus de saída e de entrada
        // nodeId->incrementOutDegree();
        // nodeTargetId->incrementOutDegree();
        // nodeId->incrementInDegree();
        // nodeTargetId->incrementInDegree();
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

/**
 * Subgrafo Vértice-induzido pelo Fecho Transitivo Direto
 *
 * @param idNode id do vértice inicial.
 * @return subgrafo gerado pelo fecho transitivo direto
 * 
 * @author Rômulo Luiz Araujo Souza Soares
 */
Graph* Graph::getVertexInduced(int idNode) {
    Node *node = this->getNode(idNode);
    Edge *edge;
    Graph *graphAux = new Graph(this->getOrder(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());

    edge = node->getFirstEdge();

    while(edge != nullptr) {
        graphAux->insertEdge(node->getId(), edge->getTargetId(), edge->getWeight());
        cout << node->getId() << " -> ";
        cout << edge->getTargetId() << endl;
        this->recursiveGetVertexInduced(edge->getTargetId(), graphAux);
        edge = edge->getNextEdge();
    }

    node = node->getNextNode();

    return graphAux;
}

/**
 * Função auxiliar para achar o Subgrafo Vértice-induzido pelo Fecho Transitivo Direto
 *
 * @param idNode id do vértice inicial.
 * @param graph subgrafo
 */
void Graph::recursiveGetVertexInduced(int id, Graph *graph) {
    Node *node = this->getNode(id);
    Edge *edge;

    edge = node->getFirstEdge();

    while(edge != nullptr) {
        graph->insertEdge(node->getId(), edge->getTargetId(), edge->getWeight());
        cout << node->getId() << " -> ";
        cout << edge->getTargetId() << endl;
        this->recursiveGetVertexInduced(edge->getTargetId(), graph);
        edge = edge->getNextEdge();
    }
}

/**
 * Subgrafo Vértice-induzido pelo Fecho Transitivo Indireto
 *
 * @param idNode id do vértice inicial.
 * @return subgrafo gerado pelo fecho transitivo indireto
 * 
 * @author Rômulo Luiz Araujo Souza Soares
 */
Graph* Graph::getIndirectTransitive(int idNode) {
    
    Node *node = this->getFirstNode();
    Edge *edge;
    Graph *graphAux = new Graph(this->getOrder(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());
    Graph *graph = new Graph(this->getOrder(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());

    graphAux = getVertexInduced(idNode);   
    while(node != nullptr) {
        if(!graphAux->searchNode(node->getId())) {
            graph->insertNode(node->getId());
            edge = node->getFirstEdge();
            while (edge != nullptr) {
                if(!graphAux->searchNode(edge->getTargetId())) {
                    graph->insertEdge(node->getId(), edge->getTargetId(), edge->getWeight());
                }
                edge = edge->getNextEdge();
            }
        }
        node = node->getNextNode();
    }
    return graph;
}

Graph* agmKuskal() {

}
Graph* agmPrim() {

}

void Graph::printGraph() {
    Node *node = this->getFirstNode();
    Edge *edge;
    printf("\e[H\e[2J");
    cout << "Lista de adjacência" << endl;
    while(node != nullptr) {
        edge = node->getFirstEdge();
        cout << node->getId() << " => ";
        while(edge != nullptr) {
            cout << edge->getTargetId() << " - ";
            edge = edge->getNextEdge();
        }
        cout << "null" << endl;
        node = node->getNextNode();
    }

}

void Graph::printGraphDot(ofstream& file) {
    if(file.is_open()) {
        cout << "Salvando o grafo" << endl;

        Node *node = this->getFirstNode();
        Edge *edge;

        // Verifica se é ou não direcionado
        if(this->getDirected()) {
            file << "digraph { \n";
        } else {
            file << "strict graph { \n";
        }

        // Verifica se o nó tem peso
        if(this->getWeightedNode()) {
            while(node != nullptr) {
                file << "   " << node->getId() << " [weight = ";
                file << node->getWeight() << "] \n";
                node = node->getNextNode();
            }
        }

        node = this->getFirstNode();

        while(node != nullptr) {
            edge = node->getFirstEdge();
            while(edge != nullptr) {
                file << "   " << node->getId();
                if(this->getDirected()) {
                    file << "->" ;
                } else {
                    file << "--";
                }
                file << edge->getTargetId();

                if(this->getWeightedEdge()) {
                    file << " [label=" << edge->getWeight();
                    file << ",weight=" << edge->getWeight() << "]";
                }
                file << "\n";
                edge = edge->getNextEdge();
            }
            node = node->getNextNode();
        }

        file << "} \n";
    } else {
        cout << "Falha ao abrir o arquivo";
    }
}