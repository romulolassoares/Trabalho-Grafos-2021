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
#include <limits>

#include <bits/stdc++.h>

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
        this->last_node = this->getFirstNode();
    } else {
        if(!this->searchNode(id)) {
            next = this->first_node;
            // Procura o último nó inserido
            while (next != nullptr) {
                aux = next;
                next = next->getNextNode();
            }
            // Inseri o nó na última posição
            aux->setNextNode(new Node(id));
            this->last_node = this->getNode(id);
        }      
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
    Node *node, *nodeAux, *previous;
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
        previous = node;
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


float Graph::floydMarshall(int idSource, int idTarget) {
    Node *node = this->getFirstNode();
    Edge *edge;
    int *map = new int[this->getOrder()];
    float distance[this->getOrder()][this->getOrder()];
    int i = 0;
    while(node != nullptr) {
        map[i] = node->getId();
        node = node->getNextNode();
        i++;
    }

    // Ordena o map
    for (int i = 0; i < this->getOrder(); i++) {
        for(int j = 0; j < this->getOrder(); j++) {
            if(map[j] > map[i]) {
                int aux = map[i];
                map[i] = map[j];
                map[j] = aux;
            }
        }
    }

    node = this->getFirstNode();
    for(int i = 0; i < this->getOrder(); i++) {
        for(int j = 0; j < this->getOrder(); j++) {
            if(i == j) {
                distance[i][j] = 0;
            } else {
                distance[i][j] = numeric_limits<float>::infinity();
            }
        }
    }

    float **distance2 = this->matrixAdj();

    while(node != nullptr) {
        edge = node->getFirstEdge();
        int nodeID = mappingVector(map, node->getId(), this->getOrder());
        while(edge != nullptr) {
            int edgeID = mappingVector(map, edge->getTargetId(), this->getOrder());
            distance[nodeID][edgeID] = edge->getWeight();
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }

    for(int k = 0; k < this->getOrder(); k++) {
        for(int i = 0; i < this->getOrder(); i++) {
            for(int j = 0; j < this->getOrder(); j++) {
                if(distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    return distance[idSource][idTarget];
}

   
float Graph::dijkstra(int idSource, int idTarget) {
	int *distance = new int[this->order];
	int *map = new int[this->order];
	int *visit = new int[this->order];
	int *previous = new int[this->order];
	
	Node *node = this->getFirstNode();
    
	for(int i=0; i < this->order; i++, node = node->getNextNode()) {
		map[i] = node->getId();
		if(node->getId() == idSource) {
			distance[i] = 0;
			visit[i] = 0;
		} else {
			distance[i] = -1;
			visit[i] = 1;
		}
		previous[i] = -1;
	}

	this->recursiveDijkstra(distance, visit, previous, map, idSource);

	int distTotal = 0;
    int targetID = mappingVector(map, idTarget, this->getOrder());
	if(distance[targetID] != -1) {
		int path = previous[targetID];
		distTotal += distance[targetID];
		while (path != -1) {
			distTotal += distance[mappingVector(map, path, this->getOrder())];
			path = previous[mappingVector(map, path, this->getOrder())];
		}
	} else {
		distTotal = -1;
	}

	delete[] visit;
	delete[] previous;
	delete[] distance;
	delete[] map;

	return distTotal;
};

void Graph::recursiveDijkstra(int* distance, int* visit, int* previous, int* map, int current) {
	Node *node = this->getNode(current);
	Edge *edge = node->getFirstEdge();

	int currentIndex = mappingVector(map, current, this->getOrder());
	int indexEdge;

	while(edge != nullptr) {
		indexEdge = mappingVector(map, edge->getTargetId(), this->getOrder());

		if(distance[indexEdge] > -1) {
            if(distance[indexEdge] > distance[indexEdge] + edge->getWeight()) {
                distance[indexEdge] = distance[indexEdge] + edge->getWeight()+1;
                previous[indexEdge] = current;
            }
		} else {
            distance[indexEdge] = distance[indexEdge] + edge->getWeight()+1;
            previous[indexEdge] = current;
		}
		edge = edge->getNextEdge();
	}

	int small = -1;

	for(int i=0; i < this->order && small == -1; i++) {
		if((visit[i] && distance[i] > -1)) {
            small = distance[i];
            current = map[i];
		}
	}

	if(small > -1) {
		for(int i = 0; i < this->order; i++) {
			if((visit[i] == 1) && (distance[i] > -1) && (distance[i] < small) ) {
                small = distance[i];
                current = map[i];
            }
		}
		visit[currentIndex] = 0;
		this->recursiveDijkstra(distance, visit, previous, map, current);
	}
}


//function that prints a topological sorting
void topologicalSorting(){

}

/**
 * Árvore dada pela ordem de caminhamento em largura
 *
 * @param idNode id do vértice inicial.
 * 
 * @author Rômulo Luiz Araujo Souza Soares
 */
void Graph::breadthFirstSearch(int id) {
    int cnt = 0;
    Node *node = this->getFirstNode();
    Graph *graphAux = new Graph(this->getOrder(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());

    int *map = new int[this->getOrder()]; // Vetor para mapear os ids de cada nó no vetor
    int *topologicalNumber = new int[this->getOrder()];
    int *tree = new int[this->getOrder()];
    queue<int> queue;
    int i = 0;

    while(node != nullptr) {
        map[i] = node->getId();
        node = node->getNextNode();
        i++;
    }
    node = this->getFirstNode();

    while(node != nullptr) {
        int idNode = mappingVector(map, node->getId(), this->getOrder());
        topologicalNumber[idNode] = tree[idNode] = -1;
        node = node->getNextNode();
    }

    node = this->getNode(id);
    tree[mappingVector(map, node->getId(), this->getOrder())] = node->getId();

    queue.push(this->getNode(id)->getId());

    while(!queue.empty()) {
        Node *nodeAux = this->getNode(queue.front());
        queue.pop();
        while(nodeAux != nullptr) {
            Edge *edge = nodeAux->getFirstEdge();
            while(edge != nullptr) {
                int idEdge = mappingVector(map, edge->getTargetId(), this->getOrder());
                if(topologicalNumber[idEdge] == -1) {
                    tree[idEdge] = nodeAux->getId();
                    topologicalNumber[idEdge] = cnt++;
                    queue.push(edge->getTargetId());
                }
                edge = edge->getNextEdge();
            }
            nodeAux = nodeAux->getNextNode();
        }
    }

    for (int i = 0; i < this->getOrder(); i++) {
        if(tree[i] != -1) {
            if(map[i] != tree[i]) {
                graphAux->insertEdge(tree[i], map[i], 0);
            }
        } else {
            graphAux->insertNode(map[i]);
        }
    }
    cout << "Árvore dada pela ordem de caminhamento em largura. Null são as arestas de retorno" << endl;
    graphAux->printGraph();
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
        this->recursiveGetVertexInduced(edge->getTargetId(), graphAux);
        edge = edge->getNextEdge();
    }

    // node = node->getNextNode();

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

    if(node != nullptr) {
        edge = node->getFirstEdge();
        while(edge != nullptr) {
            if(graph->searchNode(edge->getTargetId())) {
                edge = edge->getNextEdge();
            }

            if(edge != nullptr) {
                graph->insertEdge(node->getId(), edge->getTargetId(), edge->getWeight());
                this->recursiveGetVertexInduced(edge->getTargetId(), graph);
                edge = edge->getNextEdge();
            }
        }
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

Graph* Graph::agmKuskal() {
}



/**
 * Algoritmo de Prim
 *
 * @return subgrafo gerado pelo algoritmo de Prim
 * 
 * @author Rômulo Luiz Araujo Souza Soares
 */
Graph* Graph::agmPrim() {

    int *parent = new int[this->getOrder()];
    float *distance = new float[this->getOrder()];
    bool *visit = new bool[this->getOrder()];
    int *map = new int[this->getOrder()];
    int inf = std::numeric_limits<float>::max();
    float **matrix;
    Graph *graphAux = new Graph(this->getOrder(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());

    Node *node = this->getFirstNode();
    // cout << "Order: " << this->getOrder() << endl;
    // cout << "for - start " << endl;
    for (int i = 0; i < this->getOrder(); i++) {
        // cout << "id: " << node << endl;
        // cout << i << endl;
        map[i] = node->getId();
        
        // cout << map[i] << " ";
        distance[i] = inf;
        visit[i] = false;
        node = node->getNextNode();
    }
    // cout << "- end" << endl;
    cout << endl;

    distance[0] = 0;
    parent[0] = -1;
    node = this->getFirstNode();

    // cout << "matrix - start ";
    matrix = this->matrixAdj();
    // cout << "- end" << endl;

    for(int i = 0; i < this->getOrder(); i++) {
        int vertex = minumumDistance(visit, distance);
        visit[vertex] = true;

        for (int j = 0; j < this->getOrder(); j++) {
            if((matrix[vertex][j]) && (visit[j] == false) && matrix[vertex][j] < (distance[j])) {
                parent[j] = vertex;
                distance[j] = matrix[vertex][j];
            }
        }
    }

    for(int i = 0; i < this->getOrder(); i++) {
        if(!(parent[i] == -1)) {
            graphAux->insertEdge(parent[i], i, matrix[i][parent[i]]);
        }
    }

    return graphAux;
}



int Graph::minumumDistance(bool *visit, float *distance) {
    float min = std::numeric_limits<float>::max();
    int lighterId;

    for (int i = 0; i < this->getOrder(); i++)
    {
        if(visit[i] == false && distance[i] <= min) {
            min = distance[i];
            lighterId = i;
        }
    }
    
    return lighterId;
}

void Graph::printGraph() {
    Node *node = this->getFirstNode();
    Edge *edge;
    // printf("\e[H\e[2J");
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

int Graph::mappingVector(int *map, int id, int size) {
    for(int i = 0; i < size; i++) {
        if(map[i] == id)
            return i;
    }
}


Graph* Graph::auxAgmPrim(int *list, int sizeList) {
    Graph *aux = subGraph(list, sizeList);
    // cout << "print" << endl;
    // aux->printGraph();
    // cout << "prim" << endl;
    aux->agmPrim();
    // cout << "print" << endl;
    // aux->printGraph();
    return aux->agmPrim();
}

bool verifyList(int id, int* list, int size) {
    // cout << sizeof(list) << endl;
    for(int i = 0; i < size; i++) {
        if(list[i] == id) {
            // cout << list[i] << " - true" << endl;
            return true;
        }
    }
    // cout << id << " - false" << endl;
    return false;
}

Graph* Graph::subGraph(int *list, int sizeList) {
    Node *node = this->getFirstNode();
    Edge *edge;
    // int sizeList = (sizeof(list)/sizeof(list[0]))+1;
    // cout << "sizeList: " << sizeList << endl;
    Graph *graphAux = new Graph(sizeList, this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());
    // cout << "graphAux: " << graphAux->getOrder() << endl;
    bool *visit = new bool[this->getOrder()];
    int *map = new int[this->getOrder()];

    int i = 0;
    while(node != nullptr) {
        map[i] = node->getId();
        visit[i] = false;
        i++;
        node = node->getNextNode();
    }
    node = this->getFirstNode();
    while(node != nullptr) {
        
        int nodeID = mappingVector(map, node->getId(), this->getOrder());
        // cout << node->getId() << " - " << visit[nodeID] << endl;
        if(verifyList(node->getId(), list, sizeList) && !visit[nodeID]) {
            edge = node->getFirstEdge();
            while(edge != nullptr) {
                int edgeID = mappingVector(map, edge->getTargetId(), this->getOrder());
                if(verifyList(edge->getTargetId(), list, sizeList) /*&& !visit[edgeID]*/) {
                    // cout << "edge: " << node->getId() << " -- " << edge->getTargetId() << endl;
                    graphAux->insertEdge(node->getId(), edge->getTargetId(), edge->getWeight());
                    visit[edgeID] = true;
                }
                edge = edge->getNextEdge();
            }
        }
        visit[nodeID] = true;
        node = node->getNextNode();
    }
    // graphAux->printGraph();
    return graphAux;
}



/**
 * Função auxiliar para montar a matrix de adjacência do grafo
 *
 * @return matrix de adjacência
 * 
 * @author Rômulo Luiz Araujo Souza Soares
 */
float** Graph::matrixAdj() {
    Node *node = this->getFirstNode();
    Edge *edge;
    int nodeID, edgeID;
    int *map = new int[this->getOrder()];
    float** matrix = (float **) calloc(this->getOrder()-1, sizeof(float *));
    for(int i = 0; i < this->getOrder(); i++) {
        matrix[i] = (float *) calloc (this->getOrder()-1, sizeof(float));
    }

    for (int i = 0; i < this->getOrder(); i++) {
        for(int j = 0; j < this->getOrder(); j++) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < this->getOrder(); i++) {
        map[i] = node->getId();
        node = node->getNextNode();
    }
    node = this->getFirstNode();

    // Ordena o map
    for (int i = 0; i < this->getOrder(); i++) {
        for(int j = 0; j < this->getOrder(); j++) {
            if(map[j] > map[i]) {
                int aux = map[i];
                map[i] = map[j];
                map[j] = aux;
            }
        }
    }

    while(node != nullptr) {
        nodeID = mappingVector(map, node->getId(), this->getOrder());
        edge = node->getFirstEdge();
        while(edge != nullptr) {
            edgeID = mappingVector(map, edge->getTargetId(), this->getOrder());
            if(this->getWeightedEdge()) {
                matrix[nodeID][edgeID] = edge->getWeight();
                if(!this->getDirected()) {
                    matrix[edgeID][nodeID] = edge->getWeight();
                }
            } else {
                matrix[nodeID][edgeID] = 1;
                if(!this->getDirected()) {
                    matrix[edgeID][nodeID] = 1;
                }
            }
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }
    return matrix;
}

