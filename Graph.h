/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>

using namespace std;

class Graph{

    //Atributes
    private:
        int order;
        int number_edges;
        bool directed;
        bool weighted_edge;
        bool weighted_node;
        Node* first_node;
        Node* last_node;

    public:
        //Constructor
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
        //Destructor
        ~Graph();
        //Getters
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        bool getWeightedNode();
        Node* getFirstNode();
        Node* getLastNode();
        //Other methods
        void insertNode(int id);
        void insertEdge(int id, int target_id, float weight);
        void removeNode(int id);
        bool searchNode(int id);
        Node* getNode(int id);

        //methods phase1
        void topologicalSorting();
        void breadthFirstSearch(int id);
        Graph* getVertexInduced(int idNode);
        Graph* getIndirectTransitive(int idNode);
        Graph* agmKuskal();
        Graph* agmPrim();
        float floydMarshall(int idSource, int idTarget);
        float dijkstra(int idSource, int idTarget);
        void recursiveDijkstra(int* distance, int* visit, int* previous, int* map, int current);

        //methods phase1
        float greed();
        float greedRandom();
        float greedRactiveRandom();
    public:
        //Auxiliar methods
        void printGraphDot(ofstream& file);
        void printGraph();
        void recursiveGetVertexInduced(int id, Graph *graph);
        int mappingVector(int *map, int id, int size);

};

#endif // GRAPH_H_INCLUDED
